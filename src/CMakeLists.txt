# Biblioteca principal (core)
add_library(amb_core STATIC
    core/command.cpp
    core/context.cpp
    core/version.cpp
    
    utils/logger.cpp
    utils/error.cpp
    utils/filesystem.cpp
    utils/string_utils.cpp
    
    config/config_manager.cpp
)

# Executável principal
add_executable(amb
    main.cpp
    cli/cli_handler.cpp
    cli/argument_parser.cpp
    
    commands/install_command.cpp
    commands/remove_command.cpp
    commands/list_command.cpp
    commands/search_command.cpp
    commands/publish_command.cpp
    commands/update_command.cpp
    commands/init_command.cpp
    commands/help_command.cpp
)

# Link bibliotecas
target_link_libraries(amb 
    PRIVATE 
    amb_core
)

# Propaga includes
target_include_directories(amb_core 
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(amb
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

# Propriedades do target
set_target_properties(amb PROPERTIES
    OUTPUT_NAME "amb"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Instalação (opcional)
install(TARGETS amb
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION bin
)

install(TARGETS amb_core
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/amb
    DESTINATION include
)