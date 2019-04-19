#include "Bomb.h"
#include "Ship.h"
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

Bomb::Bomb(string fileName, Vector2f pos,float sp)
{
	if (!bombTexture.loadFromFile(fileName))
	{
		cout << "Unable to load missle texture!" << endl;
		exit(EXIT_FAILURE);
	}
	speed = sp;
	bombSprite.setTexture(bombTexture);
	bombSprite.setPosition(pos);
}


void Bomb::moveBomb()
{
	bombSprite.move(0, speed);
	bombPosition.y += speed;

}
bool Bomb::checkLowerBounds(int WINDOW_HEIGHT)
{
	if (bombSprite.getPosition().y >= WINDOW_HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}

}
void Bomb::draw(RenderWindow& window)
{
	bombSprite.setTexture(bombTexture);
	window.draw(bombSprite);
}
const Vector2f Bomb::getPos()
{
	return bombPosition;
}
const Sprite Bomb::getSprite()
{
	return bombSprite;
}

bool Bomb::Hits(Sprite ship)
{
	bool hits;
	if (bombSprite.getGlobalBounds().intersects(ship.getGlobalBounds()))
	{
		hits = true;
	}
	else
	{
		hits = false;
	}
	return hits;
}