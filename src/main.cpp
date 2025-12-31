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
        // Initialize logger first
        Logger::init();
        Logger::info("Ambar Package Manager v{}", 
                     AMB_VERSION.toString());
        
        // Create and initialize context
        auto ctx = std::make_shared<Context>();
        if (!ctx->initialize()) {
            Logger::error("Failed to initialize context");
            return EXIT_FAILURE;
        }
        
        // Parse command line
        CLIHandler cli(ctx);
        return cli.run(argc, argv);
        
    } catch (const Error& e) {
        Logger::error("Error: {}", e.what());
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        Logger::error("Unexpected error: {}", e.what());
        return EXIT_FAILURE;
    } catch (...) {
        Logger::error("Unknown fatal error");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}