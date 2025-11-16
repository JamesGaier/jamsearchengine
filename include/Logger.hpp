#pragma once
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <cstdarg>
#include <memory>

class Logger
{
public:
    Logger(const std::string &path, const std::string &name);
    Logger();

    std::string getPath() const;
    std::string getName() const;

    void setStdoutSinkLevel(spdlog::level::level_enum level);
    void setFileSinkLevel(spdlog::level::level_enum level);


    void log(spdlog::level::level_enum level, const char *str);

private:
    std::string m_path;
    std::string m_loggerName;
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_stdoutSink;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> m_fileSink;
    spdlog::logger m_logger;
};


static Logger g_logger;

[[maybe_unused]] static void log(spdlog::level::level_enum level, const char *formatStr...)
{
    constexpr static size_t BUFFER_SIZE = 10'000;
    va_list args;
    char buffer[BUFFER_SIZE];
    va_start(args, formatStr);
    vsnprintf(buffer, BUFFER_SIZE, formatStr, args);
    va_end(args);

    g_logger.setFileSinkLevel(level);
    g_logger.setStdoutSinkLevel(level);
    g_logger.log(level, buffer);
}


#define LOG_INFO(...) log(spdlog::level::info, __VA_ARGS__)
#define LOG_ERROR(...) log(spdlog::level::err, __VA_ARGS__)
#define LOG_DEBUG(...) log(spdlog::level::debug, __VA_ARGS__)
#define LOG_CRITICAL(...) log(spdlog::level::critical, __VA_ARGS__)