#ifndef FORWARDSHAD_HPP
#define FORWARDSHAD_HPP 1

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

	class ForwardShadPipeline : public RenderPipeline
	{
	public:

		void init(Pengu::Resources::ResourceManager& rm) override;
		void cleanup() override;
		void reload(Pengu::Resources::ResourceManager& rm) override;

		void render(Pengu::Scene::SceneBase& scene, Camera& camera) override;

		void onResize(int width, int height) override;

		const std::string& getName() const override
		{
			static const std::string name = "Forward Shadows";
			return name;
		}

	private:
		void destroyLightShadowMap();
		void shadowPass(Lights& light, Pengu::Scene::SceneBase& scene);
		void setupShadowMap();
		glm::mat4 buildLightSpaceMatrix(const Lights& ld, const TransformComponent& t);
		glm::mat4 buildModelMatrix(const TransformComponent& transform);
		void uploadTransform(const TransformComponent& transform, Camera& cam);
		void drawSubMeshes(const DrawableComponent& draw);
		void drawSubMeshesShadow(const DrawableComponent& draw);
		void bindLight(const Lights& light, const TransformComponent& lightTransform);
		void resetBlendState();

		std::shared_ptr<Pengu::Graphics::Shader> m_forwardShader;
		std::shared_ptr<Pengu::Graphics::Shader> m_shadowShader;
		bool m_firstpass = true;
		int m_width = 0;
		int m_height = 0;

		int shadowResolution = 512;
		GLuint shadowMapFBO = 0;
		GLuint shadowMapTexture = 0;
	};
}
#endif // !FORWARDSHAD_HPP
