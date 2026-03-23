#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP 1

#include <memory>
#include <string>
#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Pengu_Engine/Graphics/Mesh.hpp"
#include "Pengu_Engine/Graphics/Texture.hpp"
#include "Pengu_Engine/Graphics/Material.hpp"
#include "Pengu_Engine/Graphics/Shader.hpp"
#include "Pengu_Engine/Graphics/GameObject.hpp"

namespace Pengu::Resources {

	class ResourceManager {
	public:
		ResourceManager() = default;
		ResourceManager(const ResourceManager& rvalue) = delete;
		ResourceManager& operator = (const ResourceManager& rvalue) = delete;

		ResourceManager(ResourceManager&& rvalue) noexcept : m_meshes(std::move(rvalue.m_meshes)),
			m_textures(std::move(rvalue.m_textures)), m_shaders(std::move(rvalue.m_shaders)), m_materials(std::move(rvalue.m_materials))
		{
		};
		ResourceManager& operator = (ResourceManager&& rvalue) noexcept
		{
			if (this != &rvalue)
			{
				m_meshes = std::move(rvalue.m_meshes);
				m_textures = std::move(rvalue.m_textures);
				m_shaders = std::move(rvalue.m_shaders);
				m_materials = std::move(rvalue.m_materials);
			}

			return *this;
		};
		~ResourceManager();

		std::shared_ptr<Pengu::Graphics::Mesh> getMesh(const std::string& name,
			const std::vector<Pengu::Graphics::Vertex>& vertices,
			const std::vector<unsigned int>& indices);
		std::shared_ptr<Pengu::Graphics::Texture> getTexture(const std::string& path);
		std::shared_ptr<Pengu::Graphics::Shader> getShader(const std::string& vertPath,
			const std::string& fragPath);
		std::shared_ptr<Pengu::Graphics::Material> getMaterial(const std::string& name);

		std::shared_ptr<GameObject> loadObject(const std::string& path);

		std::shared_ptr<GameObject> CreatePlane(const std::string& name, int rows, int cols, int size, std::shared_ptr<Pengu::Graphics::Material> mat);

		std::shared_ptr<GameObject> CreateCube8v(const std::string& name, const int size, std::shared_ptr<Pengu::Graphics::Material> mat);
		std::shared_ptr<GameObject> CreateCube24v(const std::string& name, const int size, std::shared_ptr<Pengu::Graphics::Material> mat);

		std::shared_ptr<GameObject> CreateQuad(const std::string& name, const int size, std::shared_ptr<Pengu::Graphics::Material> mat);
		std::shared_ptr<GameObject> CreateSphere(const std::string& name, const float size, const int height, const int revs, std::shared_ptr<Pengu::Graphics::Material> mat);


	private:

		std::shared_ptr<Pengu::Graphics::Material> extractMaterial(aiMaterial* aiMat,
			const std::string& dir);

		std::unordered_map<std::string, std::weak_ptr<Pengu::Graphics::Mesh>>     m_meshes;
		std::unordered_map<std::string, std::weak_ptr<Pengu::Graphics::Texture>>  m_textures;
		std::unordered_map<std::string, std::weak_ptr<Pengu::Graphics::Shader>>   m_shaders;
		std::unordered_map<std::string, std::weak_ptr<Pengu::Graphics::Material>> m_materials;
	};
}// Pengu::Resources

#endif // !RESOURCEMANAGER_HPP
