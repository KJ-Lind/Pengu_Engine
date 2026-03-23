#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP 1

#include "glm/glm.hpp"

struct TransformComponent {
	TransformComponent() {};
	TransformComponent(glm::vec3 pos, glm::vec3 scl, glm::vec3 rot) : position_{ pos }, scale_{ scl }, rotation_{ rot } {};

	glm::mat4 model_ = glm::mat4(1.0f);

	glm::vec3 position_ = glm::vec3(0.0f);
	glm::vec3 scale_ = glm::vec3(1.0f);
	glm::vec3 rotation_ = glm::vec3(0.0f);
};

#endif // !TRANSFORMCOMPONENT_HPP
