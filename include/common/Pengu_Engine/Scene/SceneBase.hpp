#ifndef SCENEBASE_HPP 
#define SCENEBASE_HPP 1

#include "Pengu_Engine/Managers/ECS/ECSManager.hpp"
#include "Pengu_Engine/Components/DrawableComponent.hpp"
#include "Pengu_Engine/Components/TransformComponent.hpp"
#include "Pengu_Engine/Components/LightComponent.hpp"
#include "Pengu_Engine/Components/ScriptComponent.hpp"
#include "Pengu_Engine/Systems/LightSystem.hpp"
#include "Pengu_Engine/Systems/ScriptSystem.hpp"

#include <vector>
#include <string>
#include <algorithm>

namespace Pengu::Resources { class ResourceManager; }
namespace Pengu::Core { class PenguEngine; }

namespace Pengu::Scene
{
	class SceneBase {
	public:
		SceneBase(Pengu::Core::PenguEngine* engine) : m_world(std::make_unique<ECSManager>()), m_engine(engine) { m_world->Init(); };
		virtual ~SceneBase() = default;

		SceneBase(const SceneBase&) = delete;
		SceneBase& operator=(const SceneBase&) = delete;
		SceneBase(SceneBase&&) = default;
		SceneBase& operator=(SceneBase&&) = default;

		virtual void update(float dt) = 0;
		virtual void onLoad(Pengu::Resources::ResourceManager& rm) = 0;
		virtual void onUnload() = 0;

		ECSManager& getWorld() { return *m_world; };
		const ECSManager& getWorld() const { return *m_world; };

		const std::vector<Entity>& getRenderables() const { return m_renderables; }

		void setLightSystem(std::shared_ptr<LightSystem> ls) { m_lightSystem = ls; }
		std::shared_ptr<LightSystem> getLightSystem() const { return m_lightSystem; }

		void refreshRenderables();

		void registerRenderable(Entity id);

		void unregisterRenderable(Entity id);

		const std::string getName() const { return m_name; };

	protected:

		std::string m_name = "Unnamed Scene";
		Pengu::Core::PenguEngine* m_engine = nullptr;

	private:
		std::unique_ptr<ECSManager> m_world;
		std::vector<Entity> m_renderables;
		std::shared_ptr<LightSystem> m_lightSystem;
	};

} //PenguEngine::Scene
#endif // ! SCENEBASE_HPP 

