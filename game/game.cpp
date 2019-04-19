//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Missile.h"
#include "AlienArmy.h"
#include "ScoreLevelLife.h"
#include <list>
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>
using namespace sf; 

//============================================================
// YOUR HEADER WITH YOUR NAME GOES HERE. PLEASE DO NOT FORGET THIS
//============================================================

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen




int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 700;
	const int UpperBounds = WINDOW_HEIGHT - 600;
	bool isRight = false,isFired = false;
	int countTo,countBomb = 0;
	int secCounter = 0,collumn = 10,row = 5,level = 0,secCounter2 = 0,hitCounter = 0;
	Vector2f DrawingArea;
	DrawingArea.x = WINDOW_WIDTH;
	DrawingArea.y = WINDOW_HEIGHT - UpperBounds;
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	bool SpacebarPressed = false, bombDropped = false, levelStarted = false, levelFinished = false, gameOver = false, gameFinished = false,startingNext = false,isHit = false,start = false;
	// Limit the framerate to 60 frames per second
	
	window.setFramerateLimit(60);
	Ship player("player.png", window);
	Bombs bombs("bombs1.png");
	Missiles missiles("missile1.png");
	AlienArmy aliens;
	ScoreLevelLife upperDisplay(0, level, 3, player.returnSprite(), WINDOW_WIDTH);
	player.changeScale(2);
	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}

	// A sprite is a thing we can draw and manipulate on the screen.
	// We have to give it a "texture" to specify what it looks like

	Sprite background;
	background.setTexture(starsTexture);
	background.setOrigin(Vector2f(0, -UpperBounds));
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale(1.5, 1.5);
	// create sprite and texture it


	// initial position of the ship will be approx middle of screen


	while (window.isOpen())
	{
		if (!levelStarted && start)
		{
			secCounter = 0;
			secCounter2 = 0;
			hitCounter = 0;
			missiles.clear();
			bombs.clear();
			aliens.clear();
			upperDisplay.updateLevel(level);
			aliens.setupAliens(UpperBounds, window, collumn, row, "trueEnemy", level);
			levelStarted = true;
		}
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}
		if (!isHit && start)
		{
			if (Keyboard::isKeyPressed(Keyboard::Space) && !isFired)
			{
				missiles.fire(player.returnPos());
				isFired = true;
				secCounter = 1;
			}
			if (isFired)
			{
				secCounter++;
				if (secCounter == 20)
				{
					isFired = false;
					secCounter = 0;
				}
			}
		}
	
	srand(time(NULL));
	if (!bombDropped && start)
	{
		aliens.checkForBD(bombs);
		countTo = rand() % (80 - 40*level)+(60-40*level);
		bombDropped = true;
	}
	if (bombDropped && start)
	{
		countBomb++;
		if (countBomb == countTo)
		{
			bombDropped = false;
			countBomb = 0;
		}
	}
		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);
		if (!levelFinished && !gameOver && start)
		{
			if (!isHit)
			{
				isHit = player.checkShipDamage(bombs, upperDisplay);
			}
			missiles.checkUpperBounds(UpperBounds);
			aliens.checkLiveAliens(missiles, upperDisplay);

			aliens.moveAliens(WINDOW_WIDTH, isRight);
			missiles.moveMissiles();
			if (!isHit)
			{
				player.moveShip(window);
			}
			bombs.moveBombs();
			aliens.draw(window);
			missiles.drawMissiles(window);
			bombs.drawBombs(window);
			levelFinished = aliens.returnNumAliens() == 0;
		}
		if (levelFinished)
		{
			if (level == 0)
			{
				secCounter++;
				if (secCounter > 300)
				{
					startingNext = true;
					if (secCounter == 600)
					{
						startingNext = false;
						levelFinished = false;
						levelStarted = false;
						level++; secCounter = 0;
					}
				}
			}
			else if (level == 1)
			{
				gameFinished = true;
			}
		}
		upperDisplay.draw(window,levelFinished,startingNext,gameFinished,gameOver,start);
		if (isHit && !gameOver & start)
		{
			hitCounter++;
			if (hitCounter % 5 == 0)
			{
				player.draw(window);
			}
			if (hitCounter == 120)
			{
				isHit = false;
				hitCounter = 0;
			}
		}
		else if(!gameOver & start)
		{
			player.draw(window);
		}
		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();
		window.clear();
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Button::Left) && !start)
			{

				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				start = upperDisplay.checkMouseBounds(mousePos);
				if (start)
				{
					upperDisplay.resetLives();
					upperDisplay.resetScore();
					isHit = false;
					level = 0;
					levelStarted = false;
				}
			}
		}
		gameOver = aliens.checkYBounds(player.returnSprite());
		if (upperDisplay.returnLives() == 0 || gameOver)
		{
			gameOver = true;
			secCounter++;
			if (secCounter == 60)
			{
				gameOver = false;
				start = false;
			}
			
		}
	} // end body of animation loop

	return 0;
}

