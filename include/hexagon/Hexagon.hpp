#ifndef  HEXAGON
#define HEXAGON

#include <SFML/Graphics.hpp>

namespace sf {

class Hexagon : public sf::Drawable {
	public:
		Hexagon();
		Hexagon(const Hexagon &h);
		Hexagon(Vector2f center, float radius, float m_outline_thickness = 0,
				const Texture &texture = Texture());
		~Hexagon() = default;

		bool set_radius(float radius);
		float get_radius() const { return m_radius; };

		void set_center(Vector2f center);
		const Vector2f get_center() const { return m_vertices[0].position; };
		
		void set_texture(const Texture &t);

		bool set_outline_thickness(float outline_thickness);

	private:
		void calc_vertices();
		virtual void draw(RenderTarget &target, RenderStates) const;

		VertexArray m_vertices;
		float m_radius;

		Texture m_texture;
		VertexArray m_outline;
		float m_outline_thickness;
};

}
#endif 