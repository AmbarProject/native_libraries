#include "core/context.hpp"
#include "amb/config.hpp"
#include "utils/logger.hpp"
#include "utils/filesystem.hpp"

#include <iostream>

namespace amb {

Context::Context() = default;

Context::~Context() = default;

bool Context::initialize() {
    if (initialized_) {
        return true;
    }
    
    Logger::debug("Initializing context...");
    
    // Initialize configuration
    if (!ConfigManager::instance().initialize()) {
        Logger::error("Failed to initialize configuration");
        return false;
    }
    
    // Find project root
    findProjectRoot();
    
    // Setup directories
    setupDirectories();
    
    initialized_ = true;
    Logger::debug("Context initialized successfully");
    
    if (isInsideProject()) {
        Logger::debug("Inside project: {}", projectRoot_->string());
    } else {
        Logger::debug("Not inside a project");
    }
    
    return true;
}

bool Context::findProjectRoot() {
    namespace fs = std::filesystem;
    
    fs::path current = fs::current_path();
    
    // Look for ambar.json or ambar.lock
    while (current != current.root_path()) {
        if (FileSystem::isFile(current / "ambar.json") ||
            FileSystem::isFile(current / "ambar.lock")) {
            projectRoot_ = current;
            return true;
        }
        current = current.parent_path();
    }
    
    projectRoot_.reset();
    return false;
}

void Context::setupDirectories() {
    // Ensure required directories exist
    auto& config = ConfigManager::instance().config();
    
    FileSystem::createDirectory(config.ambRootDir);
    FileSystem::createDirectory(config.cacheDir);
    FileSystem::createDirectory(config.libDir);
    
    // Create project directories if inside project
    if (isInsideProject()) {
        FileSystem::createDirectory(*projectRoot_ / "ambar_modules");
        FileSystem::createDirectory(*projectRoot_ / "ambar_modules" / "lib");
    }
}

std::filesystem::path Context::getAmbRoot() const {
    return ConfigManager::instance().getAmbRoot();
}

std::filesystem::path Context::getCacheDir() const {
    return ConfigManager::instance().getCacheDir();
}

std::filesystem::path Context::getLibDir() const {
    return ConfigManager::instance().getLibDir();
}

} // namespace amb