#ifndef LOGGER_HPP
#define LOGGER_HPP 1

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

class Logger {
public:
	Logger();
	~Logger();

	static void Init();

	static std::shared_ptr<spdlog::logger>& PE();
	static std::shared_ptr<spdlog::logger>& LOG();
	static std::shared_ptr<spdlog::logger>& SCRIPT();

private:

	static std::shared_ptr<spdlog::logger> s_PenguEngine;
	static std::shared_ptr<spdlog::logger> s_Logger;
	static std::shared_ptr<spdlog::logger> s_Scripting;

};

#endif // ! LOGGER_HPP
