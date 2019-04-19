#include "Missile.h"
#include "Ship.h"
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

Missile::Missile(string fileName,Vector2f pos)
{
	if (!missileTexture.loadFromFile(fileName))
	{
		cout << "Unable to load missle texture!" << endl;
		exit(EXIT_FAILURE);
	}
	missileSprite.setTexture(missileTexture);
	missileSprite.setPosition(pos);
}


void Missile::moveMissile()
{
	const float DISTANCE = 5.0;
	missileSprite.move(0, -DISTANCE);
	missilePos.y += -DISTANCE;
	
}
bool Missile::checkUpperBounds(int UpperBounds)
{
	if (missileSprite.getPosition().y <= (UpperBounds + UpperBounds/2))
	{
		return true;
	}
	else
	{
		return false;
	}

}
void Missile::draw(RenderWindow& window)
{
	missileSprite.setTexture(missileTexture);
	window.draw(missileSprite);
}
const Vector2f Missile::getPos()
{
	return missilePos;
}
const Sprite Missile::getSprite()
{
	return missileSprite;
}

bool Missile::Hits(Sprite alien)
{
	bool hits;
	if (missileSprite.getGlobalBounds().intersects(alien.getGlobalBounds()))
	{
		hits = true;
	}
	else
	{
		hits = false;
	}
	return hits;
}

