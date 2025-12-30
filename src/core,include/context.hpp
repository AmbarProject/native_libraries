#pragma once

#include <memory>
#include <filesystem>
#include <string>
#include <optional>

namespace amb {

class ConfigManager;

// Contexto global da aplicação
class Context {
public:
    Context();
    ~Context();
    
    // Inicializa contexto
    bool initialize();
    
    // Getters
    std::filesystem::path getProjectRoot() const;
    std::filesystem::path getAmbRoot() const;
    std::filesystem::path getCacheDir() const;
    std::filesystem::path getLibDir() const;
    
    // Estado
    bool isInsideProject() const;
    bool isInitialized() const { return initialized_; }
    
    // Configuração
    void setVerbose(bool verbose);
    bool isVerbose() const;
    
    void setDryRun(bool dryRun);
    bool isDryRun() const;
    
    // Utilitários
    std::optional<std::filesystem::path> findFileInPath(
        const std::string& filename
    ) const;
    
private:
    bool findProjectRoot();
    bool setupDirectories();
    
    bool initialized_ = false;
    bool verbose_ = false;
    bool dryRun_ = false;
    std::filesystem::path projectRoot_;
    std::filesystem::path ambRoot_;
    
    std::unique_ptr<ConfigManager> configManager_;
};

} // namespace amb