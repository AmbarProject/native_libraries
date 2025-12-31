#include "cli/cli_handler.hpp"
#include "core/context.hpp"
#include "core/command.hpp"
#include "commands/base_command.hpp"
#include "utils/logger.hpp"

#include <iostream>
#include <algorithm>

namespace amb {

CLIHandler::CLIHandler(std::shared_ptr<Context> ctx) : ctx_(ctx) {
    // Register commands
    CommandFactory::instance().registerCommand<InstallCommand>();
    CommandFactory::instance().registerCommand<RemoveCommand>();
    CommandFactory::instance().registerCommand<ListCommand>();
    CommandFactory::instance().registerCommand<SearchCommand>();
    CommandFactory::instance().registerCommand<PublishCommand>();
    CommandFactory::instance().registerCommand<UpdateCommand>();
    CommandFactory::instance().registerCommand<InitCommand>();
}

CLIHandler::~CLIHandler() = default;

int CLIHandler::run(int argc, char* argv[]) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    return run(args);
}

int CLIHandler::run(const std::vector<std::string>& rawArgs) {
    try {
        auto parsed = parseArgs(rawArgs);
        
        // Handle global options
        if (parsed.verbose) {
            ctx_->setVerbose(true);
            Logger::setLevel(LogLevel::DEBUG);
        }
        
        // Handle help and version
        if (parsed.showHelp && parsed.command.empty()) {
            showHelp();
            return 0;
        }
        
        if (parsed.showVersion) {
            showVersion();
            return 0;
        }
        
        // Execute command
        return executeCommand(parsed);
        
    } catch (const std::exception& e) {
        Logger::error("CLI error: {}", e.what());
        return 1;
    }
}

CLIHandler::ParsedArgs CLIHandler::parseArgs(const std::vector<std::string>& rawArgs) const {
    ParsedArgs parsed;
    
    if (rawArgs.empty()) {
        parsed.showHelp = true;
        return parsed;
    }
    
    size_t i = 0;
    
    // Parse global options
    while (i < rawArgs.size()) {
        const auto& arg = rawArgs[i];
        
        if (arg == "-h" || arg == "--help") {
            parsed.showHelp = true;
        } else if (arg == "-v" || arg == "--version") {
            parsed.showVersion = true;
        } else if (arg == "--verbose") {
            parsed.verbose = true;
        } else if (arg.starts_with("-")) {
            // Unknown option
            Logger::warning("Unknown option: {}", arg);
        } else {
            // First non-option is the command
            parsed.command = arg;
            i++;
            break;
        }
        
        i++;
    }
    
    // Remaining args are command arguments
    while (i < rawArgs.size()) {
        parsed.args.push_back(rawArgs[i]);
        i++;
    }
    
    return parsed;
}

int CLIHandler::executeCommand(const ParsedArgs& parsed) {
    if (parsed.command.empty()) {
        if (parsed.showHelp) {
            showHelp();
            return 0;
        }
        Logger::error("No command specified");
        showHelp();
        return 1;
    }
    
    auto command = CommandFactory::instance().create(parsed.command);
    if (!command) {
        Logger::error("Unknown command: {}", parsed.command);
        std::cout << "\nAvailable commands:\n";
        for (const auto& cmd : CommandFactory::instance().listCommands()) {
            std::cout << "  " << cmd << "\n";
        }
        std::cout << "\nUse 'amb --help' for more information\n";
        return 1;
    }
    
    if (parsed.showHelp) {
        showCommandHelp(parsed.command);
        return 0;
    }
    
    Logger::debug("Executing command: {} with {} arguments", 
                  parsed.command, parsed.args.size());
    
    return command->execute(parsed.args);
}

void CLIHandler::showHelp() const {
    std::cout << "Ambar Package Manager (amb) v0.1.0\n\n";
    std::cout << "Usage: amb <command> [options] [arguments]\n\n";
    std::cout << "Global options:\n";
    std::cout << "  -h, --help     Show this help message\n";
    std::cout << "  -v, --version  Show version information\n";
    std::cout << "  --verbose      Enable verbose output\n\n";
    std::cout << "Commands:\n";
    
    auto commands = CommandFactory::instance().listCommands();
    std::sort(commands.begin(), commands.end());
    
    for (const auto& cmdName : commands) {
        auto cmd = CommandFactory::instance().create(cmdName);
        if (cmd) {
            std::cout << "  " << cmdName;
            std::cout << std::string(12 - cmdName.length(), ' ');
            std::cout << cmd->description() << "\n";
        }
    }
    
    std::cout << "\nFor more information on a specific command:\n";
    std::cout << "  amb <command> --help\n";
}

void CLIHandler::showVersion() const {
    std::cout << "amb version 0.1.0\n";
    std::cout << "Ambar Package Manager\n";
    std::cout << "Copyright (c) 2024 Ambar Language\n";
}

void CLIHandler::showCommandHelp(const std::string& command) const {
    auto cmd = CommandFactory::instance().create(command);
    if (!cmd) {
        Logger::error("Unknown command: {}", command);
        return;
    }
    
    std::cout << "Usage: amb " << command << " " << cmd->usage() << "\n\n";
    std::cout << cmd->description() << "\n\n";
    
    if (!cmd->example().empty()) {
        std::cout << "Example:\n";
        std::cout << "  " << cmd->example() << "\n\n";
    }
}

} // namespace amb