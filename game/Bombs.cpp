#include "Bombs.h"
#include "Bomb.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
Bombs::Bombs(string file)
{
	fileLoc = file;
}
void Bombs::drop(Vector2f playerLoc,float dropSpeed)
{
	bombs.push_back(Bomb(fileLoc, playerLoc,dropSpeed));
	numOfBombs++;
}
bool Bombs::checkBombContact(Sprite target)
{
	bool ShipHit = false;
	list<Bomb>::iterator c;
	c = bombs.begin();
	if (numOfBombs != 0)
	{
		while (c != bombs.end() && !ShipHit)
		{
			if (c->Hits(target))
			{
				c = bombs.erase(c);
				numOfBombs--;
				ShipHit = true;
			}
			else
			{
				c++;
			}

		}
	}
	return ShipHit;
}

void Bombs::checkLowerBounds(int UpperBounds)
{
	list<Bomb>::iterator c;
	for (c = bombs.begin(); c != bombs.end();)
	{
		if (c->checkLowerBounds(UpperBounds))
		{
			numOfBombs--;
			c = bombs.erase(c);
		}
		else
			c++;
	}
}

void Bombs::drawBombs(RenderWindow& window)
{
	list<Bomb>::iterator c;
	for (c = bombs.begin(); c != bombs.end();)
	{
		c->draw(window);
		c++;
	}
}

void Bombs::moveBombs()
{
	list<Bomb>::iterator c;
	for (c = bombs.begin(); c != bombs.end();)
	{
		c->moveBomb();
		c++;
	}
}

const int Bombs::returnNumBombs()
{
	return numOfBombs;
}

void Bombs::clear()
{
	bombs.clear();
}