#include "core/command.hpp"
#include "utils/logger.hpp"

namespace amb {

// CommandFactory implementation
CommandFactory& CommandFactory::instance() {
    static CommandFactory instance;
    return instance;
}

void CommandFactory::registerCommand(const std::string& name, CommandCreator creator) {
    if (exists(name)) {
        Logger::warning("Command '{}' already registered, overwriting", name);
    }
    creators_[name] = creator;
}

std::unique_ptr<Command> CommandFactory::create(const std::string& name) {
    auto it = creators_.find(name);
    if (it == creators_.end()) {
        return nullptr;
    }
    return it->second();
}

std::vector<std::string> CommandFactory::listCommands() const {
    std::vector<std::string> commands;
    for (const auto& [name, _] : creators_) {
        commands.push_back(name);
    }
    return commands;
}

bool CommandFactory::exists(const std::string& name) const {
    return creators_.find(name) != creators_.end();
}

} // namespace amb