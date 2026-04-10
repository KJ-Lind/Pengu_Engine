#ifndef RENDERPIPELINE_HPP
#define RENDERPIPELINE_HPP 1

#include "Pengu_Engine/Camera/Camera.hpp"
#include <string>

namespace Pengu::Resources { class ResourceManager; }
namespace Pengu::Scene { class SceneBase; }

namespace Pengu::Graphics::Rendering {

	class RenderPipeline {
	public:

		RenderPipeline() = default;
		virtual ~RenderPipeline() = default;

		RenderPipeline(const RenderPipeline&) = delete;
		RenderPipeline& operator=(const RenderPipeline&) = delete;

		virtual void init(Pengu::Resources::ResourceManager& rm) = 0;
		virtual void cleanup() = 0;
		virtual void reload(Pengu::Resources::ResourceManager& rm) = 0;

		virtual void onPreRender(Pengu::Scene::SceneBase& scene, Camera& camera) {}

		virtual void render(Pengu::Scene::SceneBase& scene, Camera& camera) = 0;

		virtual void onResize(int width, int height) = 0;

		virtual const std::string& getName() const = 0;
		bool isInitialized() const { return m_initialized; }
		bool bWireFrame = false;

	protected:
		bool m_initialized = false;
	};
}
#endif // ! RENDERPIPELINE_HPP