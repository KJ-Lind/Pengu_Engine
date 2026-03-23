#include "Pengu_Engine/PenguEngine.hpp"
#include "Pengu_Engine/Misc/AssetLoader.hpp"
#include "Pengu_Engine/Graphics/Model.hpp"
#include "Pengu_Engine/Graphics/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Pengu_Engine/Misc/FramRate.hpp"

#include <optional>

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 960;



int main() {
	std::optional<PenguEngine> mb_engine = PenguEngine::create(SCR_WIDTH, SCR_HEIGHT, "Asset_Loader");

	if (!mb_engine) return 0;

	PenguEngine engine = std::move(mb_engine.value());

	Input& inp = engine.GetInput();
	Camera& cam = engine.GetCamera();

	Model tmp("../resource/object/kindread/kindread.obj");

	Shader shaders;
	shaders.loadShader("../data/shaders/generic.vert", "../data/shaders/generic.frag");

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, -5.0f)); // translate it down so it's at the center of the scene
	model = glm::rotate(model, -1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));	// it's a bit too big for our scene, so scale it down

	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	float angle_x = 0.0f;
	float angle_y = 0.0f;
	float angle_z = 0.0f;

	glEnable(GL_DEPTH_TEST);
	while (!engine.IsClosing() &&
		!inp.isPressed(Action::Escape))
	{
		FrameRate::Get().FPSTick();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.processInput(inp, (float)FrameRate::Get().GetDeltaTime());
		if (inp.isMouseDown(0))
		{
			cam.processMouseMovement((float)inp.mouseDeltaX(), (float)inp.mouseDeltaY());
		}
		if (inp.isDown(Action::Shift)) {
			cam.movSpeed_ += (float)inp.scrollYOffset() * 0.0001f;
		}

		/** Movement **/
		if (inp.isDown(Action::Arrow_Up)) {
			model = glm::translate(model, glm::vec3(0.0f, 0.005f * (float)FrameRate::Get().GetDeltaTime(), 0.0f));
		}
		if (inp.isDown(Action::Arrow_Down)) {
			model = glm::translate(model, glm::vec3(0.0f, -0.005f * (float)FrameRate::Get().GetDeltaTime(), 0.0f));
		}
		if (inp.isDown(Action::Arrow_Right)) {
			model = glm::translate(model, glm::vec3(0.005f * (float)FrameRate::Get().GetDeltaTime(), 0.0f, 0.0f));
		}
		if (inp.isDown(Action::Arrow_Left)) {
			model = glm::translate(model, glm::vec3(-0.005f * (float)FrameRate::Get().GetDeltaTime(), 0.0f, 0.0f));
		}
		if (inp.isDown(Action::X)) {
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.005f * (float)FrameRate::Get().GetDeltaTime()));
		}
		if (inp.isDown(Action::Z)) {
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.005f * (float)FrameRate::Get().GetDeltaTime()));
		}

		/** Rotetion **/
		if (inp.isDown(Action::T)) {
			model = glm::rotate(model, 0.001f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (inp.isDown(Action::G)) {
			model = glm::rotate(model, -0.001f, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		if (inp.isDown(Action::H)) {
			model = glm::rotate(model, 0.001f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (inp.isDown(Action::F)) {
			model = glm::rotate(model, -0.001f, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (inp.isDown(Action::R)) {
			model = glm::rotate(model, 0.001f, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (inp.isDown(Action::Y)) {
			model = glm::rotate(model, -0.001f, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		shaders.setMat4("model", model);
		shaders.setMat4("view", cam.getViewMatrix());
		shaders.setMat4("projection", projection);

		engine.GetPanel().BeginFrame();

		tmp.Draw(shaders);

		engine.GetPanel().RenderPanel();

		engine.GetInput().update();

		engine.EndFrame();
	}
	engine.GetPanel().StopPanel();

}