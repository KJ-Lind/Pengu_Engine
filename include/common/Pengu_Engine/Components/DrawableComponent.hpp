#ifndef DRAWABLECOMPONENT_HPP
#define DRAWABLECOMPONENT_HPP 1

#include "Pengu_Engine/Graphics/GameObject.hpp"

#include <memory>


struct DrawableComponent {
	DrawableComponent() {};
	DrawableComponent(std::shared_ptr<GameObject> gameobj) : gameObj{ gameobj } {};

	std::shared_ptr<GameObject> gameObj;
};

#endif // !DRAWABLECOMPONENT_HPP
