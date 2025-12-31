#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <mutex>

namespace amb {

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class Logger {
public:
    static void init(LogLevel level = LogLevel::INFO);
    static void setLevel(LogLevel level);
    static void setQuiet(bool quiet);
    static LogLevel getLevel();
    
    // Basic logging methods
    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
    static void fatal(const std::string& message);
    
    // Formatted logging (C++20 style)
    template<typename... Args>
    static void debug(const std::string& format, Args&&... args) {
        log(LogLevel::DEBUG, format_string(format, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    static void info(const std::string& format, Args&&... args) {
        log(LogLevel::INFO, format_string(format, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    static void warning(const std::string& format, Args&&... args) {
        log(LogLevel::WARNING, format_string(format, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    static void error(const std::string& format, Args&&... args) {
        log(LogLevel::ERROR, format_string(format, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    static void fatal(const std::string& format, Args&&... args) {
        log(LogLevel::FATAL, format_string(format, std::forward<Args>(args)...));
    }
    
private:
    static void log(LogLevel level, const std::string& message);
    static std::string levelToString(LogLevel level);
    static std::string getTimestamp();
    
    // Simple string formatting (replace with fmt if available)
    template<typename... Args>
    static std::string format_string(const std::string& format, Args&&... args) {
        std::string result = format;
        size_t index = 0;
        ((replace_placeholder(result, "{}", std::forward<Args>(args), index)), ...);
        return result;
    }
    
    template<typename T>
    static void replace_placeholder(std::string& str, const std::string& placeholder, 
                                    T&& value, size_t& index) {
        std::ostringstream oss;
        oss << value;
        size_t pos = str.find(placeholder, index);
        if (pos != std::string::npos) {
            str.replace(pos, placeholder.length(), oss.str());
            index = pos + oss.str().length();
        }
    }
    
    static LogLevel currentLevel_;
    static bool quiet_;
    static bool initialized_;
    static std::mutex logMutex_;
};

} // namespace amb