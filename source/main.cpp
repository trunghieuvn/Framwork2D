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
#define FPS_LIMIT	3030

#define PLAYER_SPEED	350
#define TEXTURE_PLAYER	"resources/player.png"
#define TEXTURE_ENEMY	"resources/a1.png"

#define ENEMY_COUNT 7

class GameObject
{
private:

public:
	virtual void Init(const char* textureName = "", int x = 0, int y = 0) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow &window) = 0;
};

class GameObjectRender : public GameObject
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	int dir = 0;
public:
	void setDir(int dirr)
	{
		dir = dirr;
	}
	virtual void Init(const char* textureName, int x = 0, int y = 0) override
	{
		texture.loadFromFile(textureName);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		dir = 1;
	};
	void Update(float dt)
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
	void Render(sf::RenderWindow &window)
	{
		window.draw(sprite);
	}
private:

};
class Player : public GameObjectRender
{
public:

};
class Enemy : public GameObjectRender
{
public:
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
		std::cout << "y: " << pos.y << std::endl;

		sprite.setPosition(pos);
	}
};


class GameManager //: GameObject
{
private:
	Player player;
	Enemy enemy[ENEMY_COUNT];

public:
	void Init(const char* textureName = "", int x = 0, int y = 0) 
	{
		player.Init(TEXTURE_PLAYER, 300, 200);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			enemy[i].Init(TEXTURE_ENEMY, i * 100, i * 20);
		}
	}
	void Update(float dt) 
	{
		player.Update(dt);

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			enemy[i].Update(dt);
		}
	}
	void Render(RenderWindow &window) 
	{
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			enemy[i].Render(window);
		}
		player.Render(window);

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
	static GameManager* s_Instance;

	// =================================================
	

};

GameManager* GameManager::s_Instance = nullptr;

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	RenderWindow window(VideoMode(WINDOWS_W, WINDOWS_H), "Spaceship Game!", Style::Default);
	window.setFramerateLimit(FPS_LIMIT);

	// ============================ Init ============================
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

		// ================================ Update ================================ 
		GameManager::getInstance()->Update(dt);
		
		// ================================ Draw ================================ 
		window.clear();
		GameManager::getInstance()->Render(window);

		window.display();
	}

}