#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP 1

#include "Pengu_Engine/Managers/ECS/EntityManager.hpp"
#include "Pengu_Engine/Misc/Logmacros.hpp"

#include <exception>
#include <unordered_map>
#include <typeindex>

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:

	void InsertData(Entity entity, T component)
	{

		if (entityToIndexMap_.find(entity) != entityToIndexMap_.end()) {
			throw std::logic_error(
				"ComponentArray::InsertData - Component added to same entity more than once."
			);
		}

		size_t newIndex = size_;
		entityToIndexMap_[entity] = newIndex;
		indexToEntityMap_[newIndex] = entity;
		componentArray_[newIndex] = component;
		++size_;
	}

	void RemoveData(Entity entity)
	{
		if (entityToIndexMap_.find(entity) == entityToIndexMap_.end()) {
			throw std::logic_error(
				"ComponentArray::RemoveData - Removing non-existing component."
			);
		}

		size_t indexOfRemoveEntity = entityToIndexMap_[entity];
		size_t indexOfLastElement = size_ - 1;
		componentArray_[indexOfRemoveEntity] = componentArray_[indexOfLastElement];

		Entity entityOfLastElement = indexToEntityMap_[indexOfLastElement];
		entityToIndexMap_[entityOfLastElement] = indexOfRemoveEntity;
		indexToEntityMap_[indexOfRemoveEntity] = entityOfLastElement;

		entityToIndexMap_.erase(entity);
		indexToEntityMap_.erase(indexOfLastElement);
		--size_;
	}

	T& GetData(Entity entity)
	{
		if (entityToIndexMap_.find(entity) == entityToIndexMap_.end()) {
			throw std::logic_error(
				"ComponentArray::GetData - Retrieving non-existent component."
			);
		}

		return componentArray_[entityToIndexMap_[entity]];
	}

	bool HasData(Entity entity) {
		return entityToIndexMap_.find(entity) != entityToIndexMap_.end();
	}

	void EntityDestroyed(Entity entity)
	{
		if (entityToIndexMap_.find(entity) != entityToIndexMap_.end()) {
			ENGINE_INFO("Removed data of entity {}", entity);
			RemoveData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> componentArray_;
	std::unordered_map<Entity, size_t> entityToIndexMap_;
	std::unordered_map<size_t, Entity> indexToEntityMap_;

	size_t size_ = 0;
};

class ComponentManager {
public:
	template<typename T>
	void RegisterComponent()
	{

		std::type_index typeName = typeid(T);

		if (componentTypes_.find(typeName) != componentTypes_.end()) {
			throw std::logic_error(
				"ComponentManager::RegisterComponent - Registering component type more than once."
			);
		}

		componentTypes_.insert({ typeName, nextComponentType_ });

		componentArrays_.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		++nextComponentType_;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		std::type_index typeName = typeid(T);

		if (componentTypes_.find(typeName) == componentTypes_.end()) {
			throw std::logic_error(
				"ComponentManager::GetComponentType - Component not registered before use."
			);
		}

		return componentTypes_[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		try {
			GetComponentArray<T>()->InsertData(entity, component);
		}
		catch (const std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate();
		}

	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		try {
			return GetComponentArray<T>()->RemoveData(entity);
		}
		catch (std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate();
		}
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		try {
			return GetComponentArray<T>()->GetData(entity);
		}
		catch (const std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate;
		}
	}

	template<typename T>
	bool HasComponent(Entity entity) {
		try {
			return GetComponentArray<T>()->HasData(entity);
		}
		catch (const std::exception& e) {
			ENGINE_WARNING(e.what());
			std::terminate;
		}
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : componentArrays_)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<std::type_index, ComponentType> componentTypes_{};

	std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> componentArrays_{};

	ComponentType nextComponentType_{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		std::type_index typeName = typeid(T);

		if (componentTypes_.find(typeName) == componentTypes_.end()) {
			throw std::logic_error(
				"ComponentManager::GetComponentArray - Component not registered before."
			);
		}

		return std::static_pointer_cast<ComponentArray<T>>(componentArrays_[typeName]);
	}
};

#endif // !COMPONENTMANAGER_HPP


