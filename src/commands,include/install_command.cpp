#include "commands/install_command.hpp"
#include "core/context.hpp"
#include "utils/logger.hpp"
#include <iostream>

namespace amb {

InstallCommand::InstallCommand(std::shared_ptr<Context> ctx) 
    : ctx_(std::move(ctx)) {}

int InstallCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "Error: Package name required\n";
        std::cerr << "Usage: " << usage() << "\n";
        return 1;
    }
    
    std::string package = args[0];
    std::string version = "latest";
    
    // Parse package@version
    size_t atPos = package.find('@');
    if (atPos != std::string::npos) {
        version = package.substr(atPos + 1);
        package = package.substr(0, atPos);
    }
    
    Logger::info("Would install package: {}@{}", package, version);
    
    if (ctx_->isDryRun()) {
        Logger::info("[DRY RUN] Package would be installed to:");
        Logger::info("[DRY RUN]   ambar_modules/lib/{}/{}/", package, version);
        return 0;
    }
    
    // TODO: Implement actual installation
    Logger::warning("Install command not yet implemented");
    
    return 0;
}

std::string InstallCommand::description() const {
    return "Install a package";
}

std::string InstallCommand::usage() const {
    return "<package>[@<version>]";
}

std::string InstallCommand::example() const {
    return "amb install math_utils@1.0.0";
}

bool InstallCommand::requiresProject() const {
    return false; // Can install globally too
}

} // namespace amb