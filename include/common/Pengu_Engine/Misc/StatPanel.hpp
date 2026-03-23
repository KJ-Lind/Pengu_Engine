/**
 * @file StatPanel.hpp
 * @brief Debugging UI and performance telemetry panel.
 * @details Handles the initialization and rendering of the on-screen stats panel.
 * This is typically used to display FPS, frame times, and engine internal states.
 */

#ifndef STATPANEL_HPP
#define STATPANEL_HPP 1

#include "glfw/glfw3.h"
#include <optional>

 /**
	* @class StatPanel
	* @brief Orchestrates the debug UI overlay for the engine.
	* @details The StatPanel follows a factory pattern for initialization to ensure
	* the GLFW context is valid before the UI system (like ImGui) starts.
	*/
class StatPanel {

public:
	explicit StatPanel(GLFWwindow* window);
	/// @name Deleted Operations
	/// @{
	StatPanel(const StatPanel& other) = delete;
	StatPanel& operator = (const StatPanel& other) = delete;
	/// @}

	/// @name Move Semantics
	/// @{
	StatPanel(StatPanel&& other) noexcept;
	StatPanel& operator = (StatPanel&& other) noexcept;
	/// @}

	/**
	 * @brief Initializes a new UI frame.
	 * @note This must be called at the very beginning of your render loop,
	 * before any UI widgets are defined.
	 */
	void BeginFrame();

	/**
	 * @brief Renders the actual UI widgets and performance data.
	 * @details This method contains the logic for drawing graphs, text,
	 * and buttons to the overlay.
	 */
	void RenderPanel();

	/**
	 * @brief Destructor. Cleans up UI context and resources.
	 */
	~StatPanel();

};

#endif // !STATPANEL_HPP