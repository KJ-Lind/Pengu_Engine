#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP 1

#include <memory>
#include <cstdint>
#include <bitset>
#include <queue>
#include <array>
#include <vector>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 50000;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager {

public:
	EntityManager();

	Entity CreateEntity();

	void DestroyEntity(Entity entity);

	void SetSignature(Entity entity, Signature signature);

	Signature GetSignature(Entity entity);

	std::vector<Entity> GetAllEntities() const;

private:
	std::queue<Entity> availableEntities_{};

	std::array<Signature, MAX_ENTITIES> signatures_{};

	uint32_t livingEntityCount_{};
};

#endif // !ENTITYMANAGER_HPP
