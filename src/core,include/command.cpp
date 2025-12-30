#include "core/command.hpp"
#include "utils/logger.hpp"

namespace amb {

// Singleton implementation
CommandFactory& CommandFactory::instance() {
    static CommandFactory instance;
    return instance;
}

void CommandFactory::registerCommand(
    const std::string& name, 
    CommandCreator creator
) {
    // Create temporary command to get description
    auto cmd = creator();
    registry_[name] = {creator, cmd->description()};
    Logger::debug("Registered command: {}", name);
}

std::unique_ptr<Command> CommandFactory::create(const std::string& name) {
    auto it = registry_.find(name);
    if (it == registry_.end()) {
        Logger::error("Command not found: {}", name);
        return nullptr;
    }
    
    try {
        return it->second.creator();
    } catch (const std::exception& e) {
        Logger::error("Failed to create command {}: {}", name, e.what());
        return nullptr;
    }
}

std::vector<std::string> CommandFactory::listCommands() const {
    std::vector<std::string> commands;
    for (const auto& [name, _] : registry_) {
        commands.push_back(name);
    }
    return commands;
}

bool CommandFactory::exists(const std::string& name) const {
    return registry_.find(name) != registry_.end();
}

std::string CommandFactory::getDescription(const std::string& name) const {
    auto it = registry_.find(name);
    if (it == registry_.end()) {
        return "";
    }
    return it->second.description;
}

} // namespace amb