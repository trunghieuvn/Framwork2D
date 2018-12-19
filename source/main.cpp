#include <math.h>
#include <cstdlib>
#include <vector>
#include <ctime> 
#include <iostream>

#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

#define WINDOWS_W 900
#define WINDOWS_H 600


int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	RenderWindow window(VideoMode(WINDOWS_W, WINDOWS_H), "Spaceship Game!", Style::Default);
	window.setFramerateLimit(200);

	/////////////
	sf::CircleShape circleShape(200);
	circleShape.setFillColor(sf::Color::Blue);

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

		clock.restart();

		//Draw ===================================================================== DRAW
		window.clear();
		//SceneMgr::GetInstance()->Render( window);
		window.draw(circleShape);

		window.display();
	}

}