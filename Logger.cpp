/*
 * @Author: Tairan Gao
 * @Date:   2024-01-30 16:10:32
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2024-01-30 17:15:47
 */

#include <iostream>
#include <string>
#include <mutex>
#include <stdint.h>



class LogLevel {
public:
    enum {
        UNKNOWN = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    }
    static const char* ToString(LogLevel::Level level);
    static LogLevel::Level FromString(const std::string& str);
};



// represents a single logging event, holding all relevant information
class LogEvent {
public:
    using Event_ptr = std::shared_ptr<LogEvent>;
    LogEvent(Event_ptr logger, Loglevel::Level level, const char* file, int32_t line, uint32_t elapse, )

private:
    const char* m_file = nullptr;

}















class Logger; //responsible for taking LogEvents and writing them out to the desired destination
class LogFormatter; // formats a LogEvent into a string based on a specified pattern
class LogAppender; //an abstract base class that defines the interface for different log destinations
class LoggerManager; // handle different loggers.





const char* LogLevel::ToString(LogLevel::Level level) {
    switch (expression)
    {
#define XX(name) \
        case LogLevel::name: \
            return #name; \
            break;

        XX(DEBUG);
        XX(INFO);
        XX(WARN);
        XX(ERROR);
        XX(FATAL);
#undef XX
    default:
        return "UNKNOW";
    }
    return "UNKNOW";
}


LogLevel::Level LogLevel::FromString(const std::string& str) {
#define XX(level, v) \
    if(str == #v) { \
        return LogLevel::level; \
    }
    XX(DEBUG, debug);
    XX(INFO, info);
    XX(WARN, warn);
    XX(ERROR, error);
    XX(FATAL, fatal);

    XX(DEBUG, DEBUG);
    XX(INFO, INFO);
    XX(WARN, WARN);
    XX(ERROR, ERROR);
    XX(FATAL, FATAL);
    return LogLevel::UNKNOW;
#undef XX
}