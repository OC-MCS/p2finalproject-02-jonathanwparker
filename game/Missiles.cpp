#include "Missiles.h"
#include "Missile.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
Missiles::Missiles(string file)
{
	fileLoc = file;
}
void Missiles::fire(Vector2f playerLoc)
{
	missiles.push_back(Missile(fileLoc, playerLoc));
	numOfMissiles++;
}
bool Missiles::checkMissileContact(Sprite target)
{
	bool AlienHit = false;
	list<Missile>::iterator c;
	c = missiles.begin();
	if (numOfMissiles != 0)
	{
		while (c != missiles.end() && !AlienHit)
		{
			if (c->Hits(target))
			{
				c = missiles.erase(c);
				numOfMissiles--;
				AlienHit = true;
			}
			else
			{
				c++;
			}

		}
	}
	return AlienHit;
}

void Missiles::checkUpperBounds(int UpperBounds)
{
	list<Missile>::iterator c;
	for (c = missiles.begin(); c != missiles.end();)
	{
		if (c->checkUpperBounds(UpperBounds))
		{
			numOfMissiles--;
			c = missiles.erase(c);
		}
		else
			c++;
	}
}

void Missiles::drawMissiles(RenderWindow& window)
{
	list<Missile>::iterator c;
	for (c = missiles.begin(); c != missiles.end();)
	{
		c->draw(window);
		c++;
	}
}

void Missiles::moveMissiles()
{
	list<Missile>::iterator c;
	for (c = missiles.begin(); c != missiles.end();)
	{
		c->moveMissile();
  		c++;
	}
}

const int Missiles::returnNumMissiles()
{
	return numOfMissiles;
}
void Missiles::clear()
{
	missiles.clear();
}