#pragma once

#include <memory>
#include <string>
#include <vector>

namespace amb {

class Context;
class Command;

class CLIHandler {
public:
    explicit CLIHandler(std::shared_ptr<Context> ctx);
    ~CLIHandler();
    
    int run(int argc, char* argv[]);
    int run(const std::vector<std::string>& args);
    
    // Help and info
    void showHelp() const;
    void showVersion() const;
    void showCommandHelp(const std::string& command) const;
    
private:
    struct ParsedArgs {
        std::string command;
        std::vector<std::string> args;
        bool showHelp = false;
        bool showVersion = false;
        bool verbose = false;
    };
    
    ParsedArgs parseArgs(const std::vector<std::string>& rawArgs) const;
    int executeCommand(const ParsedArgs& parsed);
    
    std::shared_ptr<Context> ctx_;
};

} // namespace amb