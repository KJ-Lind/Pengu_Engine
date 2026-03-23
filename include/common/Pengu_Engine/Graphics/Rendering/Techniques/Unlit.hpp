#ifndef UNLIT_HPP
#define UNLIT_HPP 1

#include "Pengu_Engine/Graphics/Rendering/RenderPipeline.hpp"
#include "Pengu_Engine/Components/DrawableComponent.hpp"
#include "Pengu_Engine/Components/TransformComponent.hpp"

#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pengu::Resources { class ResourceManager; }
namespace Pengu::Scene { class SceneBase; }
namespace Pengu::Graphics { class Shader; }

namespace Pengu::Graphics::Rendering {

	class UnlitPipeline : public RenderPipeline {

	public:

		void init(Pengu::Resources::ResourceManager& rm) override;
		void cleanup() override;

		void render(Pengu::Scene::SceneBase& scene, Camera& camera) override;

		void onResize(int width, int height) override;

		const std::string& getName() const override
		{
			static const std::string name = "Unlit";
			return name;
		}

	private:
		glm::mat4 buildModelMatrix(const TransformComponent& transform);
		void drawSubMeshes(const DrawableComponent& draw);
		void resetBlendState();

		std::shared_ptr<Pengu::Graphics::Shader> m_shader;
		int m_width = 0;
		int m_height = 0;
	};
}
#endif // !UNLIT_HPP
