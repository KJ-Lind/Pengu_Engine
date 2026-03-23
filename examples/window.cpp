#include "Pengu_Engine/PenguEngine.hpp"
#include "Pengu_Engine/Misc/FramRate.hpp"
#include "Pengu_Engine/Misc/Logmacros.hpp"
#include <optional>

int main() {

	std::optional<PenguEngine> aux_e = PenguEngine::create(640, 480, "Window_Example");

	if (!aux_e) return 0;

	PenguEngine engine = std::move(aux_e.value());

	while (!engine.IsClosing()) {

		FrameRate::Get().FPSTick();

		glClearColor(0.48f, 0.25f, 0.52f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine.GetPanel().BeginFrame();
		engine.GetPanel().RenderPanel();
		engine.EndFrame();
	}
	engine.GetPanel().StopPanel();
	return 0;
}