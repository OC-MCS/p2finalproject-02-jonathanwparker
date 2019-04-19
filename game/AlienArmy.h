#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
#include <list>
#include "Missiles.h"
#include "Alien.h"
#include "Bombs.h"
#include "ScoreLevelLife.h"
using namespace sf;

class AlienArmy
{
private:
	list<Alien> aliens;
	float alienSpeed;
	float bombSpeed;
	float bombDropChance;
	int numOfAliens =0;
public:
	AlienArmy();
	void setupAliens(int, RenderWindow&, int, int, string, int);
	void moveAliens(int, bool&);
	void checkLiveAliens(Missiles&,ScoreLevelLife&);
	bool checkYBounds(Sprite);
	void draw(RenderWindow&);
	void checkForBD(Bombs&);
	const int returnNumAliens();
	void clear();
};