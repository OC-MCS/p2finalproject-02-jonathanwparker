#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb
{
private:
	Sprite bombSprite;
	Texture bombTexture;
	Vector2f bombPosition;
	string fileName;
	float speed;
public:
	Bomb(string, Vector2f,float);
	void moveBomb();
	bool checkLowerBounds(int);
	void draw(RenderWindow&);
	bool Hits(Sprite);
	const Vector2f getPos();
	const Sprite getSprite();
};


