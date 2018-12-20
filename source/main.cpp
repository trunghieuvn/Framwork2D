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
#define TEXTURE_ENEMY	"resources/a1.png"

class Object
{
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(RenderWindow &window) = 0;
};

class GameObject : Object
{
public:
	sf::Texture texture;
	sf::Sprite sprite;

protected:
	void loadTexture(const char* textureName)
	{
		texture.loadFromFile(textureName);
		sprite = Sprite(texture);
	}

	int dir = 1;
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

};

class Enemy : GameObject
{
public:
	void Init() override
	{
		loadTexture(TEXTURE_ENEMY);
	}

	void Init(int x, int y)
	{
		Init();
		sprite.setPosition(x, y);
	}
	void Update(float dt) override
	{
		auto pos = sprite.getPosition();
		if (pos.y > WINDOWS_H - texture.getSize().y)
		{
			dir = -1;
		}
		if (pos.y < 0)
		{
			dir = 1;
		}
		pos.y += PLAYER_SPEED * dt * dir;
		std::cout << "x: " << pos.y << std::endl;

		sprite.setPosition(pos);
	}
	void Render(RenderWindow& window) override
	{
		window.draw(sprite);
	}

private:

};

class GameManager : Object
{
public:
	void Init() override
	{
		player.Init();
		enemy.Init(300, 200);
		// TODO Enemy Manager
	}
	void Update(float dt) override
	{
		player.Update(dt);
		enemy.Update(dt);
	}
	void Render(RenderWindow &window) override
	{
		player.Render(window);
		enemy.Render(window);
	}

	static GameManager* getInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new GameManager();
		}
		return s_Instance;
	}
private:
	// =================================================
	GameManager() {};
	static GameManager* s_Instance;

	// =================================================
	Player player;
	Enemy enemy;

};
GameManager* GameManager::s_Instance = nullptr;



int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	RenderWindow window(VideoMode(WINDOWS_W, WINDOWS_H), "Game!", Style::Default);
	window.setFramerateLimit(FPS_LIMIT);

	// ================================ Init ================================
	GameManager::getInstance()->Init();

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
		
		GameManager::getInstance()->Update(dt);
		// ================================ Draw ================================ 
		window.clear();
		GameManager::getInstance()->Render(window);
		window.display();
	}

}