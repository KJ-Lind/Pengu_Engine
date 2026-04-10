#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP 1

#include "Pengu_Engine/Systems/BaseSystems.hpp"
#include "Pengu_Engine/Components/ScriptComponent.hpp"
#include "Pengu_Engine/Managers/ECS/ECSManager.hpp"
#include "Pengu_Engine/Inputs/Input.hpp"

#include <memory>
#include <unordered_map>

#include "sol/sol.hpp"

class Scripting : public System {

public:
	Scripting(ECSManager& ecs);
	~Scripting();

	void Init(Input* inp);

	void Update(double dt);

	void Start();

	void Finish();

protected:

	void BindAPI(Input* inp);

	void bindGLM();
	void bindEngine();
	void bindLogger();

	void LoadScript(Entity entity, ScriptingComponent& sc);

	void ReloadScript(Entity entity, ScriptingComponent& sc);

	template<typename... Args>
	void SafeCall(sol::protected_function& func, Args&&... args)
	{
		auto result = func(std::forward<Args>(args)...);

		if (!result.valid()) {
			sol::error err = result;
			SCRP_ERROR("[Lua Call Error] {0}", err.what());
		}
	}

private:
	void Shutdown();

	std::unordered_map<std::string, sol::bytecode> scriptCache_;
	std::set<Entity> entitiesToReload_;
	std::unique_ptr<sol::state> globalLuaState_;
	ECSManager& m_world;
};


#endif // !