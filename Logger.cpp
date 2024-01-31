/*
 * @Author: Tairan Gao
 * @Date:   2024-01-30 17:17:32
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2024-01-30 17:18:11
 */

#include <iostream>
#include <functional>
#include <time.h>
#include <string.h>

#include "Logger.h"

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