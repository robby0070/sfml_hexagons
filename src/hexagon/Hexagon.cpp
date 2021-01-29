#include "hexagon/Hexagon.hpp"

#include <utility>
#include <cassert>
#include <cmath>

#define EDGES 6

namespace sf {

Hexagon::Hexagon() :
	m_vertices(TriangleFan, EDGES + 2), //1 center + 6 vertexes + 1 to close the shape
	m_radius(0)
{ }

Hexagon::Hexagon(Vector2f center, float radius, float outline_thickness, 
				const Texture &texture) :
	m_vertices(TriangleFan, EDGES + 2), //1 center + 6 vertexes + 1 to close the shape
	m_outline(TriangleStrip, EDGES * 2 + 2) 
{
	assert(radius >= 0);
	m_vertices[0].position = center;
	m_radius = radius;
	set_outline_thickness(outline_thickness);
	set_texture(texture);
	calc_vertices();
}

Hexagon::Hexagon(const Hexagon &h) {
	assert(h.m_radius >= 0);
	m_vertices = h.m_vertices;
	m_outline = h.m_outline;
	m_radius = h.m_radius;
	m_texture = h.m_texture;
}

bool Hexagon::set_radius(float radius) {
	if (radius < 0) 
		return false;

	m_radius = radius;
	calc_vertices();
	return true;
}

void Hexagon::set_center(Vector2f center) {
	m_vertices[0].position = center;
	calc_vertices();
}

void Hexagon::set_texture(const Texture &t) {
	m_texture = t;
	float quarter_width = (m_texture.getSize().x) / 4;
	float quarter_height = (m_texture.getSize().y) / 4;

	const static std::array<std::pair<float, float>, EDGES + 1>
		texture_points = {{
		{ 2,  2 },
		{ 4,  1 },
		{ 4,  3 },
		{ 2,  4 },
		{ 0,  3 },
		{ 0,  1 },
		{ 2,  0 },
	}};
	
	for (int i = 0; i < texture_points.size(); ++i) {
		m_vertices[i].texCoords.x = texture_points[i].first * quarter_width;
		m_vertices[i].texCoords.y = texture_points[i].second * quarter_height;
	}
	m_vertices[7].texCoords = m_vertices[1].texCoords;
}

bool Hexagon::set_outline_thickness(float outline_thickness) {
	if (outline_thickness < 0)
		return false;
	m_outline_thickness = outline_thickness;
	calc_vertices();
	return true;
} 

void Hexagon::calc_vertices() {
	const auto &center = m_vertices[0].position;

	for (int i = 1; i <= EDGES; ++i) {
		float angle_deg = 60 * (i-1) - 30;
		float angle_rad = M_PI / 180 * angle_deg;
		m_vertices[i].position.x = center.x + m_radius * cos(angle_rad);
		m_vertices[i].position.y = center.y + m_radius * sin(angle_rad); 
	}
	m_vertices[EDGES + 1].position = m_vertices[1].position;


	float long_edge = m_outline_thickness;
	float short_edge = long_edge / sqrt(3);
	float hypotenus = short_edge * 2;	

	for (int i = 0; i <= EDGES * 2; i+=2) {
		m_outline[i].position = m_vertices[(i / 2) + 1].position;
	}

	const std::array<std::pair<int, int>, EDGES> offsets = {{
			{ -long_edge, +short_edge },
			{ -long_edge, -short_edge },
			{ 0, -hypotenus },
			{ +long_edge, -short_edge },
			{ +long_edge, +short_edge },
			{ +0, +hypotenus },
	}};

	for (int i = 0; i < EDGES * 2; i+=2) {
		m_outline[i+1].position = {
			m_outline[i].position.x + offsets[i/2].first,
			m_outline[i].position.y + offsets[i/2].second,
		};
	}

	m_outline[13].position = m_outline[1].position;
}

void Hexagon::draw(RenderTarget &target, RenderStates states) const {
	states.texture = &m_texture;
	target.draw(m_vertices, states);
	states.texture = nullptr;
	target.draw(m_outline, states);
}

}