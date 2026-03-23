#include "Pengu_Engine/PenguEngine.hpp"
#include "Pengu_Engine/Misc/FramRate.hpp"
#include "Pengu_Engine/Graphics/Mesh.hpp"
#include "Pengu_Engine/Graphics/Model.hpp"
#include "Pengu_Engine/Graphics/Shader.hpp"
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <optional>

int main() {

	std::optional<PenguEngine> aux_e = PenguEngine::create(1280, 960, "Triangle_Example");

	if (!aux_e) return 0;

	PenguEngine engine = std::move(aux_e.value());

	Shader shader;
	shader.loadShader("../data/shaders/triangle.vert", "../data/shaders/triangle.frag");

	Mesh tri;
	tri.MakeTriangle();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)1280 / (float)960, 0.1f, 100.0f);

	while (!engine.IsClosing() &&
		!engine.GetInput().isDown(Action::Escape)) {

		FrameRate::Get().FPSTick();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		shader.setMat4("model", model);
		shader.setMat4("projection", projection);
		shader.setMat4("view", engine.GetCamera().getViewMatrix());

		engine.GetPanel().BeginFrame();

		tri.Draw(shader);

		engine.GetPanel().RenderPanel();
		engine.GetInput().update();
		engine.EndFrame();
	}

	engine.GetPanel().StopPanel();

	return 0;
}