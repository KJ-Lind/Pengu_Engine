#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP 1

#include "Pengu_Engine/Graphics/Mesh.hpp"
#include "Pengu_Engine/Graphics/Material.hpp"
#include <memory>
#include <vector>

struct SubMeshes {
	Pengu::Graphics::Mesh mesh_;
	Pengu::Graphics::Material material_;

	bool visible = true;
};

class GameObject {
public:
	GameObject() = default;
	~GameObject() { subMeshes.clear(); };

	std::vector<SubMeshes> subMeshes;

	void addSubMesh(std::shared_ptr<Pengu::Graphics::Mesh> mesh,
		std::shared_ptr<Pengu::Graphics::Material> mat);

	bool visible = true;
};

#endif // !GAMEOBJECT_HPP
