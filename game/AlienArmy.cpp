#include "AlienArmy.h"
#include "Alien.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>
#include "ScoreLevelLife.h"
using namespace std;
using namespace sf;

int checkForBombDrop(int numOfAliens)
{
	srand(time(NULL));
	if (numOfAliens != 0)
		return  rand() % numOfAliens;
	else
		return 0;
}

AlienArmy::AlienArmy()
{
	
}

void AlienArmy::setupAliens(int UpperBounds, RenderWindow& window, int collums, int rows, string fileName, int level)
{
	string fileLoc = fileName;
	fileLoc += to_string(level);
	fileLoc += ".png";
	cout << fileLoc << endl;
	Vector2f alienPos(window.getSize().x / 2.0, 2 * UpperBounds);
	alienSpeed = 2.500;
	bombSpeed = 3.00;
	bombSpeed += level * 0.35*bombSpeed;
	alienSpeed += level * 0.35*alienSpeed;
	Texture texture;
	if (!texture.loadFromFile(fileLoc))
	{
		cout << "Unable to load missle texture!" << endl;
		exit(EXIT_FAILURE);
	}
	for (int c = 0; c < collums; c++)
	{
		alienPos.y = 2 * UpperBounds;
		for (int r = 0; r < rows; r++)
		{

			aliens.push_back(Alien(fileLoc, alienPos));
			alienPos.y += texture.getSize().y + 10;
			numOfAliens++;

		}
		alienPos.x += texture.getSize().x + 10;
	}
}

void AlienArmy::moveAliens(int WINDOW_WIDTH, bool& isRight)
{
	Vector2f newEnemyLoc;
	Vector2f movement;
	list<Alien>::iterator iterB;
	list<Alien>::iterator iterE;
	list<Alien>::iterator iterAll;
	if (numOfAliens != 0)
	{
		iterB = aliens.begin();
		advance(iterB, numOfAliens - 1);
		iterE = iterB;
		iterB = aliens.begin();
		Sprite firstAlien = (*iterB).returnSprite();
		Sprite lastAlien = (*iterE).returnSprite();
		Texture texture = iterB->returnTexture();
		if (isRight)
		{
			movement.x = alienSpeed;
			movement.y = 0;
			lastAlien.move(movement);
			newEnemyLoc = lastAlien.getPosition();
			if (newEnemyLoc.x > WINDOW_WIDTH - texture.getSize().x)
			{
				movement.x = 0;
				movement.y = texture.getSize().y;
				for (iterAll = aliens.begin(); iterAll != aliens.end(); /* note no ++ here*/)
				{
					(*iterAll).moveAlien(movement);
					iterAll++;
				}
				isRight = false;
			}
			else
			{
				for (iterAll = aliens.begin(); iterAll != aliens.end(); /* note no ++ here*/)
				{
					for (iterAll = aliens.begin(); iterAll != aliens.end(); /* note no ++ here*/)
					{
						(*iterAll).moveAlien(movement);
						iterAll++;
					}
				}
			}
		}
		if (!isRight)
		{
			movement.x = -alienSpeed;
			movement.y = 0;
			firstAlien.move(movement);
			newEnemyLoc = firstAlien.getPosition();
			if (newEnemyLoc.x < 0)
			{
				movement.x = 0;
				movement.y = texture.getSize().y;
				for (iterAll = aliens.begin(); iterAll != aliens.end(); /* note no ++ here*/)
				{
					iterAll->moveAlien(movement);
					iterAll++;
				}
				isRight = true;
			}
			else
			{
				for (iterAll = aliens.begin(); iterAll != aliens.end(); /* note no ++ here*/)
				{
					iterAll->moveAlien(movement);
					iterAll++;
				}
			}
		}
	}
}

void AlienArmy::draw(RenderWindow& window)
{
	list<Alien>::iterator iterAll;
	Sprite Alien;
	for (iterAll = aliens.begin(); iterAll != aliens.end(); /* note no ++ here*/)
	{
		Alien = iterAll->returnSprite();
		window.draw(Alien);
		iterAll++;
	}
}

void AlienArmy::checkLiveAliens(Missiles& missiles,ScoreLevelLife& sll)
{
	list<Alien>::iterator a;
	for (a = aliens.begin(); a != aliens.end();)
	{
		if (missiles.checkMissileContact(a->returnSprite()))
		{
			numOfAliens--;
			a = aliens.erase(a);
			sll.updateScore();
		}
		else
			a++;
	}
	if (numOfAliens == 0)
	{
 		//cout << "There be bugs in these parts..." << endl;
	}
}

void AlienArmy::checkForBD(Bombs& bombs)
{
	list<Alien>::iterator iterAll;
	iterAll = aliens.begin();
	if (numOfAliens != 0)
	{
		advance(iterAll, checkForBombDrop(numOfAliens-1));
		bombs.drop(iterAll->returnPos(),bombSpeed);
	}

}

bool AlienArmy::checkYBounds(Sprite shipPos)
{
	bool gameOver = false;
	list<Alien>::iterator a;
	a = aliens.begin();
	while (a != aliens.end() && !gameOver)
	{
		if (a->returnPos().y >= shipPos.getPosition().y - shipPos.getTexture()->getSize().y)
		{
			gameOver = true;
		}
		else
		{
			a++;
		}

	}
	return gameOver;
}

const int AlienArmy::returnNumAliens()
{
	return numOfAliens;
}

void AlienArmy::clear()
{
	aliens.clear();
	numOfAliens = 0;
}