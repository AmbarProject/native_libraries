#include "utils/logger.hpp"
#include <chrono>
#include <iomanip>
#include <cstdlib>

namespace amb {

LogLevel Logger::currentLevel_ = LogLevel::INFO;
bool Logger::quiet_ = false;
bool Logger::initialized_ = false;
std::mutex Logger::logMutex_;

void Logger::init(LogLevel level) {
    std::lock_guard lock(logMutex_);
    currentLevel_ = level;
    initialized_ = true;
}

void Logger::setLevel(LogLevel level) {
    std::lock_guard lock(logMutex_);
    currentLevel_ = level;
}

void Logger::setQuiet(bool quiet) {
    std::lock_guard lock(logMutex_);
    quiet_ = quiet;
}

LogLevel Logger::getLevel() {
    return currentLevel_;
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::fatal(const std::string& message) {
    log(LogLevel::FATAL, message);
    std::exit(EXIT_FAILURE);
}

void Logger::log(LogLevel level, const std::string& message) {
    if (quiet_ || level < currentLevel_) {
        return;
    }
    
    std::lock_guard lock(logMutex_);
    
    std::cerr << "[" << getTimestamp() << "] ";
    std::cerr << "[" << levelToString(level) << "] ";
    std::cerr << message << std::endl;
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARN";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::FATAL:   return "FATAL";
        default:                return "UNKNOWN";
    }
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

} // namespace amb