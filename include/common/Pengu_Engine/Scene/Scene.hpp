#ifndef SCENE_HPP 
#define SCENE_HPP 1

#include "Pengu_Engine/Scene/SceneBase.hpp"
#include "Pengu_Engine/PenguEngine.hpp"

namespace Pengu::Resources { class ResourceManager; }

namespace Pengu::Scene {
	class Scene : public SceneBase {
	public:
		Scene(Pengu::Core::PenguEngine* engine) : SceneBase(engine) { m_name = "Scene"; }

		void update(float dt) override;
		void onLoad(Pengu::Resources::ResourceManager& rm) override;
		void onUnload() override;

	};
}
#endif // ! SCENE_HPP 
