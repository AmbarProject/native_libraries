# Commands library
add_library(amb_commands STATIC
    base_command.cpp
    install_command.cpp
    remove_command.cpp
    list_command.cpp
)

target_include_directories(amb_commands PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(amb_commands amb_core amb_utils)