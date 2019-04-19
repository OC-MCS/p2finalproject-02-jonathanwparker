#pragma once
#include "Alien.h"
#include "Bomb.h"
#include <list>
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bombs
{
private:
	list<Bomb> bombs;
	string fileLoc;
	int numOfBombs;
public:
	Bombs(string);
	void drop(Vector2f,float);
	bool checkBombContact(Sprite);
	void checkLowerBounds(int);
	void moveBombs();
	void drawBombs(RenderWindow&);
	void clear();
	const int returnNumBombs();
};