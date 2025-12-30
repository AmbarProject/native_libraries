#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

namespace amb {

class Context;

// Interface base para todos os comandos
class Command {
public:
    virtual ~Command() = default;
    
    // Executa o comando
    virtual int execute(const std::vector<std::string>& args) = 0;
    
    // Retorna descrição do comando
    virtual std::string description() const = 0;
    
    // Retorna uso do comando
    virtual std::string usage() const = 0;
    
    // Retorna exemplo de uso
    virtual std::string example() const { return ""; }
    
    // Retorna se o comando requer projeto
    virtual bool requiresProject() const { return false; }
    
    // Retorna se o comando pode ser executado globalmente
    virtual bool canRunGlobally() const { return true; }
};

// Factory para criar comandos
class CommandFactory {
public:
    using CommandCreator = std::function<std::unique_ptr<Command>()>;
    
    static CommandFactory& instance();
    
    // Registra um comando
    void registerCommand(const std::string& name, CommandCreator creator);
    
    // Cria um comando
    std::unique_ptr<Command> create(const std::string& name);
    
    // Lista todos os comandos registrados
    std::vector<std::string> listCommands() const;
    
    // Verifica se comando existe
    bool exists(const std::string& name) const;
    
    // Obtém descrição do comando
    std::string getDescription(const std::string& name) const;
    
private:
    CommandFactory() = default;
    
    struct CommandInfo {
        CommandCreator creator;
        std::string description;
    };
    
    std::map<std::string, CommandInfo> registry_;
};

} // namespace amb