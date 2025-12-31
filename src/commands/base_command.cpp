#include "commands/base_command.hpp"
#include "core/context.hpp"
#include "utils/logger.hpp"
#include <iostream>

namespace amb {

int BaseCommand::execute(const std::vector<std::string>& args) {
    try {
        if (!validateArgs(args)) {
            showUsage();
            return 1;
        }
        
        return run(args);
        
    } catch (const std::exception& e) {
        showError(e.what());
        return 1;
    }
}

bool BaseCommand::validateArgs(const std::vector<std::string>& args) {
    // Default validation: accept any number of arguments
    return true;
}

void BaseCommand::showUsage() const {
    std::cout << "Usage: amb " << name() << " " << usage() << "\n";
    
    if (!example().empty()) {
        std::cout << "Example: " << example() << "\n";
    }
}

void BaseCommand::showError(const std::string& message) const {
    Logger::error("{}: {}", name(), message);
    std::cerr << "Error: " << message << "\n";
}

} // namespace amb