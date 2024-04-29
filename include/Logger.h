//
// Created by wen on 2023-12-30.
//

#ifndef _LOGGER_H
#define _LOGGER_H
// Logger.h


#if defined(_WIN32) || defined(_WIN64)
    // Windows platform
    #ifdef THREADPOOL_EXPORTS
        #define THREADPOOL_API __declspec(dllexport)
    #else
        #define THREADPOOL_API __declspec(dllimport)
    #endif
#else
    // not Windows platform, assume Unix-like platform（e.g. Linux）
    #if __GNUC__ >= 4
        #define THREADPOOL_API __attribute__ ((visibility ("default")))
    #else
        #define THREADPOOL_API
    #endif
#endif

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <chrono>
#include <iomanip>
#include <cstdarg>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class THREADPOOL_API Logger {
public:
//    Logger();
    explicit Logger(LogLevel level = LogLevel::INFO);
    void SetOutput(std::ostream* os);
    void SetLevel(LogLevel level);
    void Log(const std::string& message, LogLevel level,
             const char* file, int line, const char* func);
    void Log(LogLevel level, const char* file, int line, const char* func, const char* format, ...);

    template<typename... Args>
    inline void LogDebug(const char* file, int line, const char* func, const char* format, Args... args) {
        Log(LogLevel::DEBUG, file, line, func, format, args...);
    }

    template<typename... Args>
    inline void LogInfo(const char* file, int line, const char* func, const char* format, Args... args) {
        Log(LogLevel::INFO, file, line, func, format, args...);
    }

    template<typename... Args>
    inline void LogWarning(const char* file, int line, const char* func, const char* format, Args... args) {
        Log(LogLevel::WARNING, file, line, func, format, args...);
    }

    template<typename... Args>
    inline void LogError(const char* file, int line, const char* func, const char* format, Args... args) {
        Log(LogLevel::ERROR, file, line, func, format, args...);
    }

    template<typename... Args>
    inline void LogFatal(const char* file, int line, const char* func, const char* format, Args... args) {
        Log(LogLevel::FATAL, file, line, func, format, args...);
    }

    // template<typename... Args>
    // inline void LogDebug(const char* format, Args... args) {
    //     Log(LogLevel::DEBUG, __FILE__, __LINE__, __FUNCTION__, format, args...);
    // }

    // template<typename... Args>
    // inline void LogInfo(const char* format, Args... args) {
    //     Log(LogLevel::INFO, __FILE__, __LINE__, __FUNCTION__, format, args...);
    // }

    // template<typename... Args>
    // inline void LogWarning(const char* format, Args... args) {
    //     Log(LogLevel::WARNING, __FILE__, __LINE__, __FUNCTION__, format, args...);
    // }

    // template<typename... Args>
    // inline void LogError(const char* format, Args... args) {
    //     Log(LogLevel::ERROR, __FILE__, __LINE__, __FUNCTION__, format, args...);
    // }

    // template<typename... Args>
    // inline void LogFatal(const char* format, Args... args) {
    //     Log(LogLevel::FATAL, __FILE__, __LINE__, __FUNCTION__, format, args...);
    // }
private:
    std::ostream* out_stream;
    std::mutex mu;
    LogLevel level;
    // ANSI color codes
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";     // ERROR
    const std::string GREEN = "\033[32m";   // INFO
    const std::string YELLOW = "\033[33m";  // WARNING
    const std::string BLUE = "\033[34m";    // DEBUG
    const std::string PURPLE = "\033[35m";  // FATAL
    LogLevel currentLevel;
};

//#define LOG(logger, level, message) logger.Log(message, level, __FILE__, __LINE__, __FUNCTION__)
// Generic LOG macro definition
#define LOG(logger, level, message) logger.Log(message, level, __FILE__, __LINE__, __FUNCTION__)

#define LOG_DEBUG(format, ...) this->LogDebug(__FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) this->LogInfo(__FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) this->LogWarning(__FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) this->LogError(__FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) this->LogFatal(__FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

// Specific level macros based on generic LOG macro definition
//#define LOG_INFO(logger, message) LOG(logger, LogLevel::INFO, message)
//#define LOG_WARNING(logger, message) LOG(logger, LogLevel::WARNING, message)
//#define LOG_ERROR(logger, message) LOG(logger, LogLevel::ERROR, message)
// #define LOG_DEBUG(message) LOG(logger, LogLevel::DEBUG, message)
// #define LOG_INFO(message) LOG(logger, LogLevel::INFO, message)
// #define LOG_WARNING(message) LOG(logger, LogLevel::WARNING, message)
// #define LOG_ERROR(message) LOG(logger, LogLevel::ERROR, message)
// #define LOG_FATAL(message) LOG(logger, LogLevel::FATAL, message)
//#define LOGDEBUG(logger, format, ...) logger.Log(LogLevel::DEBUG, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
//#define LOGINFO(logger, format, ...) logger.Log(LogLevel::INFO, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
//#define LOGWARNING(logger, format, ...) logger.Log(LogLevel::WARNING, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
//#define LOGERROR(logger, format, ...) logger.Log(LogLevel::ERROR, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
//#define LOGFATAL(logger, format, ...) logger.Log(LogLevel::FATAL, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGDEBUG(format, ...) logger.Log(LogLevel::DEBUG, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGINFO(format, ...) logger.Log(LogLevel::INFO, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGWARNING(format, ...) logger.Log(LogLevel::WARNING, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGERROR(format, ...) logger.Log(LogLevel::ERROR, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGFATAL(format, ...) logger.Log(LogLevel::FATAL, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

#endif //MEMORYPOOL_LOGGER_H