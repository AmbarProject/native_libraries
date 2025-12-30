#include "amb/version.hpp"
#include "core/context.hpp"
#include "cli/cli_handler.hpp"
#include "utils/logger.hpp"
#include "utils/error.hpp"

#include <iostream>
#include <cstdlib>
#include <memory>

int main(int argc, char* argv[]) {
    using namespace amb;
    
    try {
        // Inicializa logger
        Logger::init();
        Logger::info("Starting Ambar Package Manager v{}", 
                     AMB_VERSION.toString());
        
        // Cria e inicializa contexto
        auto ctx = std::make_shared<Context>();
        if (!ctx->initialize()) {
            Logger::error("Failed to initialize context");
            return EXIT_FAILURE;
        }
        
        // Processa linha de comando
        CLIHandler cli(ctx);
        return cli.run(argc, argv);
        
    } catch (const Error& e) {
        Logger::error("Error: {}", e.what());
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        Logger::error("Unexpected error: {}", e.what());
        return EXIT_FAILURE;
    } catch (...) {
        Logger::error("Unknown error occurred");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}