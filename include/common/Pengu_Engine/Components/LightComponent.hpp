#ifndef LIGHTCOMPONENT_HPP
#define LIGHTCOMPONENT_HPP 1

#include "gl/glew.h"
#include "glm/glm.hpp"

enum class LightType {
	E_Directional,
	E_Point,
	E_Spot
};

struct Lights {

	Lights() {};

	Lights(LightType lightType_)
	{
		switch (lightType_)
		{
		case LightType::E_Directional:
			type_ = 0;
			break;
		case LightType::E_Point:
			type_ = 1;
			break;
		case LightType::E_Spot:
			type_ = 2;
			break;
		default:
			type_ = 1;
			break;
		}
	};

	int type_ = 0;

	glm::vec3 position_ = { 0.0f,0.0f,0.0f };
	glm::vec3 direction_ = glm::normalize(glm::vec3(-0.2f, -1.0f, -0.3f));
	glm::vec3 color_ = { 1.0f,1.0f,1.0f };
	float intensity_ = 1.0f;
	float shin_ = 32.0f;

	float ambiStr_ = 0.1f;
	float specStr_ = 0.5f;

	// Point
	float radius_ = 10.0f;

	// Spot
	float innerCutoff_ = glm::cos(glm::radians(12.5f));
	float outerCutoff_ = glm::cos(glm::radians(17.5f));


	// Attenuation
	float constant_ = 1.0f;
	float linear_ = 0.022f;
	float quadratic_ = 0.0019f;

	float shadowSoftness_ = 1.0f;
	bool castsShadows = true;
	glm::mat4 lightSpaceMatrix = glm::mat4(1.0f);
};

#endif // !LIGHTCOMPONENT_HPP
