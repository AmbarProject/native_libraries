# CLI component
add_library(amb_cli STATIC
    cli_handler.cpp
)

target_include_directories(amb_cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(amb_cli amb_core)