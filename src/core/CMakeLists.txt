# Core library
add_library(amb_core STATIC
    command.cpp
    context.cpp
)

target_include_directories(amb_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(amb_core)