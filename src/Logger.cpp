#include "Logger.hpp"



Logger::Logger(const std::string &path, const std::string &name)
: m_path(path)
, m_loggerName(name)
, m_stdoutSink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>())
, m_fileSink(std::make_shared<spdlog::sinks::basic_file_sink_mt>(m_path, true))
, m_logger(m_loggerName, {m_stdoutSink, m_fileSink})
{
    // for now I am hardcoding this value.  A better way to do this is to make a sink class then make
    // adding a sink configurable as well as the level for each sink configurable
    m_logger.set_level(spdlog::level::info);
}

Logger::Logger()
: m_path("logs/webcrawler.log")
, m_loggerName("mylogger")
, m_stdoutSink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>())
, m_fileSink(std::make_shared<spdlog::sinks::basic_file_sink_mt>(m_path, true))
, m_logger(m_loggerName, {m_stdoutSink, m_fileSink})
{
    m_logger.set_level(spdlog::level::info);
}


std::string Logger::getPath() const
{
    return m_path;
}

std::string Logger::getName() const
{
    return m_loggerName;
}

void Logger::setStdoutSinkLevel(spdlog::level::level_enum level)
{
    m_stdoutSink->set_level(level);
}

void Logger::setFileSinkLevel(spdlog::level::level_enum level)
{
    m_fileSink->set_level(level);
}

void Logger::log(spdlog::level::level_enum level, const char *str)
{
    m_logger.log(level, str);
    m_logger.flush();
}