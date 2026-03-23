#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP 1

#include <memory>

namespace Pengu::Scene { class SceneBase; }
namespace Pengu::Resources { class ResourceManager; }
namespace Pengu::Core { class PenguEngine; }

namespace Pengu::Scene {

	class SceneManager {

	public:

		SceneManager() = default;
		~SceneManager() = default;

		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

		SceneManager(SceneManager&&) = default;
		SceneManager& operator=(SceneManager&&) = default;

		void loadScene(std::unique_ptr<SceneBase> newScene, Pengu::Resources::ResourceManager& rm);
		void unloadCurrent();
		void update(float dt);

		Pengu::Scene::SceneBase* getActiveScene() { return m_activeScene.get(); };
		const Pengu::Scene::SceneBase* getActiveScene() const { return m_activeScene.get(); };


	private:

		std::unique_ptr<SceneBase> m_activeScene;

	};
}// Pengu::Scene

#endif // !SCENEMANAGER_HPP
