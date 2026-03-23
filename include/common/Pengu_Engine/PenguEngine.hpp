/**
 * @file PenguEngine.hpp
 * @brief Main entry point and orchestrator for the Pengu Engine core systems.
 */

#ifndef PENGUENGINE_HPP 
#define PENGUENGINE_HPP 1

#include "Pengu_Engine/Window/Window.hpp"
#include "Pengu_Engine/Inputs/Input.hpp"
#include "Pengu_Engine/Misc/StatPanel.hpp"
#include "Pengu_Engine/Camera/Camera.hpp"
#include "Pengu_Engine/Misc/Logger.hpp"

#include "Pengu_Engine/Managers/Resource/ResourceManager.hpp"
#include "Pengu_Engine/Scene/SceneManager.hpp"
#include "Pengu_Engine/Graphics/Rendering/Renderer.hpp"
#include "Pengu_Engine/Scene/SceneBase.hpp"

#include <string>
#include <optional>

namespace Pengu::Resources { class ResourceManager; }
namespace Pengu::Scene { class SceneManager; class SceneBase; }
namespace Pengu::Graphics::Rendering { class Renderer; }

namespace Pengu::Core {

	struct EngineConfig {
		unsigned int screen_width;
		unsigned int screen_height;
		std::string title;
		float cam_speed = 0.005f;
		float fov = 90.0f;
		float cam_sens = 0.1f;
	};

	/**
	 * @class PenguEngine
	 * @brief The central class that manages the lifecycle of all engine subsystems.
	 * * PenguEngine follows a move-only pattern to ensure unique ownership of
	 * hardware resources like the window context and input listeners.
	 */
	class PenguEngine {
	public:
		PenguEngine(const PenguEngine&) = delete;
		PenguEngine& operator=(const PenguEngine&) = delete;

		PenguEngine(PenguEngine&&);
		PenguEngine& operator=(PenguEngine&&);

		~PenguEngine();

		/// @name Factory Methods
		/// @{
		/**
		 * @brief Creates an engine instance with custom window parameters.
		 * @param width The width of the window in pixels.
		 * @param height The height of the window in pixels.
		 * @param title The title displayed on the window bar.
		 * @return An optional containing the engine instance if successful.
		 */
		static std::optional<PenguEngine> create(const EngineConfig& config);

		static PenguEngine startEngine(const EngineConfig& config);

		/**
		 * @brief Checks if the engine's window has been requested to close.
		 * @return True if the user or OS requested a close, false otherwise.
		 */
		bool IsClosing() const;

		/**
		 * @brief Finalizes the current frame.
		 * * Swaps buffers, polls events, and clears the per-frame allocators.
		 */
		void EndFrame();

		/// @}

		/// @name System Accessors
		/// @{

		/** @brief Returns a reference to the window management system. */
		Window& GetWindow() { return *m_window; }
		Input& GetInput() { return *m_input; }
		StatPanel& GetPanel() { return *panel_; }
		Camera& GetCamera() { return m_camera; }
		Logger& Log() { return log_; }
		Pengu::Resources::ResourceManager& GetResourceManager();
		Pengu::Scene::SceneManager& getSceneManager();
		Pengu::Graphics::Rendering::Renderer& getRenderer();


		void loadScene(std::unique_ptr<Pengu::Scene::SceneBase> scene);

		Pengu::Scene::SceneBase* getActiveScene();

		void update();

	private:
		/**
		 * @brief Private constructor used by the static create() factory methods.
		 */
		PenguEngine(std::unique_ptr<Window> window,
			std::unique_ptr<Input> input,
			std::unique_ptr<StatPanel> panel,
			Camera                      camera,
			Logger                      log,
			std::unique_ptr<Pengu::Resources::ResourceManager> rm,
			std::unique_ptr<Pengu::Scene::SceneManager> scenemanager,
			std::unique_ptr<Pengu::Graphics::Rendering::Renderer> renderer
		);

		std::unique_ptr<Window> m_window;    ///< The GLFW window context.
		std::unique_ptr<Input> m_input;      ///< Keyboard and Mouse input state.
		std::unique_ptr<StatPanel> panel_;  ///< UI overlay for engine performance stats.
		Camera m_camera;											///< The primary viewing camera.
		Logger log_;
		std::unique_ptr<Pengu::Resources::ResourceManager> m_resourceManager;
		std::unique_ptr<Pengu::Scene::SceneManager> m_scenemanager;
		std::unique_ptr<Pengu::Graphics::Rendering::Renderer> m_renderer;
		// Add all the other systems
	};
}
#endif // !PENGUENGINE_HPP