#pragma once

#include <memory>
#include <filesystem>
#include <string>
#include <optional>

namespace amb {

class ConfigManager;

class Context {
public:
    Context();
    ~Context();
    
    // Lifecycle
    bool initialize();
    bool isInitialized() const { return initialized_; }
    
    // Project detection
    bool isInsideProject() const { return projectRoot_.has_value(); }
    std::optional<std::filesystem::path> getProjectRoot() const { return projectRoot_; }
    
    // Configuration
    std::filesystem::path getAmbRoot() const;
    std::filesystem::path getCacheDir() const;
    std::filesystem::path getLibDir() const;
    
    // State
    void setVerbose(bool verbose) { verbose_ = verbose; }
    bool isVerbose() const { return verbose_; }
    
private:
    bool findProjectRoot();
    void setupDirectories();
    
    bool initialized_ = false;
    bool verbose_ = false;
    std::optional<std::filesystem::path> projectRoot_;
};

} // namespace amb