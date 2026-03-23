#ifndef MATERIAL_HPP
#define MATERIAL_HPP 1

#include <memory>
#include "glm/glm.hpp"

namespace Pengu::Graphics { class Texture; }
namespace Pengu::Graphics { class Shader; }


namespace Pengu::Graphics {

	class Material {
	public:
		glm::vec4 albedoColor = { 1.0f,1.0f,1.0f,1.0f };

		float roughness = 0.5f;
		float metallic = 0.0f;

		std::shared_ptr<Texture> albedoMap = nullptr;
		std::shared_ptr<Texture> normalMap = nullptr;
		std::shared_ptr<Texture> roughnessMap = nullptr;

		void Bind(Shader& s);
	};
}//Pengu::Graphics::Material

#endif // !MATERIAL_HPP
