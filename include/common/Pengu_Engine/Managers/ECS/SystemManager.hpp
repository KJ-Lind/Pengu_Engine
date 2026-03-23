#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP 1

#include "Pengu_Engine/Managers/ECS/EntityManager.hpp"
#include "Pengu_Engine/Systems/BaseSystems.hpp"

#include <stdexcept>
#include <typeindex>
#include <set>
#include <memory>
#include <unordered_map>

class SystemManager {

public:
	template<typename T, typename... Args>
	std::shared_ptr<T> RegisterSystem(Args&&... args) {
		std::type_index typeName = typeid(T);

		if (systems_.find(typeName) != systems_.end()) {
			throw std::logic_error(
				"SystemManager::RegisterSystem - Registering system more than once."
			);
		}

		auto system = std::make_shared<T>(std::forward<Args>(args)...);
		systems_.insert({ typeName, system });
		return system;
	};

	template<typename T>
	void SetSignature(Signature signature) {
		std::type_index typeName = typeid(T);

		if (systems_.find(typeName) == systems_.end()) {
			throw std::logic_error(
				"SystemManager::SetSignature - System used before registered."
			);
		}

		signatures_.insert({ typeName, signature });
	};

	void EntityDestroyed(Entity entity) {
		for (auto const& pair : systems_) {
			auto const& system = pair.second;

			system->entities_.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature);

private:
	std::unordered_map<std::type_index, Signature> signatures_{};
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems_{};
};

#endif // !SYSTEMMANAGER_HPP

