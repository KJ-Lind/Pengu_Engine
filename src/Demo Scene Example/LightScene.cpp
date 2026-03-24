#include "Pengu_Engine/Scene/LightScene.hpp"
#include "Pengu_Engine/Managers/Resource/ResourceManager.hpp"
#include "Pengu_Engine/Graphics/Rendering/Techniques/ForwardShad.hpp"

namespace Pengu::Scene {
	void LightScene::update(float dt)
	{
		auto& world = getWorld();
		auto& inp = m_engine->GetInput();
		auto& camera = m_engine->GetCamera();

		auto light = world.GetEntityByTag("Light");
		world.GetComponent<TransformComponent>(light).position_ = camera.position_;
		world.GetComponent<TransformComponent>(light).rotation_ = glm::normalize(camera.front_);


		if (inp.isPressed(Action::C)) {
			auto FlashLight = world.CreateEntity();
			world.AddComponent(FlashLight, Lights(LightType::E_Spot));
			world.AddComponent(FlashLight, TransformComponent(camera.position_, glm::vec3(1.0f), glm::normalize(camera.front_)));
			world.GetComponent<Lights>(FlashLight).color_ = glm::vec3(0.5f, 0.5f, 0.5f);
			world.GetComponent<Lights>(FlashLight).radius_ = 50.0f;
			world.GetComponent<Lights>(FlashLight).innerCutoff_ = glm::cos(glm::radians(12.0f));
			world.GetComponent<Lights>(FlashLight).outerCutoff_ = glm::cos(glm::radians(17.0f));
			world.GetComponent<Lights>(FlashLight).shadowSoftness_ = 1.0f;
		}
	}

	void LightScene::onLoad(Pengu::Resources::ResourceManager& rm)
	{
		auto& world = getWorld();
		auto& camera = m_engine->GetCamera();

		getWorld().RegisterComponent<DrawableComponent>();
		getWorld().RegisterComponent<TransformComponent>();
		getWorld().RegisterComponent<Lights>();
		getWorld().RegisterComponent<TagComponent>();

		auto lightsys = getWorld().RegisterSystem<LightSystem>();
		{
			Signature signature;
			signature.set(getWorld().GetComponentType<Lights>());
			signature.set(getWorld().GetComponentType<TransformComponent>());
			getWorld().SetSystemSignature<LightSystem>(signature);
		}
		setLightSystem(lightsys);

		auto planeMat = rm.getMaterial("Plane_Material");
		planeMat->albedoMap = nullptr;
		planeMat->albedoColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		auto plane = rm.CreatePlane("Plane", 100, 100, 1, planeMat);

		auto BasicMat = rm.getMaterial("Cube_Material");
		BasicMat->albedoMap = nullptr;
		BasicMat->albedoColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		auto cube8 = rm.CreateCube8v("Cube_8", 2.5f, BasicMat);

		BasicMat->albedoColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		auto cube24 = rm.CreateCube24v("Cube_24", 2.5f, BasicMat);

		BasicMat->albedoColor = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
		auto quad = rm.CreateQuad("Quad", 1.0f, BasicMat);

		BasicMat->albedoColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		auto sphere = rm.CreateSphere("Quad", 1.0f, 50.0f, 50.0f, BasicMat);

		auto panda = rm.loadObject("../resource/object/redpanda/red-panda.obj");

		auto player = getWorld().CreateEntity();

		getWorld().AddComponent(player, DrawableComponent(panda));
		getWorld().AddComponent(player, TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.5f), glm::vec3(0.0f)));

		auto floor = getWorld().CreateEntity();

		getWorld().AddComponent(floor, DrawableComponent(plane));
		getWorld().AddComponent(floor, TransformComponent(glm::vec3(-1.0f), glm::vec3(1.0f), glm::vec3(0.0f)));

		auto box = getWorld().CreateEntity();

		getWorld().AddComponent(box, DrawableComponent(cube8));
		getWorld().AddComponent(box, TransformComponent(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f)));

		box = getWorld().CreateEntity();

		getWorld().AddComponent(box, DrawableComponent(cube24));
		getWorld().AddComponent(box, TransformComponent(glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f)));

		auto panel = getWorld().CreateEntity();

		getWorld().AddComponent(panel, DrawableComponent(quad));
		getWorld().AddComponent(panel, TransformComponent(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(1.0f), glm::vec3(glm::radians(-45.0f), 0.0f, 0.0f)));

		auto ball = getWorld().CreateEntity();

		getWorld().AddComponent(ball, DrawableComponent(sphere));
		getWorld().AddComponent(ball, TransformComponent(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(1.0f), glm::vec3(0.0f)));

		auto FlashLight = world.CreateEntity();
		world.AddComponent(FlashLight, Lights(LightType::E_Spot));
		world.AddComponent(FlashLight, TransformComponent(camera.position_, glm::vec3(1.0f), glm::normalize(camera.front_)));
		world.AddComponent(FlashLight, TagComponent("Light"));
		world.GetComponent<Lights>(FlashLight).color_ = glm::vec3(0.5f, 0.5f, 0.5f);
		world.GetComponent<Lights>(FlashLight).radius_ = 50.0f;
		world.GetComponent<Lights>(FlashLight).innerCutoff_ = glm::cos(glm::radians(12.0f));
		world.GetComponent<Lights>(FlashLight).outerCutoff_ = glm::cos(glm::radians(17.0f));
		world.GetComponent<Lights>(FlashLight).shadowSoftness_ = 0.5f;

		refreshRenderables();
	}


	void LightScene::onUnload()
	{


	}
}
