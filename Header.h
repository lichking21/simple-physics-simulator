#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Simu {

public:
	sf::RectangleShape square;
	sf::RectangleShape floor;
	sf::CircleShape circle;
	sf::Sprite sprite;

	sf::Vector2f centerMouse(sf::RenderWindow& window, sf::RectangleShape obj); // Centers mouse position inside object
	void draw(sf::RenderWindow& window); // Draw object :/
	void collision(sf::RenderWindow& window, sf::RectangleShape& obj); // Objects collision with window borders

	void gravity(sf::RectangleShape& obj); // Gravitation Force
	void mechWork(sf::RectangleShape& obj); // Mechanical Work
};


#endif

