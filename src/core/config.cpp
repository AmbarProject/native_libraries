#include "amb/config.hpp"
#include "utils/logger.hpp"
#include "utils/filesystem.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace amb {

GlobalConfig::GlobalConfig() {
    auto home = FileSystem::getHomeDirectory();
    ambRootDir = home / ".ambar";
    cacheDir = ambRootDir / "cache";
    libDir = ambRootDir / "lib";
}

ConfigManager& ConfigManager::instance() {
    static ConfigManager instance;
    return instance;
}

bool ConfigManager::initialize() {
    if (initialized_) {
        return true;
    }
    
    setupDefaultPaths();
    
    // Try to load config
    load();
    
    // Ensure directories exist
    FileSystem::createDirectories(config_.ambRootDir);
    FileSystem::createDirectories(config_.cacheDir);
    FileSystem::createDirectories(config_.libDir);
    
    initialized_ = true;
    Logger::debug("Configuration initialized");
    
    return true;
}

void ConfigManager::setupDefaultPaths() {
    // Defaults já estão no construtor de GlobalConfig
    configPath_ = config_.ambRootDir / "config.json";
}

fs::path ConfigManager::getAmbRoot() const {
    return config_.ambRootDir;
}

fs::path ConfigManager::getCacheDir() const {
    return config_.cacheDir;
}

fs::path ConfigManager::getLibDir() const {
    return config_.libDir;
}

fs::path ConfigManager::getRegistryPath() const {
    // Se for file://, extrai o path
    if (config_.registryUrl.starts_with("file://")) {
        return fs::path(config_.registryUrl.substr(7));
    }
    return fs::path();
}

void ConfigManager::setRegistryUrl(const std::string& url) {
    config_.registryUrl = url;
    save();
}

void ConfigManager::setAllowInsecure(bool allow) {
    config_.allowInsecure = allow;
    save();
}

bool ConfigManager::load() {
    if (!FileSystem::exists(configPath_)) {
        Logger::debug("Config file not found, using defaults");
        return true;
    }
    
    try {
        auto content = FileSystem::readFile(configPath_);
        if (!content) {
            Logger::warning("Failed to read config file");
            return false;
        }
        
        auto j = json::parse(*content);
        
        if (j.contains("registry_url")) {
            config_.registryUrl = j["registry_url"];
        }
        
        if (j.contains("allow_insecure")) {
            config_.allowInsecure = j["allow_insecure"];
        }
        
        if (j.contains("network_timeout")) {
            config_.networkTimeout = j["network_timeout"];
        }
        
        Logger::debug("Configuration loaded from {}", configPath_.string());
        return true;
        
    } catch (const std::exception& e) {
        Logger::warning("Failed to parse config file: {}", e.what());
        return false;
    }
}

bool ConfigManager::save() {
    try {
        json j;
        j["registry_url"] = config_.registryUrl;
        j["allow_insecure"] = config_.allowInsecure;
        j["network_timeout"] = config_.networkTimeout;
        
        std::string content = j.dump(2);
        return FileSystem::writeFile(configPath_, content);
        
    } catch (const std::exception& e) {
        Logger::error("Failed to save config: {}", e.what());
        return false;
    }
}

} // namespace amb