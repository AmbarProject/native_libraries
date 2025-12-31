#pragma once

#include <stdexcept>
#include <string>
#include <system_error>
#include <filesystem>

namespace amb {

class Error : public std::runtime_error {
public:
    explicit Error(const std::string& message) 
        : std::runtime_error(message) {}
    
    explicit Error(const char* message) 
        : std::runtime_error(message) {}
};

class ConfigError : public Error {
public:
    explicit ConfigError(const std::string& message) 
        : Error("Configuration error: " + message) {}
    
    explicit ConfigError(const std::filesystem::filesystem_error& e)
        : Error("Configuration error: " + std::string(e.what())) {}
};

class CommandError : public Error {
public:
    explicit CommandError(const std::string& message) 
        : Error("Command error: " + message) {}
    
    explicit CommandError(const std::string& command, const std::string& message)
        : Error("Command '" + command + "' error: " + message) {}
};

class FilesystemError : public Error {
public:
    explicit FilesystemError(const std::string& message) 
        : Error("Filesystem error: " + message) {}
    
    explicit FilesystemError(const std::filesystem::filesystem_error& e)
        : Error("Filesystem error: " + std::string(e.what())) {}
};

class NetworkError : public Error {
public:
    explicit NetworkError(const std::string& message) 
        : Error("Network error: " + message) {}
    
    explicit NetworkError(const std::system_error& e)
        : Error("Network error: " + std::string(e.what())) {}
};

class PackageError : public Error {
public:
    explicit PackageError(const std::string& message) 
        : Error("Package error: " + message) {}
    
    explicit PackageError(const std::string& package, const std::string& message)
        : Error("Package '" + package + "' error: " + message) {}
};

} // namespace amb