#ifndef LIGHTSYSTEM_HPP
#define LIGHTSYSTEM_HPP 1

#include "Pengu_Engine/Systems/BaseSystems.hpp"
#include "Pengu_Engine/Components/LightComponent.hpp"
#include "Pengu_Engine/Components/TransformComponent.hpp"
#include "Pengu_Engine/Managers/ECS/ECSManager.hpp"

#include <vector>

struct LightData {
	Lights* light;
	const TransformComponent* transform;
};

class LightSystem : public System {
public:
	LightSystem() = default;
	~LightSystem() = default;

	std::vector<LightData> collectLights(ECSManager& ecs) const {
		std::vector<LightData> result;
		for (auto& light : entities_) {
			if (ecs.HasComponent<Lights>(light)) {
				result.push_back({ 
					&ecs.GetComponent<Lights>(light),
					&ecs.GetComponent<TransformComponent>(light) 
					});
			}
		}
		return result;
	}
};

#endif // !LIGHTSYSTEM_HPP
