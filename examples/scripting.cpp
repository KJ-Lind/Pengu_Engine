#include "Pengu_Engine/PenguEngine.hpp"
#include "Pengu_Engine/Graphics/Model.hpp"
#include "Pengu_Engine/Graphics/Shader.hpp"
#include "Pengu_Engine/ECS/ECSManager.hpp"
#include "Pengu_Engine/ECS/Components/DrawableComponent.hpp"
#include "Pengu_Engine/ECS/Components/TransformComponent.hpp"
#include "Pengu_Engine/ECS/Components/ScriptComponent.hpp"
#include "Pengu_Engine/ECS/Systems/RenderSystem.hpp"
#include "Pengu_Engine/ECS/Systems/ScriptSystem.hpp"

#include "../src/common/Misc/imgui/imgui.h"
#include "../src/common/Misc/imgui/imgui_impl_glfw.h"
#include "../src/common/Misc/imgui/imgui_impl_opengl3.h"

#include "Pengu_Engine/Misc/FramRate.hpp"

#include <iostream>
#include <random>

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 960;
const int amount = 500;
float angle_x = 0.0f;
float angle_y = 0.0f;

int main() {
	std::optional<PenguEngine> mb_engine = PenguEngine::create(SCR_WIDTH, SCR_HEIGHT, "Scripting");

	if (!mb_engine) return 0;

	PenguEngine engine = std::move(mb_engine.value());

	Input& inp = engine.GetInput();

	auto ecs = engine.GetECS();

	auto ezreal = std::make_shared<Model>("../resource/object/ezreal/ezreal.obj");

	auto cube = std::make_shared<Model>("../resource/object/cube/cube.obj");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-50, 50);

	ecs->RegisterComponent<DrawableComponent>();
	ecs->RegisterComponent<TransformComponent>();
	ecs->RegisterComponent<ScriptingComponent>();

	auto rendersys = ecs->RegisterSystem<Renderer>();
	{
		Signature signature;
		signature.set(ecs->GetComponentType<DrawableComponent>());
		signature.set(ecs->GetComponentType<TransformComponent>());
		ecs->SetSystemSignature<Renderer>(signature);
	}

	auto scriptingsys = ecs->RegisterSystem<Scripting>();
	{
		Signature signature;
		signature.set(ecs->GetComponentType<ScriptingComponent>());
		ecs->SetSystemSignature<Scripting>(signature);
	}


	scriptingsys->Init(ecs, &inp);

	std::vector<Entity> entities(amount);

	for (auto& entity : entities) {
		entity = ecs->CreateEntity();

		ecs->AddComponent(entity, DrawableComponent(ezreal));
		ecs->AddComponent(entity, TransformComponent{ glm::vec3(distrib(gen), distrib(gen), distrib(gen)),glm::vec3(0.03f), glm::vec3(0.0f) });
		ecs->AddComponent(entity, ScriptingComponent("../data/scripts/entities.lua"));

		ecs->GetComponent<TransformComponent>(entity).projection_ = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	}

	auto player = ecs->CreateEntity();

	ecs->AddComponent(player, DrawableComponent(cube));
	ecs->AddComponent(player, TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)));
	ecs->AddComponent(player, ScriptingComponent("../data/scripts/player.lua"));

	ecs->GetComponent<TransformComponent>(player).projection_ = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	scriptingsys->Start();

	glEnable(GL_DEPTH_TEST);
	while (!engine.IsClosing() &&
		!inp.isDown(Action::Escape))
	{
		FrameRate::Get().FPSTick();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine.GetCamera().processInput(inp, (float)FrameRate::Get().GetDeltaTime());
		if (inp.isMouseDown(1))
		{
			engine.GetCamera().processMouseMovement((float)inp.mouseDeltaX(), (float)inp.mouseDeltaY());
		}

		engine.GetPanel().BeginFrame();

		scriptingsys->Update(FrameRate::Get().GetDeltaTime());

		rendersys->Render(ecs, engine.GetCamera());

		rendersys->ResetTex();

		engine.GetPanel().RenderPanel();
		engine.GetInput().update();
		engine.EndFrame();
	}
	engine.GetPanel().StopPanel();
}