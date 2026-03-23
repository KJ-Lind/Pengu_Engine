#pragma once

#include "Logger.hpp"

#define ENGINE_INFO(...)    ::Logger::PE()->info(__VA_ARGS__);
#define ENGINE_WARNING(...) ::Logger::PE()->warn(__VA_ARGS__);
#define ENGINE_ERROR(...)   ::Logger::PE()->error(__VA_ARGS__);

#define LOG_INFO(...)       ::Logger::LOG()->info(__VA_ARGS__); 
#define LOG_WARNING(...)    ::Logger::LOG()->warn(__VA_ARGS__); 
#define LOG_ERROR(...)      ::Logger::LOG()->error(__VA_ARGS__);