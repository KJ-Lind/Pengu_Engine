#include "Pengu_Engine/PenguEngine.hpp"
#include "Pengu_Engine/Inputs/Input.hpp"
#include "Pengu_Engine/Misc/FramRate.hpp"
#include "Pengu_Engine/Graphics/Mesh.hpp"
#include "Pengu_Engine/Graphics/Model.hpp"
#include <iostream>
#include <glm/glm.hpp>

int main() {


	std::optional<PenguEngine> aux_e = PenguEngine::create(1280, 960, "Input_Example");

	if (!aux_e) return 0;

	PenguEngine engine = std::move(aux_e.value());

	Input& inp = engine.GetInput();

	Shader shader;
	shader.loadShader("../data/shaders/triangle.vert", "../data/shaders/triangle.frag");

	Mesh tri;
	tri.MakeTriangle();
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)1280 / (float)960, 0.1f, 100.0f);


	glm::vec3 pos = { 0.0f,0.0f,-1.0f };
	float rotation = 0.0f;
	float scale = 1.0f;


	while (!engine.IsClosing() &&
		!inp.isDown(Action::Escape)) {

		FrameRate::Get().FPSTick();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float dt = (float)FrameRate::Get().GetDeltaTime();

		if (inp.isDown(Action::Up)) {
			pos.y += 0.0025f * dt;
		}
		if (inp.isDown(Action::Down)) {
			pos.y -= 0.0025f * dt;
		}
		if (inp.isDown(Action::Right)) {
			pos.x += 0.0025f * dt;
		}
		if (inp.isDown(Action::Left)) {
			pos.x -= 0.0025f * dt;
		}

		if (inp.isDown(Action::Q)) {
			rotation += 0.0025f * dt;
		}
		if (inp.isDown(Action::E)) {
			rotation -= 0.0025f * dt;
		}

		if (inp.isDown(Action::Arrow_Up)) {
			scale += 0.0025f * dt;
		}
		if (inp.isDown(Action::Arrow_Down)) {
			scale -= 0.0025f * dt;
		}

		scale = glm::max(scale, 0.1f);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));


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