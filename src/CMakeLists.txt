# src/CMakeLists.txt - VERSÃO CORRIGIDA

# Subdiretórios
add_subdirectory(core)
add_subdirectory(cli)
add_subdirectory(utils)
add_subdirectory(commands)

# Main executable
add_executable(amb
    main.cpp
)

target_include_directories(amb PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(amb
    amb_core
    amb_cli
    amb_utils
    amb_commands
)

# Aplicar warnings APÓS criar o target
if(COMMAND set_project_warnings)
    set_project_warnings(amb)
    set_project_warnings(amb_core)
    set_project_warnings(amb_cli)
    set_project_warnings(amb_utils)
    set_project_warnings(amb_commands)
endif()

# Install target
install(TARGETS amb DESTINATION bin)