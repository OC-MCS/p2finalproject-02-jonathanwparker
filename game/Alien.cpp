#include "Alien.h"
using namespace std;
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

Alien::Alien(string texture, Vector2f alienP)
{
    if (!alienTexture.loadFromFile(texture))
	{
		cout << "Unable to load missle texture!" << endl;
		exit(EXIT_FAILURE);
	}
	//alienTexture = texture;
	//cout << texture.getSize().x << endl;
	//cout << texture.getSize().y << endl;
	fileName = texture;
	alienPos = alienP;
	alienSprite.setPosition(alienPos);

}
void Alien::moveAlien(Vector2f movement)
{
	alienSprite.move(movement);
	alienPos = alienSprite.getPosition();
}

void Alien::draw(RenderWindow& window)
{
	alienTexture.loadFromFile(fileName);
	alienSprite.setTexture(alienTexture);
	window.draw(alienSprite);
}
const Vector2f Alien::returnPos()
{
	return alienPos;
}

const Sprite Alien::returnSprite()
{
	alienSprite.setTexture(alienTexture);
	return alienSprite;
}
Texture Alien::returnTexture()
{
	return alienTexture;
}

string Alien::returnFileName()
{
	return fileName;
}