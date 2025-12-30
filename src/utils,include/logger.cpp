#include "utils/logger.hpp"
#include <chrono>
#include <iomanip>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

namespace amb {

Logger::Logger() 
    : currentLevel_(Level::INFO)
    , quiet_(false)
    , useColors_(true) {
    
#ifdef _WIN32
    // Enable ANSI escape codes on Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

void Logger::setLevel(Level level) {
    std::lock_guard<std::mutex> lock(mutex_);
    currentLevel_ = level;
}

void Logger::setQuiet(bool quiet) {
    std::lock_guard<std::mutex> lock(mutex_);
    quiet_ = quiet;
}

void Logger::setUseColors(bool useColors) {
    std::lock_guard<std::mutex> lock(mutex_);
    useColors_ = useColors;
}

void Logger::debug(const std::string& message) {
    log(Level::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(Level::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(Level::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(Level::ERROR, message);
}

void Logger::fatal(const std::string& message) {
    log(Level::FATAL, message);
}

void Logger::log(Level level, const std::string& message) {
    if (quiet_ || level < currentLevel_) {
        return;
    }
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::ostream& stream = (level >= Level::ERROR) ? std::cerr : std::cout;
    
    if (useColors_) {
        stream << levelToColor(level);
    }
    
    stream << "[" << getTimestamp() << "] ";
    stream << "[" << levelToString(level) << "] ";
    stream << message;
    
    if (useColors_) {
        stream << "\033[0m";
    }
    
    stream << std::endl;
}

std::string Logger::levelToString(Level level) const {
    switch (level) {
        case Level::DEBUG:   return "DEBUG";
        case Level::INFO:    return "INFO";
        case Level::WARNING: return "WARN";
        case Level::ERROR:   return "ERROR";
        case Level::FATAL:   return "FATAL";
        default:             return "UNKNOWN";
    }
}

std::string Logger::levelToColor(Level level) const {
    if (!useColors_) {
        return "";
    }
    
    switch (level) {
        case Level::DEBUG:   return "\033[36m";  // Cyan
        case Level::INFO:    return "\033[32m";  // Green
        case Level::WARNING: return "\033[33m";  // Yellow
        case Level::ERROR:   return "\033[31m";  // Red
        case Level::FATAL:   return "\033[35m";  // Magenta
        default:             return "\033[0m";   // Reset
    }
}

std::string Logger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;
    
    std::tm tmBuf;
#ifdef _WIN32
    localtime_s(&tmBuf, &time);
#else
    localtime_r(&time, &tmBuf);
#endif
    
    std::ostringstream oss;
    oss << std::put_time(&tmBuf, "%H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    
    return oss.str();
}

} // namespace amb