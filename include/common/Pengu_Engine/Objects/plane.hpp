#ifndef PLANE_HPP
#define PLANE_HPP 1

#include "Pengu_Engine/Graphics/Mesh.hpp"

struct PlaneData {
	std::vector<Pengu::Graphics::Vertex> vertices;
	std::vector<unsigned int> indices;
};

class Plane {

public:
	Plane(int rows, int cols, int size);
	PlaneData data_;
};

#endif // !PLANE_HPP
