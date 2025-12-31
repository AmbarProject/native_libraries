#pragma once

#include "core/command.hpp"
#include <memory>
#include <string>

namespace amb {

class Context;

// Base implementation for commands
class BaseCommand : public Command {
public:
    explicit BaseCommand(Context* ctx = nullptr) : ctx_(ctx) {}
    virtual ~BaseCommand() = default;
    
    // Command interface implementation
    int execute(const std::vector<std::string>& args) override;
    virtual std::string usage() const override { return "[options]"; }
    
    // Validation
    virtual bool validateArgs(const std::vector<std::string>& args);
    
    // Helpers
    void showUsage() const;
    void showError(const std::string& message) const;
    
protected:
    Context* ctx_ = nullptr;
    
    virtual int run(const std::vector<std::string>& args) = 0;
};

// Concrete commands

class InstallCommand : public BaseCommand {
public:
    static constexpr const char* COMMAND_NAME = "install";
    
    std::string name() const override { return COMMAND_NAME; }
    std::string description() const override { return "Install packages"; }
    std::string usage() const override { return "<package>[@<version>]"; }
    std::string example() const override { return "amb install math_utils@1.0.0"; }
    
protected:
    int run(const std::vector<std::string>& args) override;
};

class RemoveCommand : public BaseCommand {
public:
    static constexpr const char* COMMAND_NAME = "remove";
    
    std::string name() const override { return COMMAND_NAME; }
    std::string description() const override { return "Remove packages"; }
    std::string usage() const override { return "<package>"; }
    std::string example() const override { return "amb remove math_utils"; }
    
protected:
    int run(const std::vector<std::string>& args) override;
};

class ListCommand : public BaseCommand {
public:
    static constexpr const char* COMMAND_NAME = "list";
    
    std::string name() const override { return COMMAND_NAME; }
    std::string description() const override { return "List installed packages"; }
    std::string usage() const override { return "[--global]"; }
    std::string example() const override { return "amb list --global"; }
    
protected:
    int run(const std::vector<std::string>& args) override;
};

class SearchCommand : public BaseCommand {
public:
    static constexpr const char* COMMAND_NAME = "search";
    
    std::string name() const override { return COMMAND_NAME; }
    std::string description() const override { return "Search for packages"; }
    std::string usage() const override { return "<query>"; }
    std::string example() const override { return "amb search math"; }
    
protected:
    int run(const std::vector<std::string>& args) override;
};

class PublishCommand : public BaseCommand {
public:
    static constexpr const char* COMMAND_NAME = "publish";
    
    std::string name() const override { return COMMAND_NAME; }
    std::string description() const override { return "Publish a package"; }
    std::string usage() const override { return "[<path>]"; }
    std::string example() const override { return "amb publish ."; }
    
protected:
    int run(const std::vector<std::string>& args) override;
};

class UpdateCommand : public BaseCommand {
public:
    static constexpr const char* COMMAND_NAME = "update";
    
    std::string name() const override { return COMMAND_NAME; }
    std::string description() const override { return "Update packages"; }
    std::string usage() const override { return "[<package>]"; }
    std::string example() const override { return "amb update math_utils"; }
    
protected:
    int run(const std::vector<std::string>& args) override;
};

class InitCommand : public BaseCommand {
public:
    static constexpr const char* COMMAND_NAME = "init";
    
    std::string name() const override { return COMMAND_NAME; }
    std::string description() const override { return "Initialize a new project"; }
    std::string usage() const override { return "[<name>]"; }
    std::string example() const override { return "amb init my_project"; }
    
protected:
    int run(const std::vector<std::string>& args) override;
};

} // namespace amb