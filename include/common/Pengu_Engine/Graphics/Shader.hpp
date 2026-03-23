/**
 * @file Shader.hpp
 * @brief Simple OpenGL Shader program wrapper.
 */

#ifndef SHADER_HPP
#define SHADER_HPP 1

#include "gl/glew.h"

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>

 /**
	* @class Shader
	* @brief Manages the compilation, linking, and uniform distribution of GLSL shaders.
	* * This class encapsulates an OpenGL Program ID and provides a high-level
	* interface for sending data (uniforms) from the CPU to the GPU.
	*/
namespace Pengu::Graphics {

	class Shader {

	public:
		Shader() = default;

		void load(const std::string& vertexPath, const std::string& fragmentPath);
		void bind() const { glUseProgram(s_id); }
		void unbind() const { glUseProgram(0); }
		bool isValid() const { return s_id != 0; }

		/** @brief Set a boolean uniform. */
		void setBool(const std::string& name, bool value) const;

		/** @brief Set an integer uniform. */
		void setInt(const std::string& name, int value) const;

		/** @brief Set an unsigned integer uniform. */
		void setUInt(const std::string& name, unsigned int value) const;

		/** @brief Set a float uniform. */
		void setFloat(const std::string& name, float value) const;

		/** @brief Set a 2D vector uniform. */
		void setVec2(const std::string& name, const glm::vec2& value) const;
		/** @brief Set a 2D vector uniform using raw components. */
		void setVec2(const std::string& name, float x, float y) const;

		/** @brief Set a 3D vector uniform. */
		void setVec3(const std::string& name, const glm::vec3& value) const;
		/** @brief Set a 3D vector uniform using raw components. */
		void setVec3(const std::string& name, float x, float y, float z) const;

		/** @brief Set a 4D vector uniform. */
		void setVec4(const std::string& name, const glm::vec4& value) const;
		/** @brief Set a 4D vector uniform using raw components. */
		void setVec4(const std::string& name, float x, float y, float z, float w) const;

		/** @brief Set a 2x2 matrix uniform. */
		void setMat2(const std::string& name, const glm::mat2& mat) const;

		/** @brief Set a 3x3 matrix uniform. */
		void setMat3(const std::string& name, const glm::mat3& mat) const;

		/** @brief Set a 4x4 matrix uniform (standard for transformation matrices). */
		void setMat4(const std::string& name, const glm::mat4& mat) const;

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		Shader(Shader&& other) noexcept {
			s_id = other.s_id;
			s_locCache = std::move(other.s_locCache);
			other.s_id = 0;
		}

		~Shader() { unbind(); };
	private:
		unsigned int s_id; ///< Internal OpenGL Program ID handle.
		mutable std::unordered_map<std::string, int> s_locCache;

		int loc(const char* name);
		unsigned int compile(const char* src, GLenum type);
		void link(unsigned int vert, unsigned int frag);
		std::string readFile(const std::string& path);

	};
}//Pengu::Graphics

#endif // !SHADER_HPP
