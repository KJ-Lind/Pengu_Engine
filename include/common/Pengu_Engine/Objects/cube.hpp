#ifndef CUBE_HPP
#define CUBE_HPP 1

#include "Pengu_Engine/Graphics/Mesh.hpp"

struct CubeData {
	std::vector<Pengu::Graphics::Vertex> vertices;
	std::vector<unsigned int> indices;
};

class Cube
{

public:
	Cube(const float size) : m_size(size) {};

	void init8v();
	void init24v();

	float m_size;
	CubeData m_data;
};

#endif // !CUBE_HPP
