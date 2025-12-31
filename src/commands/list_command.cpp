#include "commands/base_command.hpp"
#include "utils/logger.hpp"
#include "utils/filesystem.hpp"
#include <iostream>

namespace amb {

int ListCommand::run(const std::vector<std::string>& args) {
    bool listGlobal = false;
    
    // Parse arguments
    for (const auto& arg : args) {
        if (arg == "--global" || arg == "-g") {
            listGlobal = true;
        } else {
            Logger::warning("Unknown argument: {}", arg);
        }
    }
    
    if (listGlobal) {
        Logger::info("Listing globally installed packages...");
        // TODO: List packages from ~/.ambar/lib/
    } else {
        Logger::info("Listing locally installed packages...");
        
        // Check if we're in a project
        if (!ctx_ || !ctx_->isInsideProject()) {
            showError("Not in an Ambar project directory");
            std::cout << "Run this command inside a project directory,\n";
            std::cout << "or use --global to list global packages\n";
            return 1;
        }
        
        // List packages from ambar_modules/lib/
        auto projectRoot = ctx_->getProjectRoot();
        if (projectRoot) {
            auto libDir = *projectRoot / "ambar_modules" / "lib";
            
            if (FileSystem::isDirectory(libDir)) {
                auto packages = FileSystem::listDirectories(libDir);
                
                if (packages.empty()) {
                    std::cout << "No packages installed locally\n";
                } else {
                    std::cout << "Locally installed packages:\n";
                    for (const auto& pkg : packages) {
                        std::cout << "  " << FileSystem::filename(pkg) << "\n";
                        
                        // List versions
                        auto versions = FileSystem::listDirectories(pkg);
                        for (const auto& ver : versions) {
                            std::cout << "    " << FileSystem::filename(ver) << "\n";
                        }
                    }
                }
            } else {
                std::cout << "No packages installed locally\n";
            }
        }
    }
    
    return 0;
}

} // namespace amb