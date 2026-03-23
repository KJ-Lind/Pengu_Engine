#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP 1

#include <string>
#include <sol/sol.hpp>

class Interpreter {
public:
	Interpreter();
	~Interpreter();

	void ExecScript(std::string scriptPath);

	//void ExecFunc(std::string callFunc);

private:

	sol::state Lua;

	//templates<typename T>
	//DefiningCppMethods(&T );

};

#endif // !INTERPRETER_HPP
