#pragma once

#include <filesystem>
#include <string>
#include <optional>
#include <unordered_map>

namespace amb {

namespace fs = std::filesystem;

struct GlobalConfig {
    fs::path ambRootDir;
    fs::path cacheDir;
    fs::path libDir;
    std::string registryUrl = "file://./registry"; // Default local
    bool allowInsecure = false;
    int networkTimeout = 30;
    
    // Default constructor sets default paths
    GlobalConfig();
};

class ConfigManager {
public:
    // Singleton pattern
    static ConfigManager& instance();
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    
    // Lifecycle
    bool initialize();
    bool isInitialized() const { return initialized_; }
    
    // Configuration access
    const GlobalConfig& config() const { return config_; }
    GlobalConfig& mutableConfig() { return config_; }
    
    // Path helpers
    fs::path getAmbRoot() const;
    fs::path getCacheDir() const;
    fs::path getLibDir() const;
    fs::path getRegistryPath() const;
    
    // Configuration manipulation
    void setRegistryUrl(const std::string& url);
    void setAllowInsecure(bool allow);
    
    // Save/load
    bool load();
    bool save();
    
private:
    ConfigManager() = default;
    
    GlobalConfig config_;
    bool initialized_ = false;
    fs::path configPath_;
    
    void setupDefaultPaths();
    fs::path findConfigFile() const;
};

} // namespace amb