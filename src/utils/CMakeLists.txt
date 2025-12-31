# Utilities library
add_library(amb_utils STATIC
    logger.cpp
    error.cpp
    filesystem.cpp
)

target_include_directories(amb_utils PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

# Link system libraries for filesystem operations
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(amb_utils PRIVATE stdc++fs)
endif()