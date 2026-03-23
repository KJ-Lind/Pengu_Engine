#include "Pengu_Engine/PenguEngine.hpp"
#include "Pengu_Engine/Misc/AssetLoader.hpp"
#include "Pengu_Engine/Graphics/Model.hpp"
#include "Pengu_Engine/Graphics/Shader.hpp"
#include "Pengu_Engine/ECS/ECSManager.hpp"
#include "Pengu_Engine/ECS/Components/DrawableComponent.hpp"
#include "Pengu_Engine/ECS/Components/TransformComponent.hpp"
#include "Pengu_Engine/ECS/Systems/RenderSystem.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Pengu_Engine/Misc/FramRate.hpp"

#include <optional>
#include <random>

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 960;
const int amount = 5000;
float angle_x = 0.0f;
float angle_y = 0.0f;

int main() {
	std::optional<PenguEngine> mb_engine = PenguEngine::create(SCR_WIDTH, SCR_HEIGHT, "ECS_Manager");

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

	auto rendersys = ecs->RegisterSystem<Renderer>();

	Signature signature;
	signature.set(ecs->GetComponentType<DrawableComponent>());
	signature.set(ecs->GetComponentType<TransformComponent>());
	ecs->SetSystemSignature<Renderer>(signature);

	std::vector<Entity> entities(amount);

	for (auto& entity : entities) {
		entity = ecs->CreateEntity();

		ecs->AddComponent(entity, DrawableComponent(ezreal));
		ecs->AddComponent(entity, TransformComponent{ glm::vec3(distrib(gen), distrib(gen), distrib(gen)),glm::vec3(0.03f), glm::vec3(0.0f) });

		ecs->GetComponent<TransformComponent>(entity).projection_ = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	}

	auto player = ecs->CreateEntity();

	ecs->AddComponent(player, DrawableComponent(cube));
	ecs->AddComponent(player, TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)));

	ecs->GetComponent<TransformComponent>(player).projection_ = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

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

		for (auto& entity : entities) {
			ecs->GetComponent<TransformComponent>(entity).rotation_.y += 0.001f * (float)FrameRate::Get().GetDeltaTime();
		}

		if (inp.isDown(Action::Arrow_Up)) {
			ecs->GetComponent<TransformComponent>(player).position_.z += 0.005f * (float)FrameRate::Get().GetDeltaTime();
		}
		if (inp.isDown(Action::Arrow_Down)) {
			ecs->GetComponent<TransformComponent>(player).position_.z -= 0.005f * (float)FrameRate::Get().GetDeltaTime();
		}
		if (inp.isDown(Action::Arrow_Right)) {
			ecs->GetComponent<TransformComponent>(player).position_.x += 0.005f * (float)FrameRate::Get().GetDeltaTime();
		}
		if (inp.isDown(Action::Arrow_Left)) {
			ecs->GetComponent<TransformComponent>(player).position_.x -= 0.005f * (float)FrameRate::Get().GetDeltaTime();
		}
		if (inp.isDown(Action::Q)) {
			ecs->GetComponent<TransformComponent>(player).position_.y += 0.005f * (float)FrameRate::Get().GetDeltaTime();
		}
		if (inp.isDown(Action::E)) {
			ecs->GetComponent<TransformComponent>(player).position_.y -= 0.005f * (float)FrameRate::Get().GetDeltaTime();
		}

		rendersys->shader_.setMat4("view", engine.GetCamera().getViewMatrix());

		engine.GetPanel().BeginFrame();

		rendersys->Render(ecs);

		rendersys->ResetTex();

		engine.GetPanel().RenderPanel();
		engine.GetInput().update();
		engine.EndFrame();
	}
	engine.GetPanel().StopPanel();
}