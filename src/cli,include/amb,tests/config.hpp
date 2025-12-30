#pragma once

#include <string>
#include <filesystem>
#include <optional>
#include <unordered_map>

namespace amb {

struct GlobalConfig {
    // Paths
    std::filesystem::path ambRootDir;
    std::filesystem::path cacheDir;
    std::filesystem::path libDir;
    std::filesystem::path tempDir;
    
    // Registry
    std::string registryUrl;
    std::string registryApiKey;
    
    // Network
    int networkTimeout = 30; // segundos
    int maxRetries = 3;
    
    // Security
    bool allowInsecure = false;
    bool verifySsl = true;
    
    // Features
    bool autoUpdate = false;
    bool verbose = false;
    bool colorOutput = true;
    
    // Override paths with environment variables
    void applyEnvironmentOverrides();
};

class ConfigManager {
public:
    static ConfigManager& instance();
    
    // Carrega configuração
    bool load();
    bool save();
    
    // Getters
    const GlobalConfig& config() const { return config_; }
    std::filesystem::path getAmbRoot() const;
    std::filesystem::path getCacheDir() const;
    std::filesystem::path getLibDir() const;
    std::filesystem::path getTempDir() const;
    
    // Setters
    void setRegistryUrl(const std::string& url);
    void setApiKey(const std::string& key);
    void setVerbose(bool verbose);
    void setAllowInsecure(bool allow);
    
    // Validação
    bool validate() const;
    std::vector<std::string> getValidationErrors() const;
    
private:
    ConfigManager();
    ~ConfigManager() = default;
    
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    
    std::filesystem::path getUserConfigPath() const;
    std::filesystem::path getSystemConfigPath() const;
    std::filesystem::path getLocalConfigPath() const;
    
    bool loadFromFile(const std::filesystem::path& path);
    bool saveToFile(const std::filesystem::path& path) const;
    
    void createDefaultConfig();
    void ensureDirectoriesExist();
    
    GlobalConfig config_;
    bool loaded_ = false;
    std::filesystem::path configFilePath_;
};

} // namespace amb