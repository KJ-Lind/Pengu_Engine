/**
 * @file Camera.hpp
 * @brief 3D First-Person/Free-fly camera system.
 * @details Manages the view matrix generation using Euler angles (Yaw, Pitch)
 * and handles movement logic based on engine input.
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP 1

#include "GL/glew.h"
#include "Pengu_Engine/Inputs/Input.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

 /** * @enum CamMovement
	* @brief Directions for relative camera movement.
	*/
enum CamMovement {
	kForward,
	kBackward,
	kLeft,
	kRight
};

// Default camera constants
const float YAW = -90.0f;  ///< Default horizontal rotation (facing -Z).
const float PITCH = 0.0f;   ///< Default vertical rotation.
const float SPEED = 0.01f;  ///< Default movement speed.
const float SENSITIVITY = 0.1f;   ///< Default mouse look sensitivity.
const float ZOOM = 45.0f;  ///< Default Field of View (FOV).

/**
 * @class Camera
 * @brief Processes input and calculates the corresponding View Matrix for OpenGL.
 * @details The camera uses Euler angles to calculate its Front, Right, and Up vectors.
 * It integrates with the Pengu_Engine::Input system for movement and rotation.
 */
class Camera {

public:

	Camera()
	{
		updateCameraVectors();
	}

	~Camera() = default;

	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	Camera(Camera&&) = default;
	Camera& operator=(Camera&&) = default;

	/**
	 * @brief Calculates the view matrix using the LookAt algorithm.
	 * @return glm::mat4 The transformation matrix representing the camera's view.
	 */
	glm::mat4 getViewMatrix();

	glm::vec3 getPosition() { return position_; };

	void CreatePrespective(int screen_width, int screen_height);

	/**
	 * @brief Processes keyboard-style movement input.
	 * @param input Reference to the Input system.
	 * @param deltaTime Time elapsed since last frame to ensure smooth movement.
	 */
	void processInput(Input& input, float deltaTime);

	/**
	 * @brief Processes mouse movement for camera rotation.
	 * @param xoffset Horizontal mouse displacement.
	 * @param yoffset Vertical mouse displacement.
	 * @param constraintPitch If true, prevents the camera from flipping over (90 to -90 degrees).
	 */
	void processMouseMovement(float xoffset, float yoffset, GLboolean constraintPitch = true);

	/**
	 * @brief Processes scroll wheel input to adjust zoom (FOV).
	 * @param yoffset The scroll displacement.
	 */
	void processMouseScroll(float yoffset);

	// --- Public Members ---

	glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 3.0f); // pulled back on Z so scene is visible
	glm::vec3 front_ = glm::vec3(0.0f, 0.0f, -1.0f); // looking into the scene
	glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right_ = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 worldUp_ = glm::vec3(0.0f, 1.0f, 0.0f); // this was also zero!
	glm::mat4 projection_;

	/** @brief Sets the movement speed with internal clamping. */
	void Set_CamSpeed(float speed) { movSpeed_ = glm::clamp(speed, 0.0f, 0.5f); };
	/** @brief Gets the current movement speed. */
	float Get_CamSpeed() { return movSpeed_; };

	/** @brief Sets the look sensitivity with internal clamping. */
	void Set_CamSens(float sens) { mouseSens_ = glm::clamp(sens, 0.0f, 0.5f); };
	/** @brief Gets the current look sensitivity. */
	float Get_CamSens() { return mouseSens_; };

	float yaw_ = YAW;        ///< Horizontal Euler angle (in degrees).
	float pitch_ = PITCH;      ///< Vertical Euler angle (in degrees).
	float movSpeed_ = SPEED;   ///< Current speed multiplier for movement.
	float mouseSens_ = SENSITIVITY;  ///< Multiplier for mouse rotation speed.
	float zoom_ = ZOOM;       ///< Current Field of View (FOV).

private:
	/**
	 * @brief Re-calculates the Front, Right, and Up vectors based on updated Euler angles.
	 * @details Uses trigonometric functions to derive the front vector, then cross
	 * products to find Right and Up.
	 */
	void updateCameraVectors();

	float m_presp_radius;
	float m_presp_scr_width;
	float m_presp_scr_height;
	float m_presp_near;
	float m_presp_far;

};

#endif // !CAMERA_HPP