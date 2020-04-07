#include "hexagon/CubeCoord.hpp"
#include "hexagon/Hexagon.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <cmath>

int main() {
	sf::RenderWindow game_window(sf::VideoMode(640, 480), "giocobello");

	sf::Texture texture;
	texture.loadFromFile("img2.jpeg");

	std::unordered_map<CubeCoord, sf::Hexagon> map;
	float radius = 50.;
	int width = 10;
	int height = 5;
	for (int r = 0; r < height; r++) {
		int r_offset = floor(r/2); 
		for (int q = -r_offset; q < width - r_offset; q++) {
			CubeCoord coord (q, r, -(q + r));
			auto center = coord.to_pixel(radius);
			sf::Vector2f sf_center = { center.first, center.second};
			map.insert({coord, {sf_center, radius, 0, texture}});
		}
	}

	while (game_window.isOpen()) {
		sf::Event event;
		while (game_window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::KeyPressed:
					break;

				case sf::Event::KeyReleased:
					break;

				case sf::Event::Closed:
					game_window.close();
					break;
				case sf::Event::MouseButtonPressed:
					auto coordinate = CubeCoord::from_pixel(event.mouseButton.x, event.mouseButton.y, radius);
					std::cout << "q: " << coordinate.m_q << "\tr: " << coordinate.m_r << "\ts:" << coordinate.m_s << std::endl;
					std::cout << "ciao" << std::endl;
					map[coordinate].set_outline_thickness(10);
					break;
			}
		}
		game_window.clear();
		for (auto elem : map) {
			game_window.draw(elem.second);
		}
		game_window.display();
	}
	return 0;
}