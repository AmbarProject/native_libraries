#include "cli/cli_handler.hpp"
#include "core/context.hpp"
#include "core/command.hpp"
#include "utils/logger.hpp"
#include "commands/help_command.hpp"
#include "commands/install_command.hpp"
#include "commands/remove_command.hpp"
#include "commands/list_command.hpp"
#include "commands/search_command.hpp"
#include "commands/publish_command.hpp"
#include "commands/update_command.hpp"
#include "commands/init_command.hpp"

#include <iostream>
#include <iomanip>

namespace amb {

CLIHandler::CLIHandler(std::shared_ptr<Context> ctx) 
    : ctx_(std::move(ctx)) {
    
    Logger::debug("CLIHandler initialized");
}

CLIHandler::~CLIHandler() = default;

int CLIHandler::run(int argc, char* argv[]) {
    try {
        // Parse arguments
        auto args = parseArgs(argc, argv);
        
        if (args.empty()) {
            showHelp();
            return 0;
        }
        
        // Process global options first
        std::vector<std::string> remainingArgs;
        processGlobalOptions(args, remainingArgs);
        
        if (remainingArgs.empty()) {
            // Only global options were provided
            return 0;
        }
        
        // Extract command
        std::string command = remainingArgs[0];
        std::vector<std::string> commandArgs(
            remainingArgs.begin() + 1, 
            remainingArgs.end()
        );
        
        // Handle built-in commands
        if (command == "help" || command == "--help" || command == "-h") {
            showHelp();
            return 0;
        }
        
        if (command == "version" || command == "--version" || command == "-v") {
            showVersion();
            return 0;
        }
        
        // Execute regular command
        return executeCommand(command, commandArgs);
        
    } catch (const std::exception& e) {
        Logger::error("CLI error: {}", e.what());
        return 1;
    }
}

std::vector<std::string> CLIHandler::parseArgs(int argc, char* argv[]) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    return args;
}

void CLIHandler::processGlobalOptions(
    const std::vector<std::string>& args,
    std::vector<std::string>& remainingArgs
) {
    for (size_t i = 0; i < args.size(); ++i) {
        const auto& arg = args[i];
        
        if (arg == "--verbose" || arg == "-V") {
            ctx_->setVerbose(true);
        } else if (arg == "--dry-run" || arg == "-n") {
            ctx_->setDryRun(true);
        } else if (arg == "--no-color") {
            // TODO: Implement color output control
        } else {
            // Not a global option, add to remaining args
            remainingArgs.push_back(arg);
        }
    }
}

int CLIHandler::executeCommand(
    const std::string& command,
    const std::vector<std::string>& args
) {
    try {
        Logger::debug("Executing command: {} with {} args", 
                     command, args.size());
        
        // Check if command exists
        auto& factory = CommandFactory::instance();
        if (!factory.exists(command)) {
            Logger::error("Unknown command: {}", command);
            std::cerr << "Error: Unknown command '" << command << "'\n\n";
            showHelp();
            return 1;
        }
        
        // Create and execute command
        auto cmd = factory.create(command);
        if (!cmd) {
            Logger::error("Failed to create command: {}", command);
            return 1;
        }
        
        // Check if command requires project context
        if (cmd->requiresProject() && !ctx_->isInsideProject()) {
            Logger::error("Command '{}' requires a project", command);
            std::cerr << "Error: This command must be run inside an Ambar project\n";
            std::cerr << "Run 'amb init' to create a new project\n";
            return 1;
        }
        
        return cmd->execute(args);
        
    } catch (const std::exception& e) {
        Logger::error("Command execution failed: {}", e.what());
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}

void CLIHandler::showHelp() const {
    std::cout << "Ambar Package Manager (amb) v0.1.0\n\n";
    std::cout << "Usage: amb <command> [options] [arguments]\n\n";
    
    std::cout << "Global Options:\n";
    std::cout << "  -V, --verbose     Enable verbose output\n";
    std::cout << "  -n, --dry-run     Show what would be done without making changes\n";
    std::cout << "  --no-color        Disable colored output\n";
    std::cout << "  -h, --help        Show this help message\n";
    std::cout << "  -v, --version     Show version information\n\n";
    
    std::cout << "Commands:\n";
    
    auto& factory = CommandFactory::instance();
    auto commands = factory.listCommands();
    
    // Calculate max command length for formatting
    size_t maxLen = 0;
    for (const auto& cmd : commands) {
        maxLen = std::max(maxLen, cmd.length());
    }
    
    // Display commands
    for (const auto& cmd : commands) {
        std::string description = factory.getDescription(cmd);
        std::cout << "  " << std::left << std::setw(static_cast<int>(maxLen + 2))
                  << cmd << description << "\n";
    }
    
    std::cout << "\n";
    std::cout << "Run 'amb help <command>' for more information on a specific command.\n";
}

void CLIHandler::showCommandHelp(const std::string& command) const {
    auto& factory = CommandFactory::instance();
    if (!factory.exists(command)) {
        std::cerr << "Error: Unknown command '" << command << "'\n";
        return;
    }
    
    auto cmd = factory.create(command);
    if (!cmd) {
        std::cerr << "Error: Failed to create command '" << command << "'\n";
        return;
    }
    
    std::cout << "Command: " << command << "\n\n";
    std::cout << "Description:\n";
    std::cout << "  " << cmd->description() << "\n\n";
    
    std::cout << "Usage:\n";
    std::cout << "  amb " << command << " " << cmd->usage() << "\n\n";
    
    if (!cmd->example().empty()) {
        std::cout << "Example:\n";
        std::cout << "  " << cmd->example() << "\n\n";
    }
    
    if (cmd->requiresProject()) {
        std::cout << "Note: This command requires a project context.\n";
    }
}

void CLIHandler::showVersion() const {
    std::cout << "amb version 0.1.0\n";
    std::cout << "Ambar Package Manager\n";
    std::cout << "Protocol version: 1.0\n";
}

} // namespace amb