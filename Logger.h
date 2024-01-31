/*
 * @Author: Tairan Gao
 * @Date:   2024-01-30 16:10:32
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2024-01-30 21:26:13
 */
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdint.h>

#include <mutex>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>


class Logger;
class LogAppender;

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
    using ptr = std::shared_ptr<LogEvent>;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
        , const char* file, int32_t line, uint32_t elapse
        , uint32_t thread_id, uint32_t fiber_id, uint64_t time
        , const std::string& thread_name)
        :m_file(file)
        , m_line(line)
        , m_elapse(elapse)
        , m_threadId(thread_id)
        , m_fiberId(fiber_id)
        , m_time(time)
        , m_threadName(thread_name)
        , m_logger(logger)
        , m_level(level) {
    }

    inline const char* getFile() const { return m_file; }
    inline int32_t getLine() const { return m_line; }
    inline uint32_t getElapse() const { return m_elapse; }
    inline uint32_t getThreadId() const { return m_threadId; }
    inline uint32_t getFiberId() const { return m_fiberId; }
    inline uint64_t getTime() const { return m_time; }
    inline const std::string& getThreadName() const { return m_threadName; }
    inline std::string getContent() const { return m_ss.str(); }
    inline std::shared_ptr<Logger> getLogger() const { return m_logger; }
    inline LogLevel::Level getLevel() const { return m_level; }
    inline std::stringstream& getSS() { return m_ss; }

private:

    // File name
    const char* m_file = nullptr;

    // Line number
    int32_t m_line = 0;

    // The number of milliseconds elapsed since the program started
    uint32_t m_elapse = 0;

    // Thread ID
    uint32_t m_threadId = 0;

    // Coroutine ID
    uint32_t m_fiberId = 0;

    // Timestamp
    uint64_t m_time = 0;

    // Thread name
    std::string m_threadName;

    // Log content stream
    std::stringstream m_ss;

    // Logger
    std::shared_ptr<Logger> m_logger;

    // Log level
    LogLevel::Level m_level;
}


class LogEventWrap {
public:
    LogEventWrap(LogEvent::ptr e) : m_event(e) {};
    ~LogEventWrap() {
        m_event->getLogger()->log(m_event->getLevel(), m_event);
    }
    inline LogEvent::ptr getEvent() const { return m_event; }
    inline std::stringstream& getSS() { return m_event->getSS(); };

private:
    LogEvent::ptr m_event;
}

//responsible for taking LogEvents and writing them out to the desired destination
class Logger : public std::enable_shared_from_this<Logger> {
public:
    using ptr = std::shared_ptr<Logger>;
    Logger(const std::string& name = "root");

private:
    // Logger name
    std::string m_name;

    // Logger level
    LogLevel::Level m_level;

    // Logger mutex
    MutexType m_mutex;

    // Collection of logger targets
    std::list<LogAppender::ptr> m_appenders;

    // logger formatter
    LogFormatter::ptr m_formatter;

    // Main logger
    Logger::ptr m_root;
};

class LogFormatter; // formats a LogEvent into a string based on a specified pattern
class LogAppender; //an abstract base class that defines the interface for different log destinations
class LoggerManager; // handle different loggers.








#endif