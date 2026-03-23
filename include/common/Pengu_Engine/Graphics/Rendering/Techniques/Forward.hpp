#ifndef FORWARD_HPP
#define FORWARD_HPP 1

#include "Pengu_Engine/Graphics/Rendering/RenderPipeline.hpp"
#include "Pengu_Engine/Components/DrawableComponent.hpp"
#include "Pengu_Engine/Components/TransformComponent.hpp"
#include "Pengu_Engine/Components/LightComponent.hpp"

#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pengu::Resource { class ResourceManager; }
namespace Pengu::Scene { class SceneBase; }
namespace Pengu::Graphics { class Shader; }

namespace Pengu::Graphics::Rendering {

	class ForwardPipeline : public RenderPipeline
	{
	public:

		void init(Pengu::Resources::ResourceManager& rm) override;
		void cleanup() override;

		void render(Pengu::Scene::SceneBase& scene, Camera& camera) override;

		void onResize(int width, int height) override;

		const std::string& getName() const override
		{
			static const std::string name = "Forward";
			return name;
		}

	private:
		glm::mat4 buildModelMatrix(const TransformComponent& transform);
		void drawSubMeshes(const DrawableComponent& draw);
		void bindLight(const Lights& light, const TransformComponent& lightTransform);
		void resetBlendState();

		std::shared_ptr<Pengu::Graphics::Shader> m_shader;
		bool m_firstpass = true;
		int m_width = 0;
		int m_height = 0;
	};
}
#endif // !FORWARD_HPP
