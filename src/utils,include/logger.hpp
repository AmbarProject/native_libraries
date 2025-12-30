#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <mutex>
#include <memory>

namespace amb {

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };
    
    // Singleton access
    static Logger& instance();
    
    // Configuration
    void setLevel(Level level);
    void setQuiet(bool quiet);
    void setUseColors(bool useColors);
    
    // Logging methods
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void fatal(const std::string& message);
    
    // Convenience static methods
    template<typename... Args>
    static void debug(const std::string& format, Args&&... args) {
        instance().log(Level::DEBUG, formatString(format, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    static void info(const std::string& format, Args&&... args) {
        instance().log(Level::INFO, formatString(format, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    static void warning(const std::string& format, Args&&... args) {
        instance().log(Level::WARNING, formatString(format, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    static void error(const std::string& format, Args&&... args) {
        instance().log(Level::ERROR, formatString(format, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    static void fatal(const std::string& format, Args&&... args) {
        std::string message = formatString(format, std::forward<Args>(args)...);
        instance().log(Level::FATAL, message);
        throw std::runtime_error(message);
    }
    
private:
    Logger();
    ~Logger() = default;
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    void log(Level level, const std::string& message);
    std::string levelToString(Level level) const;
    std::string levelToColor(Level level) const;
    std::string getTimestamp() const;
    
    template<typename... Args>
    static std::string formatString(const std::string& format, Args&&... args) {
        std::ostringstream oss;
        formatStringImpl(oss, format, std::forward<Args>(args)...);
        return oss.str();
    }
    
    template<typename T, typename... Args>
    static void formatStringImpl(std::ostringstream& oss, 
                                const std::string& format, 
                                T&& first, 
                                Args&&... rest) {
        size_t pos = format.find("{}");
        if (pos == std::string::npos) {
            oss << format;
            return;
        }
        
        oss << format.substr(0, pos);
        oss << std::forward<T>(first);
        formatStringImpl(oss, format.substr(pos + 2), std::forward<Args>(rest)...);
    }
    
    static void formatStringImpl(std::ostringstream& oss, const std::string& format) {
        oss << format;
    }
    
    Level currentLevel_;
    bool quiet_;
    bool useColors_;
    mutable std::mutex mutex_;
};

} // namespace amb