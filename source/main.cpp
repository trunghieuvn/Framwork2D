#include <math.h>
#include <cstdlib>
#include <vector>
#include <ctime> 
#include <iostream>

#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

#define WINDOWS_W	900
#define WINDOWS_H	600
#define FPS_LIMIT	60

#define PLAYER_SPEED	370

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	RenderWindow window(VideoMode(WINDOWS_W, WINDOWS_H), "Game!", Style::Default);
	window.setFramerateLimit(FPS_LIMIT);

	// ---------------------- Draw Color ----------------------
	sf::CircleShape circleShape(50);
	circleShape.setFillColor(sf::Color::Blue);
	// ----------------------Draw Image  ----------------------
	sf::Texture texture;
	texture.loadFromFile("resources/player.png");

	sf::Sprite player(texture);
	int dir = 1;

	Clock clock;
	Time elapsed;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		elapsed = clock.getElapsedTime();
		// A microsecond is 1/1,000,000th of a second, 1000 microseconds == 1 millisecond
		float dt = clock.getElapsedTime().asMicroseconds() * 1.0f / 1000000;
		//std::cout << "dt: " << dt << std::endl;
		// Start the countdown over.  Think of laps on a stop watch.
		clock.restart();

		// ================================ Update ================================ 
		auto pos = player.getPosition();
		if (pos.x > WINDOWS_W - texture.getSize().x)
		{
			dir = -1;
		}
		if (pos.x < 0)
		{
			dir = 1;
		}

		pos.x += PLAYER_SPEED * dt * dir;
		std::cout << "x: " << pos.x << std::endl;

		player.setPosition(pos);
		
		// ================================ Draw ================================ 
		window.clear();
		window.draw(circleShape);
		window.draw(player);
		
		window.display();
	}

}