#ifndef SPHERE_HPP
#define SPHERE_HPP 1

#include "Pengu_Engine/Graphics/Mesh.hpp"

struct SphereData {
	std::vector<Pengu::Graphics::Vertex> vertices;
	std::vector<unsigned int> indices;
};

class Sphere {
public:
	Sphere(const float size, const int height, const int revs);
	SphereData m_data;
};

#endif // !SPHERE_HPP
