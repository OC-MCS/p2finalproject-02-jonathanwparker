#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
#include "Bombs.h"
#include "ScoreLevelLife.h"
using namespace sf;

class Ship
{
private:
	Sprite shipSprite;
	Texture shipTexture;
	Vector2f shipPos;
	float scale = 1;
public:
	Ship(string,RenderWindow&);
	void moveShip(RenderWindow&);
	void draw(RenderWindow&);
	void changeScale(int);
	const Vector2f returnPos();
	const Sprite returnSprite();
	bool checkShipDamage(Bombs&,ScoreLevelLife&);
};