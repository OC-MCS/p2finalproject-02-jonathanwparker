#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class ScoreLevelLife
{
private:
	Vector2f lifePos;
	int score;
	int lives;
	int level;
	Text scoreDisplay;
	Text levelDisplay;
	Text scoreHeading;
	Text livesHeading;
	Font font;
	Sprite shipTexture;
	Text levelBeat;
	Text ProceedingLevel;
	Text beatGame;
	Text GameOver;
	RectangleShape startButton;
	Text startButtonText;
public:
	ScoreLevelLife(int, int, int,Sprite,int);
	void updateScore();
	void resetScore();
	void updateLives();
	void resetLives();
	void updateLevel(int);
	void draw(RenderWindow&,bool,bool,bool,bool,bool);
	const int returnLives();
	bool checkMouseBounds(Vector2f);

};