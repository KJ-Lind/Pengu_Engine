#ifndef QUAD_HPP
#define QUAD_HPP

#include "Pengu_Engine/Graphics/Mesh.hpp"

struct QuadData {
	std::vector<Pengu::Graphics::Vertex> vertices;
	std::vector<unsigned int> indices;
};

class Quad {
public:
	Quad(const float size);
	QuadData m_data;
};

#endif // !QUAD_HPP
