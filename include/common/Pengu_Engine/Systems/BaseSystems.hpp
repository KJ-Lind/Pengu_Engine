#ifndef BASESYSTEMS_HPP
#define BASESYSTEMS_HPP 1

#include "Pengu_Engine/Managers/ECS/EntityManager.hpp"

#include <set>

class System {
public:
	std::set<Entity> entities_;
};

#endif // !