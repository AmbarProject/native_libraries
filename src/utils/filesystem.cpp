#include "utils/filesystem.hpp"
#include "utils/error.hpp"
#include "utils/logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <pwd.h>
#endif

namespace amb {

bool FileSystem::createDirectory(const fs::path& path) {
    try {
        if (exists(path)) {
            return isDirectory(path);
        }
        return fs::create_directory(path);
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to create directory {}: {}", path.string(), e.what());
        return false;
    }
}

bool FileSystem::createDirectories(const fs::path& path) {
    try {
        if (exists(path)) {
            return isDirectory(path);
        }
        fs::create_directories(path);
        return true;
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to create directories {}: {}", path.string(), e.what());
        return false;
    }
}

bool FileSystem::removeDirectory(const fs::path& path) {
    try {
        if (!exists(path)) {
            return true;
        }
        return fs::remove(path);
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to remove directory {}: {}", path.string(), e.what());
        return false;
    }
}

bool FileSystem::removeDirectories(const fs::path& path) {
    try {
        if (!exists(path)) {
            return true;
        }
        fs::remove_all(path);
        return true;
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to remove directories {}: {}", path.string(), e.what());
        return false;
    }
}

std::optional<std::string> FileSystem::readFile(const fs::path& path) {
    try {
        if (!isFile(path)) {
            return std::nullopt;
        }
        
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            return std::nullopt;
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
        
    } catch (const std::exception& e) {
        Logger::error("Failed to read file {}: {}", path.string(), e.what());
        return std::nullopt;
    }
}

bool FileSystem::writeFile(const fs::path& path, const std::string& content) {
    try {
        // Create parent directory if it doesn't exist
        if (path.has_parent_path()) {
            createDirectories(path.parent_path());
        }
        
        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        file.write(content.data(), content.size());
        return file.good();
        
    } catch (const std::exception& e) {
        Logger::error("Failed to write file {}: {}", path.string(), e.what());
        return false;
    }
}

bool FileSystem::exists(const fs::path& path) {
    try {
        return fs::exists(path);
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to check existence of {}: {}", path.string(), e.what());
        return false;
    }
}

bool FileSystem::isDirectory(const fs::path& path) {
    try {
        return fs::is_directory(path);
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to check if {} is directory: {}", path.string(), e.what());
        return false;
    }
}

bool FileSystem::isFile(const fs::path& path) {
    try {
        return fs::is_regular_file(path);
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to check if {} is file: {}", path.string(), e.what());
        return false;
    }
}

std::vector<fs::path> FileSystem::listFiles(const fs::path& dir) {
    std::vector<fs::path> files;
    
    try {
        if (!isDirectory(dir)) {
            return files;
        }
        
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path());
            }
        }
        
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to list files in {}: {}", dir.string(), e.what());
    }
    
    return files;
}

std::vector<fs::path> FileSystem::listDirectories(const fs::path& dir) {
    std::vector<fs::path> dirs;
    
    try {
        if (!isDirectory(dir)) {
            return dirs;
        }
        
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (entry.is_directory()) {
                dirs.push_back(entry.path());
            }
        }
        
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to list directories in {}: {}", dir.string(), e.what());
    }
    
    return dirs;
}

fs::path FileSystem::getHomeDirectory() {
    #ifdef _WIN32
        char* userProfile = nullptr;
        size_t len = 0;
        if (_dupenv_s(&userProfile, &len, "USERPROFILE") == 0 && userProfile != nullptr) {
            fs::path result(userProfile);
            free(userProfile);
            return result;
        }
        return fs::path();
    #else
        const char* home = getenv("HOME");
        if (home != nullptr) {
            return fs::path(home);
        }
        
        // Fallback to getpwuid
        struct passwd* pw = getpwuid(getuid());
        if (pw != nullptr) {
            return fs::path(pw->pw_dir);
        }
        
        return fs::path();
    #endif
}

fs::path FileSystem::getCurrentDirectory() {
    try {
        return fs::current_path();
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to get current directory: {}", e.what());
        return fs::path();
    }
}

bool FileSystem::setCurrentDirectory(const fs::path& path) {
    try {
        fs::current_path(path);
        return true;
    } catch (const fs::filesystem_error& e) {
        Logger::error("Failed to set current directory to {}: {}", path.string(), e.what());
        return false;
    }
}

std::string FileSystem::calculateFileHash(const fs::path& path) {
    // Simplified hash for MVP - use file size and modification time
    // In production, use SHA256 from OpenSSL or similar
    try {
        if (!isFile(path)) {
            return "";
        }
        
        auto size = fileSize(path);
        auto time = fs::last_write_time(path);
        
        std::stringstream ss;
        ss << std::hex << size << "-" << time.time_since_epoch().count();
        return ss.str();
        
    } catch (const std::exception& e) {
        Logger::error("Failed to calculate hash for {}: {}", path.string(), e.what());
        return "";
    }
}

} // namespace amb