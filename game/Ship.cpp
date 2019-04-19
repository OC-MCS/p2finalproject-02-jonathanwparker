#include "Ship.h"
#include "Bombs.h"
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

Ship::Ship(string textureLoc,RenderWindow& DrawingArea)
{
	if (!shipTexture.loadFromFile(textureLoc))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	shipSprite.setTexture(shipTexture);

	shipPos.x = DrawingArea.getSize().x / 2.0f;
	shipPos.y = DrawingArea.getSize().y / 2.0f + 300;
	shipSprite.setPosition(shipPos);
}
void Ship::moveShip(RenderWindow& window)
{
	const float DISTANCE = 5.0;
	Vector2f shipCur = shipSprite.getPosition();
	Vector2u shipSize = shipTexture.getSize();
	float WINDOW_WIDTH = window.getSize().x;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		// left arrow is pressed: move our ship left 5 pixels
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		shipSprite.move(-DISTANCE, 0);
		shipPos = shipSprite.getPosition();
		if (shipPos.x < 0)
		{
			shipSprite.setPosition(shipCur);
			shipPos = shipSprite.getPosition();
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		// right arrow is pressed: move our ship right 5 pixels
		shipSprite.move(DISTANCE, 0);
		shipPos = shipSprite.getPosition();

		if (shipPos.x > WINDOW_WIDTH - shipSize.x*scale)
		{
			shipSprite.setPosition(shipCur);
			shipPos = shipSprite.getPosition();
		}
	}
}
void Ship::draw(RenderWindow& window)
{
	window.draw(shipSprite);
}

const Vector2f Ship::returnPos()
{
	return shipPos;
}
const Sprite Ship::returnSprite()
{
	return shipSprite;
}

bool Ship::checkShipDamage(Bombs& bombs,ScoreLevelLife& sll)
{
	bool isHit = false;
	if (bombs.checkBombContact(shipSprite))
	{
		sll.updateLives();
		isHit = true;
	}
	return isHit;
}

void Ship::changeScale(int s)
{
	shipSprite.setScale(s, s);
	scale = s;
}