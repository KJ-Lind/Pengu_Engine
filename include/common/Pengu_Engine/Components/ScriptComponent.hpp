#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP 1

#include <filesystem>

#include "sol/sol.hpp"

struct ScriptingComponent {
	ScriptingComponent() : scriptPath_{}
	{
		env_ = sol::nil;
		instance = sol::nil;
	};
	ScriptingComponent(std::string path) : scriptPath_{ path } {};

	std::string scriptPath_;

	sol::environment env_ = sol::nil;
	sol::table instance;

	sol::protected_function onStart;
	sol::protected_function onUpdate;
	sol::protected_function onFinish;

	std::filesystem::file_time_type lastWriteTime;
};

#endif // !SCRIPTCOMPONENT_HPP
