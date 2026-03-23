#ifndef LUAWRAPPER_HPP
#define LUAWRAPPER_HPP 1

#include "Pengu_Engine/Managers/ECS/EntityManager.hpp"
#include "Pengu_Engine/Managers/ECS/ComponentManager.hpp"
#include "Pengu_Engine/Managers/ECS/ECSManager.hpp"
#include "Pengu_Engine/Misc/Logmacros.hpp"


#include <memory>

class LuaEntity {
public:
	LuaEntity(Entity e, std::shared_ptr<ECSManager> ecs) : entity_{ e }, ecs_{ ecs } {}

	template<typename T>
	T& GetComponent()
	{
		return ecs_->GetComponent<T>(entity_);
	}

	Entity entity_;
	std::shared_ptr<ECSManager> ecs_;
};

#endif // !LUAWRAPPER_HPP
