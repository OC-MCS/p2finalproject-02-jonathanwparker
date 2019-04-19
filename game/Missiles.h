#pragma once
#include "Missile.h"
#include "Ship.h"
#include "Alien.h"
#include <list>
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Missiles
{
private:
	list<Missile> missiles;
	string fileLoc;
	int numOfMissiles;
public:
	Missiles(string);
	void fire(Vector2f);
	bool checkMissileContact(Sprite);
	void checkUpperBounds(int);
	void moveMissiles();
	void drawMissiles(RenderWindow&);
	void clear();
	const int returnNumMissiles();
};