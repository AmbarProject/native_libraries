#include "core/context.hpp"
#include "config/config_manager.hpp"
#include "utils/logger.hpp"
#include "utils/filesystem.hpp"

#include <cstdlib>
#include <algorithm>

namespace amb {

Context::Context() = default;

Context::~Context() = default;

bool Context::initialize() {
    if (initialized_) {
        return true;
    }
    
    try {
        Logger::debug("Initializing context...");
        
        // Carrega configuração
        configManager_ = std::make_unique<ConfigManager>();
        if (!configManager_->load()) {
            Logger::warn("Failed to load configuration, using defaults");
        }
        
        // Encontra raiz do projeto (se houver)
        findProjectRoot();
        
        // Configura diretórios
        if (!setupDirectories()) {
            Logger::error("Failed to setup directories");
            return false;
        }
        
        initialized_ = true;
        Logger::debug("Context initialized successfully");
        
        if (isInsideProject()) {
            Logger::debug("Inside project: {}", projectRoot_.string());
        }
        
        return true;
        
    } catch (const std::exception& e) {
        Logger::error("Failed to initialize context: {}", e.what());
        return false;
    }
}

bool Context::findProjectRoot() {
    std::filesystem::path current = std::filesystem::current_path();
    
    // Procura por ambar.json ou .ambar/ subindo diretórios
    while (!current.empty() && current != current.root_path()) {
        std::filesystem::path ambarJson = current / "ambar.json";
        std::filesystem::path ambarDir = current / ".ambar";
        
        if (FileSystem::isFile(ambarJson) || FileSystem::isDirectory(ambarDir)) {
            projectRoot_ = current;
            Logger::debug("Found project root: {}", projectRoot_.string());
            return true;
        }
        
        current = current.parent_path();
    }
    
    Logger::debug("No project root found");
    return false;
}

bool Context::setupDirectories() {
    try {
        // Diretório raiz do amb
        ambRoot_ = configManager_->getAmbRoot();
        
        // Cria diretórios necessários
        std::vector<std::filesystem::path> dirs = {
            ambRoot_,
            configManager_->getCacheDir(),
            configManager_->getLibDir(),
            configManager_->getTempDir()
        };
        
        for (const auto& dir : dirs) {
            if (!FileSystem::createDirectory(dir)) {
                Logger::error("Failed to create directory: {}", dir.string());
                return false;
            }
        }
        
        return true;
        
    } catch (const std::exception& e) {
        Logger::error("Failed to setup directories: {}", e.what());
        return false;
    }
}

std::filesystem::path Context::getProjectRoot() const {
    return projectRoot_;
}

std::filesystem::path Context::getAmbRoot() const {
    return ambRoot_;
}

std::filesystem::path Context::getCacheDir() const {
    return configManager_ ? configManager_->getCacheDir() : ambRoot_ / "cache";
}

std::filesystem::path Context::getLibDir() const {
    return configManager_ ? configManager_->getLibDir() : ambRoot_ / "lib";
}

bool Context::isInsideProject() const {
    return !projectRoot_.empty();
}

void Context::setVerbose(bool verbose) {
    verbose_ = verbose;
    if (verbose) {
        Logger::setLevel(Logger::Level::DEBUG);
    }
}

bool Context::isVerbose() const {
    return verbose_;
}

void Context::setDryRun(bool dryRun) {
    dryRun_ = dryRun;
    if (dryRun) {
        Logger::info("DRY RUN MODE - No changes will be made");
    }
}

bool Context::isDryRun() const {
    return dryRun_;
}

std::optional<std::filesystem::path> Context::findFileInPath(
    const std::string& filename
) const {
    // TODO: Implementar busca no PATH
    (void)filename;
    return std::nullopt;
}

} // namespace amb