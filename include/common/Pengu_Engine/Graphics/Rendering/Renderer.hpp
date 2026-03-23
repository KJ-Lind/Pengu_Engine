#ifndef RENDERER_HPP
#define RENDERER_HPP 1

#include "Pengu_Engine/Camera/Camera.hpp"
#include "Pengu_Engine/Graphics/Rendering/RenderPipeline.hpp"
#include <memory>

namespace Pengu::Scene { class SceneBase; }
namespace Pengu::Resources { class ResourceManager; }

namespace Pengu::Graphics::Rendering {

	class Renderer {
	public:

		Renderer() = default;
		~Renderer() { shutdown(); }

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		void init(std::unique_ptr<RenderPipeline> pipeline, Pengu::Resources::ResourceManager& rm);
		void setPipeline(std::unique_ptr<RenderPipeline> newPipeline);
		void render(Pengu::Scene::SceneBase& scene, Camera& camera);
		void onResize(int width, int height);

		RenderPipeline* getPipeline() { return m_pipeline.get(); }
		const RenderPipeline* getPipeline() const { return m_pipeline.get(); }

		bool hasPipeline() const { return m_pipeline != nullptr; }

		void shutdown();

	private:
		std::unique_ptr<RenderPipeline> m_pipeline;
		Pengu::Resources::ResourceManager* m_rm = nullptr;
		int m_width = 0;
		int m_height = 0;
	};
}

#endif // !RENDERER_HPP
