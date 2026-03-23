#include "Pengu_Engine/PenguEngine.hpp"
#include "Pengu_Engine/Misc/AssetLoader.hpp"
#include "Pengu_Engine/Graphics/Model.hpp"
#include "Pengu_Engine/Graphics/Shader.hpp"
#include "Pengu_Engine/Misc/FramRate.hpp"
#include "Pengu_Engine/Misc/JobSystem.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <optional>
#include <thread>

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 960;
float angle_x = 0.0f;
float angle_y = 0.0f;

void InputCollection(Input& inp, glm::mat4& model_) {
	if (inp.isDown(Action::Arrow_Up)) {
		model_ = glm::translate(model_, glm::vec3(0.0f, 0.005f * (float)FrameRate::Get().GetDeltaTime(), 0.0f));
	}
	if (inp.isDown(Action::Arrow_Down)) {
		model_ = glm::translate(model_, glm::vec3(0.0f, -0.005f * (float)FrameRate::Get().GetDeltaTime(), 0.0f));
	}
	if (inp.isDown(Action::Arrow_Right)) {
		model_ = glm::translate(model_, glm::vec3(0.005f * (float)FrameRate::Get().GetDeltaTime(), 0.0f, 0.0f));
	}
	if (inp.isDown(Action::Arrow_Left)) {
		model_ = glm::translate(model_, glm::vec3(-0.005f * (float)FrameRate::Get().GetDeltaTime(), 0.0f, 0.0f));
	}
	if (inp.isDown(Action::X)) {
		model_ = glm::translate(model_, glm::vec3(0.0f, 0.0f, 0.005f * (float)FrameRate::Get().GetDeltaTime()));
	}
	if (inp.isDown(Action::Z)) {
		model_ = glm::translate(model_, glm::vec3(0.0f, 0.0f, -0.005f * (float)FrameRate::Get().GetDeltaTime()));
	}

	/** Rotetion **/
	if (inp.isDown(Action::T)) {
		model_ = glm::rotate(model_, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (inp.isDown(Action::G)) {
		model_ = glm::rotate(model_, -0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
	}

	if (inp.isDown(Action::F)) {
		model_ = glm::rotate(model_, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (inp.isDown(Action::H)) {
		model_ = glm::rotate(model_, -0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (inp.isDown(Action::R)) {
		model_ = glm::rotate(model_, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	if (inp.isDown(Action::Y)) {
		model_ = glm::rotate(model_, -0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

int main() {
	std::optional<PenguEngine> mb_engine = PenguEngine::create(SCR_WIDTH, SCR_HEIGHT, "Jobsystem");

	if (!mb_engine) return 0;

	PenguEngine engine = std::move(mb_engine.value());

	Input& inp = engine.GetInput();
	Camera& cam = engine.GetCamera();

	Shader shader;
	shader.loadShader("../data/shaders/generic.vert", "../data/shaders/generic.frag");

	std::vector<std::string> paths;

	paths.push_back("../resource/object/cube/cube.obj");
	paths.push_back("../resource/object/redpanda/red-panda.obj");
	paths.push_back("../resource/object/ezreal/ezreal.obj");
	paths.push_back("../resource/object/kindread/kindread.obj");

	unsigned int index = 0;
	bool IsChanging = false;

	JobSystem jb;

	std::future<CPUModel> model_to_load;

	Model current_model{ "../resource/object/cube/cube.obj" };

	glm::mat4 modelmat = glm::mat4(1.0f);
	modelmat = glm::translate(modelmat, glm::vec3(0.0f, 0.0f, -10.0f));
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)1280 / (float)960, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	while (!engine.IsClosing() &&
		!inp.isPressed(Action::Escape))
	{
		FrameRate::Get().FPSTick();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine.GetCamera().processInput(inp, (float)FrameRate::Get().GetDeltaTime());
		if (inp.isMouseDown(0))
		{
			engine.GetCamera().processMouseMovement((float)inp.mouseDeltaX(), (float)inp.mouseDeltaY());
		}

		InputCollection(inp, modelmat);

		if (inp.isDown(Action::N) && !IsChanging) {
			if (index < paths.size() - 1)
			{
				index += 1;
				IsChanging = true;
				model_to_load = jb.Enqueue([&path = paths[index]]() {return LoadCPUModelFromDisk(path); });
			}
		}

		if (inp.isDown(Action::B) && !IsChanging) {
			if (index > 0)
			{
				index -= 1;
				IsChanging = true;
				model_to_load = jb.Enqueue([&path = paths[index]]() {return LoadCPUModelFromDisk(path); });
			}
		}

		if (model_to_load.valid() &&
			model_to_load.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
		{
			CPUModel cpuData = model_to_load.get();
			current_model = CreateModel(cpuData);
			IsChanging = false;
		}

		shader.use();
		shader.setMat4("model", modelmat);
		shader.setMat4("view", cam.getViewMatrix());
		shader.setMat4("projection", projection);

		engine.GetPanel().BeginFrame();

		current_model.Draw(shader);

		engine.GetPanel().RenderPanel();
		engine.GetInput().update();
		engine.EndFrame();
	}
	engine.GetPanel().StopPanel();

}