#ifndef MESH_HPP
#define MESH_HPP 1

#include "glm/glm.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <vector>
#include <string>
namespace Pengu::Graphics {

	/**
	* @struct Vertex
	* @brief Representation of a single vertex point in 3D space.
	*/
	struct Vertex {
		glm::vec3 position;  ///< 3D coordinates of the vertex.
		glm::vec3 normal;   ///< Normal vector for lighting calculations.
		glm::vec2 uv; ///< UV coordinates for texture mapping.
	};

	/**
	* @class Mesh
	 * @brief Manages vertex data buffers and executes draw calls.
	 * * This class encapsulates the OpenGL VAO, VBO, and EBO/IBO to simplify
	 * the process of sending geometry to the GPU.
	*/
	class Mesh {

	public:
		Mesh() = default;

		bool loadFromAssimp(aiMesh* mesh);
		void Draw(bool bWireFrame);

		bool isValid() const {
			if (m_indexCount > 0 && m_vertexCount > 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		unsigned int indexCount() const { return m_indexCount; }
		unsigned int vertexCount() const { return m_vertexCount; }
		bool isUploaded() const { return m_vao != 0; }

		~Mesh();
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		Mesh(Mesh&& other) noexcept {
			m_vao = other.m_vao;
			m_vbo = other.m_vbo;
			m_ebo = other.m_ebo;
			m_indexCount = other.m_indexCount;
			m_vertexCount = other.m_vertexCount;
			other.m_vao = other.m_vbo = other.m_ebo = 0;
		}

		void upload(const std::vector<Vertex>& vertices,
			const std::vector<unsigned int>& indices);
	private:
		void processMesh(aiMesh* mesh);
		void uploadToGPU();

		std::vector<Vertex>   m_vertices;
		std::vector<unsigned int> m_indices;

		unsigned int m_vao = 0;
		unsigned int m_vbo = 0;
		unsigned int m_ebo = 0;
		unsigned int m_indexCount = 0;
		unsigned int m_vertexCount = 0;
	};
}//Pengu::Graphics

#endif // !MESH_HPP
