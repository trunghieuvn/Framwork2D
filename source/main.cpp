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
#define TEXTURE_PLAYER	"resources/player.png"

class GameObject
{
public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(RenderWindow &window) = 0;
	sf::Texture texture;
	sf::Sprite sprite;

protected:
	void loadTexture(const char* textureName)
	{
		texture.loadFromFile(textureName);
		sprite = Sprite(texture);
	}
};

class Player : GameObject
{
public:
	void Init() override 
	{
		loadTexture(TEXTURE_PLAYER);
	}
	void Update(float dt) override
	{
		auto pos = sprite.getPosition();
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

		sprite.setPosition(pos);
	}
	void Render(RenderWindow& window) override
	{
		window.draw(sprite);
	}
private:
	int dir = 1;

};

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	RenderWindow window(VideoMode(WINDOWS_W, WINDOWS_H), "Game!", Style::Default);
	window.setFramerateLimit(FPS_LIMIT);

	// ================================ Init ================================
	Player player;
	player.Init();

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

		// ================================ Update  ================================ 
		player.Update(dt);
		
		// ================================ Draw ================================ 
		window.clear();
		player.Render(window);
		
		window.display();
	}

}