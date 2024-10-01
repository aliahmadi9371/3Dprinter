#ifndef LOGINSTANCE_H
#define LOGINSTANCE_H
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <spdlog/spdlog.h>
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class LogInstance {
public:
//    static std::shared_ptr<spdlog::logger> info_logger_;
//    static spdlog::logger *logger;
    static LogInstance& Instance() {
        static LogInstance instance;
        return instance;
    }
    template <typename... Args>
    static void info(const Args&... args) {
//        info_logger_->info(args...);
//        info_logger_->flush();
//        spdlog::info(args...);
//        LogInstance::logger->info(args...);
    }

    template <typename... Args>
    static void error(const Args&... args) {
//        spdlog::error(args...);
//        LogInstance::logger->error(args...);
    }

    template <typename... Args>
    static void warn(const Args&... args) {
//        spdlog::warn(args...);
//        LogInstance::logger->warn(args...);
    }

private:
    LogInstance() {
//        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
//        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.txt");
////        spdlog::logger logger("console and file", { console_sink, file_sink });
//        logger = new spdlog::logger("console and file", { console_sink, file_sink });
//        spdlog::flush_on(spdlog::level::info);
//        spdlog::set_async_mode(4096);
//        spdlog:
//        spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %l %n[%t]: [test_tag] %v");
    };
    LogInstance(const LogInstance&) = delete;
    void operator=(const LogInstance&) = delete;
};

#endif // LOGINSTANCE_H
