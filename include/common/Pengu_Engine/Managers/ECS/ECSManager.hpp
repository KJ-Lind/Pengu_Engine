/**
 * @file ECSManager.hpp
 * @brief Core Entity Component System (ECS) management.
 * @details This system manages entity lifecycles and component storage using
 * a Type-to-List mapping. It facilitates high-performance data-oriented programming.
 */

#ifndef ECSMANAGER_HPP
#define ECSMANAGER_HPP 1

#include "Pengu_Engine/Managers/ECS/EntityManager.hpp"
#include "Pengu_Engine/Managers/ECS/ComponentManager.hpp"
#include "Pengu_Engine/Managers/ECS/SystemManager.hpp"
#include "Pengu_Engine//Components/TagComponent.hpp"

class ECSManager {
public:

	ECSManager();

	ECSManager(const ECSManager& rvalue) = delete;
	ECSManager& operator = (const ECSManager& rvalue) = delete;

	ECSManager(ECSManager&& rvalue) noexcept : entityManager_(std::move(rvalue.entityManager_)), componentManager_(std::move(rvalue.componentManager_)), systemManager_(std::move(rvalue.systemManager_))
	{

	}
	ECSManager& operator = (ECSManager&& rvalue)noexcept
	{
		if (this != &rvalue)
		{
			componentManager_ = std::move(rvalue.componentManager_);
			entityManager_ = std::move(rvalue.entityManager_);
			systemManager_ = std::move(rvalue.systemManager_);
		}

		return *this;
	};

	void Init();
	// Entity Methods 
	Entity CreateEntity() {
		try {
			return entityManager_->CreateEntity();
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate;
		}
	};

	void DestroyEntity(Entity entity) {
		try {
			entityManager_->DestroyEntity(entity);

			componentManager_->EntityDestroyed(entity);

			systemManager_->EntityDestroyed(entity);
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
		}
	};

	std::vector<Entity> GetAllEntities() const {
		return entityManager_->GetAllEntities();
	}

	Entity GetEntityByTag(const std::string& tag) {
		for (auto entity : entityManager_->GetAllEntities()) {
			if (!HasComponent<TagComponent>(entity)) continue;
			if (GetComponent<TagComponent>(entity).tag == tag)
				return entity;
		}
		return -1; // or whatever your invalid entity constant is
	}

	std::vector<Entity> GetEntitiesByTag(const std::string& tag) {
		std::vector<Entity> result;
		for (auto entity : entityManager_->GetAllEntities()) {
			if (!HasComponent<TagComponent>(entity)) continue;
			if (GetComponent<TagComponent>(entity).tag == tag)
				result.push_back(entity);
		}
		return result;
	}

	// Component Methods
	template<typename T>
	void RegisterComponent() {
		try {
			componentManager_->RegisterComponent<T>();
		}
		catch (std::exception& e) {
			ENGINE_ERROR(e.what());
		}
	};

	template<typename T>
	void AddComponent(Entity entity, T component) {
		try {
			componentManager_->AddComponent<T>(entity, component);

			auto signature = entityManager_->GetSignature(entity);
			signature.set(componentManager_->GetComponentType<T>(), true);
			entityManager_->SetSignature(entity, signature);

			systemManager_->EntitySignatureChanged(entity, signature);
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
		}
	};

	template<typename T>
	void RemoveComponent(Entity entity) {
		try {
			componentManager_->RemoveComponent<T>(entity);

			auto signature = entityManager_->GetSignature(entity);
			signature.set(componentManager_->GetComponentType<T>(), false);
			entityManager_->SetSignature(entity, signature);

			systemManager_->EntitySignatureChanged(entity, signature);
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
		}
	};

	template<typename T>
	T& GetComponent(Entity entity) {
		try {
			return componentManager_->GetComponent<T>(entity);
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate;
		}
	};

	template<typename T>
	bool HasComponent(Entity entity) {
		try {
			return componentManager_->HasComponent<T>(entity);
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate;
		}
	}

	template<typename T>
	ComponentType GetComponentType() {
		try {
			return componentManager_->GetComponentType<T>();
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate;
		}
	};

	// System Methods
	template<typename T, typename... Args>
	std::shared_ptr<T> RegisterSystem(Args&&... args) {
		try {
			return systemManager_->RegisterSystem<T>(std::forward<Args>(args)...);
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate;
		}
	};

	template<typename T>
	void SetSystemSignature(Signature signature) {
		try {
			return systemManager_->SetSignature<T>(signature);
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
		}
	};

private:
	std::unique_ptr<ComponentManager> componentManager_;
	std::unique_ptr<EntityManager> entityManager_;
	std::unique_ptr<SystemManager> systemManager_;
};

#endif // ECSMANAGER_HPP


