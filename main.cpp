#include "Header.h"


Simu Simulator;

const int WINDOW_WIDTH = 860;
const int WINDOW_HEIGHT = 640;

const float squareWidth = 100.f;
const float squareHeight = 100.f;

float g = 9.81f; // acceleration of gravity
float m = 0.1f; // mass of the square
int count = 0; // count of jumps

sf::Vector2f Simu::centerMouse(sf::RenderWindow& window, sf::RectangleShape obj) {

	float objWidth = obj.getGlobalBounds().width;
	float objHeight = obj.getGlobalBounds().height;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	float centerMouseX = static_cast<float>(mousePos.x) - objWidth / 2; // get centered mouse position x in figure  
	float centerMouseY = static_cast<float>(mousePos.y) - objHeight / 2; // get centered mouse position y in figure

	sf::Vector2f pos(centerMouseX, centerMouseY);

	return pos;
}
void Simu::draw(sf::RenderWindow& window) {

	this->square.setSize(sf::Vector2f(squareWidth, squareHeight));
	this->square.setFillColor(sf::Color::Yellow);

	this->floor.setSize(sf::Vector2f(860.f, 1.f));
	this->floor.setFillColor(sf::Color::Black);

	this->circle.setRadius(50.f);
	this->circle.setFillColor(sf::Color::Red);

	window.draw(this->circle);
	window.draw(this->floor);
	window.draw(this->square);
}
void Simu::collision(sf::RenderWindow& window, sf::RectangleShape& obj) {

// Window borders collision
// check left collision
	if (obj.getPosition().x < 0.f)
		obj.setPosition(0.f, obj.getPosition().y);
// check top collision
	if (obj.getPosition().y < 0.f)
		obj.setPosition(obj.getPosition().x, 0.f);
// check right collision
	if (obj.getPosition().x + obj.getGlobalBounds().width > WINDOW_WIDTH)
		obj.setPosition(WINDOW_WIDTH - obj.getGlobalBounds().width, obj.getPosition().y);
// check bottom collision
	if (obj.getPosition().y + obj.getGlobalBounds().height > WINDOW_HEIGHT)
		obj.setPosition(obj.getPosition().x, WINDOW_HEIGHT - obj.getGlobalBounds().height);

}

void Simu::gravity(sf::RectangleShape& obj) {
	float resurectionCoef = 0.8f;
	float energyLoss = 0.9f;

	float h = WINDOW_HEIGHT - (obj.getPosition().y + obj.getGlobalBounds().height); // height of object
	float t = sqrt((2 * abs(h)) / g); // time of falling
	float v = (g * t) * 110; // speed of falling
	float F = m * g; // gravity force
	float x = 20;

	int max = 4;

	if (obj.getPosition().y + obj.getGlobalBounds().height >= floor.getPosition().y) {

		F *= -v * energyLoss * resurectionCoef;

		count++;
		if (count >= max) {
			F = 0;
			x = 0;
		}

		sf::Vector2f gF(x, F);
		obj.move(gF);

	}

	else {

		F = m * g;
		sf::Vector2f gF(0, F);
		obj.move(gF);
	}
}
void Simu::mechWork(sf::RectangleShape& obj) {
	
	float a = 1.f; // acceleration
	float F = a * m; // force for work
	float sM = 20.f; // distance in metres
	float S = sM * 4.f; // distance in pixels (1 m = 4 px)

	float W = F * S;
	sf::Vector2f work(W, 0);
	
	sf::FloatRect oBounds = obj.getGlobalBounds();  
	sf::FloatRect cBounds = this->circle.getGlobalBounds();

	if (oBounds.intersects(cBounds)) {

		if (obj.getPosition().x > this->circle.getPosition().x) this->circle.move(-work);
		else this->circle.move(work);
	}
}



int main() {
	// Set window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simualator");
	Simulator.square.setPosition(100.f, 100.f);
	Simulator.floor.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT - 1.f);
	Simulator.circle.setPosition(400.f, 540.f);

	while (window.isOpen()) {
		
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		Simulator.draw(window);
		Simulator.mechWork(Simulator.square);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f convertedMousePos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			
			count = 0;
			if (Simulator.square.getGlobalBounds().contains(convertedMousePos)) {
				Simulator.square.setPosition(Simulator.centerMouse(window, Simulator.square));
			}
		}
		else
			Simulator.gravity(Simulator.square);
		
		window.draw(Simulator.sprite);
		window.display();
	}
}