#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

namespace amb {

class Context;

// Base command interface
class Command {
public:
    virtual ~Command() = default;
    
    virtual int execute(const std::vector<std::string>& args) = 0;
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
    virtual std::string usage() const = 0;
    virtual std::string example() const { return ""; }
};

// Command factory
class CommandFactory {
public:
    using CommandCreator = std::function<std::unique_ptr<Command>()>;
    
    static CommandFactory& instance();
    
    void registerCommand(const std::string& name, CommandCreator creator);
    std::unique_ptr<Command> create(const std::string& name);
    std::vector<std::string> listCommands() const;
    bool exists(const std::string& name) const;
    
    template<typename T>
    void registerCommand() {
        registerCommand(T::COMMAND_NAME, []() {
            return std::make_unique<T>();
        });
    }
    
private:
    CommandFactory() = default;
    std::map<std::string, CommandCreator> creators_;
};

} // namespace amb