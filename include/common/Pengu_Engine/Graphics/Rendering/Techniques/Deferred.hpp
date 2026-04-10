#ifndef DEFERRED_HPP
#define DEFERRED_HPP 1

#include "Pengu_Engine/Graphics/Rendering/RenderPipeline.hpp"
#include "Pengu_Engine/Components/DrawableComponent.hpp"
#include "Pengu_Engine/Components/TransformComponent.hpp"
#include "Pengu_Engine/Components/LightComponent.hpp"

#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pengu::Resources { class ResourceManager; }
namespace Pengu::Scene { class SceneBase; }
namespace Pengu::Graphics { class Shader; }


namespace Pengu::Graphics::Rendering {
	class DeferredPipeline : public RenderPipeline
	{
	public:
		void init(Pengu::Resources::ResourceManager& rm) override;
		void cleanup() override;
		void reload(Pengu::Resources::ResourceManager& rm) override;

		void onPreRender(Pengu::Scene::SceneBase& scene, Camera& camera) override;
		void render(Pengu::Scene::SceneBase& scene, Camera& camera) override;

		void onResize(int width, int height) override;

		const std::string& getName() const override
		{
			static const std::string name = "Deferred";
			return name;
		}


	private:

		void setupBuffer();
		void deleteBuffers();
		void setupQuad();
		void renderQuad();
		void bindLight(const Lights& light, const TransformComponent& lightTransform);
		void resetBlendState();

		/* Render Passes */
		void geometryPass(Pengu::Scene::SceneBase& scene, Camera& camera);
		void lightPass(Pengu::Scene::SceneBase& scene, Camera& camera);

		glm::mat4 buildModelMatrix(const TransformComponent& transform);
		void drawSubMeshes(const DrawableComponent& draw);

		/* Shaders */
		std::shared_ptr<Pengu::Graphics::Shader> m_bufferShad;
		std::shared_ptr<Pengu::Graphics::Shader> m_deferredShad;


		/* Buffers */
		unsigned int m_gBuffer = 0;
		unsigned int m_gPosition = 0;
		unsigned int m_gNormal = 0;
		unsigned int m_gColorSpec = 0;
		unsigned int m_rboDepth = 0;


		/* Quad */
		unsigned int m_quadVAO = 0;
		unsigned int m_quadVBO;

		std::shared_ptr<Pengu::Graphics::Shader> m_shadowShader;
		bool m_firstpass = true;
		int m_width = 0;
		int m_height = 0;

		int shadowResolution = 512;
		GLuint shadowMapFBO = 0;
		GLuint shadowMapTexture = 0;
	};
};


#endif // !DEFERRED_HPP
