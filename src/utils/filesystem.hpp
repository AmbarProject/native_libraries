#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <optional>
#include <functional>

namespace amb {

namespace fs = std::filesystem;

class FileSystem {
public:
    // Directory operations
    static bool createDirectory(const fs::path& path);
    static bool createDirectories(const fs::path& path);
    static bool removeDirectory(const fs::path& path);
    static bool removeDirectories(const fs::path& path);
    static bool copyDirectory(const fs::path& from, const fs::path& to);
    
    // File operations
    static std::optional<std::string> readFile(const fs::path& path);
    static bool writeFile(const fs::path& path, const std::string& content);
    static bool appendFile(const fs::path& path, const std::string& content);
    static bool copyFile(const fs::path& from, const fs::path& to);
    static bool removeFile(const fs::path& path);
    
    // File information
    static bool exists(const fs::path& path);
    static bool isDirectory(const fs::path& path);
    static bool isFile(const fs::path& path);
    static bool isEmpty(const fs::path& path);
    static uintmax_t fileSize(const fs::path& path);
    static std::string filename(const fs::path& path);
    static std::string extension(const fs::path& path);
    
    // Directory listing
    static std::vector<fs::path> listFiles(const fs::path& dir);
    static std::vector<fs::path> listDirectories(const fs::path& dir);
    static std::vector<fs::path> listAll(const fs::path& dir);
    
    // Path manipulation
    static fs::path absolute(const fs::path& path);
    static fs::path canonical(const fs::path& path);
    static fs::path relative(const fs::path& path, const fs::path& base = fs::current_path());
    static fs::path normalize(const fs::path& path);
    
    // Special paths
    static fs::path getHomeDirectory();
    static fs::path getTempDirectory();
    static fs::path getCurrentDirectory();
    static bool setCurrentDirectory(const fs::path& path);
    
    // Search operations
    static std::vector<fs::path> findFiles(const fs::path& dir, const std::string& pattern);
    static std::vector<fs::path> findFilesRecursive(const fs::path& dir, const std::string& pattern);
    
    // Hash operations (simplified for MVP)
    static std::string calculateFileHash(const fs::path& path);
    static std::string calculateStringHash(const std::string& content);
    
    // Archive operations (for future use)
    static bool extractZip(const fs::path& archive, const fs::path& destination);
    static bool createZip(const fs::path& source, const fs::path& archive);
};

} // namespace amb