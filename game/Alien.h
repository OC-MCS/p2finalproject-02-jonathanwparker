#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Alien
{
private:
	Sprite alienSprite;
	Texture alienTexture;
	Vector2f alienPos;
	string fileName;
public:
	Alien(string, Vector2f);
	void moveAlien(Vector2f);
	void draw(RenderWindow&);
	const Vector2f returnPos();
	const Sprite returnSprite();
	Texture returnTexture();
	string returnFileName();
};