#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
#include "Alien.h"
using namespace sf;

class Missile
{
private:
	Sprite missileSprite;
	Texture missileTexture;
	Vector2f missilePos;
	string fileName;
public:
	Missile(string,Vector2f);
	void moveMissile();
	bool checkUpperBounds(int);
	void draw(RenderWindow&);
	bool Hits(Sprite);
	const Vector2f getPos();
	const Sprite getSprite();
};