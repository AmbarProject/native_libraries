#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace amb {

class Context;
class Command;

struct CLIResult {
    int exitCode = 0;
    std::string message;
    bool shouldExit = false;
};

class CLIHandler {
public:
    explicit CLIHandler(std::shared_ptr<Context> ctx);
    ~CLIHandler();
    
    // Executa handler com argumentos
    int run(int argc, char* argv[]);
    
    // Processa comandos
    CLIResult processCommand(const std::string& command, 
                           const std::vector<std::string>& args);
    
    // Mostra ajuda
    void showHelp() const;
    void showCommandHelp(const std::string& command) const;
    
    // Mostra versão
    void showVersion() const;
    
private:
    // Processa argumentos
    std::vector<std::string> parseArgs(int argc, char* argv[]);
    
    // Extrai opções globais
    void processGlobalOptions(const std::vector<std::string>& args,
                            std::vector<std::string>& remainingArgs);
    
    // Executa comando
    int executeCommand(const std::string& command,
                      const std::vector<std::string>& args);
    
    // Comandos internos
    CLIResult handleHelp(const std::vector<std::string>& args);
    CLIResult handleVersion(const std::vector<std::string>& args);
    
    std::shared_ptr<Context> ctx_;
    std::unordered_map<std::string, std::unique_ptr<Command>> commandCache_;
};

} // namespace amb