#include "Pengu_Engine/Scene/Scene.hpp"
#include "Pengu_Engine/PenguEngine.hpp"
#include "Pengu_Engine/Scene/LightScene.hpp"
#include "Pengu_Engine/Misc/FramRate.hpp"

using Pengu::Core::PenguEngine;
using Pengu::Core::EngineConfig;

static EngineConfig config{ .screen_width = 1280, .screen_height = 960, .title = "Pengu_Engine" };

int main() {
	auto engine = PenguEngine::startEngine(config);

	engine.loadScene(std::make_unique<Pengu::Scene::LightScene>(&engine));

	while (!engine.IsClosing() &&
		!engine.GetInput().isDown(Action::Escape))
	{
		engine.update();
		engine.EndFrame();
	}
}