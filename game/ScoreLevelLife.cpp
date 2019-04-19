#include "ScoreLevelLife.h"
using namespace std;
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;

ScoreLevelLife::ScoreLevelLife(int s, int lev, int lif,Sprite ship,int WINDOW_WIDTH)
{
	score = s;
	level = lev+1;
	lives = lif;
	shipTexture = ship;
	shipTexture.setScale(1.5, 1.5);
	shipTexture.setPosition(WINDOW_WIDTH - 175, 80);
	lifePos.x = shipTexture.getPosition().x;
	lifePos.y = shipTexture.getPosition().y;
	startButton.setPosition(275, 70);
	startButton.setSize(Vector2f(200,50));
	startButton.setOutlineThickness(2);
	startButton.setOutlineColor(Color::Blue);
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
	{
		cout << "Couldn't load font.";
	}
	else
	{
		scoreDisplay.setFont(font);
		scoreDisplay.setPosition(10, 2*25);
		scoreDisplay.setCharacterSize(25);

		levelDisplay.setCharacterSize(25);
		levelDisplay.setFont(font);
		levelDisplay.setPosition(WINDOW_WIDTH / 2 - 50, 2 * 10);

		livesHeading.setCharacterSize(25);
		livesHeading.setFont(font);
		livesHeading.setPosition(WINDOW_WIDTH - 150, 2 * 10);
		livesHeading.setString("Lives:");


		scoreHeading.setFont(font);
		scoreHeading.setCharacterSize(25);
		scoreHeading.setPosition(20, 2*10);
		scoreHeading.setString("Score:");
		
		levelBeat.setFont(font);
		levelBeat.setCharacterSize(30);
		levelBeat.setPosition(250, 70);

		ProceedingLevel.setFont(font);
		ProceedingLevel.setCharacterSize(30);
		ProceedingLevel.setPosition(250, 70);

		beatGame.setFont(font);
		beatGame.setCharacterSize(30);
		beatGame.setPosition(250, 70);

		GameOver.setFont(font);
		GameOver.setCharacterSize(30);
		GameOver.setPosition(250, 70);

		startButtonText.setFont(font);
		startButtonText.setCharacterSize(30);
		startButtonText.setPosition(295, 75);
		startButtonText.setString("Start Game");
		startButtonText.setFillColor(Color::Black);
	}
}

void ScoreLevelLife::updateLevel(int lev)
{
	level = lev+1;
}

void ScoreLevelLife::updateScore()
{
	score += 30;
}

void ScoreLevelLife::updateLives()
{
	lives--;
}

void ScoreLevelLife::draw(RenderWindow& window,bool levelFinished,bool startingNext,bool gameFinish,bool gameOver,bool start)
{
	string s = to_string(score);
	string lev ="Level: " + to_string(level);
	string levWOCol = "Level " + to_string(level);
	string nextLevWOCol = "Level " + to_string(level + 1);
	for (int i = 0; i < 10 - (s.length()); i++)
	{
		s.insert(0, "0");
	}
	for (int i = 0; i < lives; i++)
	{
		shipTexture.setPosition(lifePos.x + i *(2* shipTexture.getTexture()->getSize().x), lifePos.y);
		window.draw(shipTexture);
	}
	if (!start)
	{
		window.draw(startButton);
		window.draw(startButtonText);
	}
	else if (gameOver)
	{
		GameOver.setString("You've lost the Game.");
		window.draw(GameOver);
	}
	else if (gameFinish)
	{
		beatGame.setString("You've won the game!");
		window.draw(beatGame);
	}
	else if (startingNext)
	{
		ProceedingLevel.setString("Proceeding to " + nextLevWOCol);
		window.draw(ProceedingLevel);
	}
	else if (levelFinished)
	{
		levelBeat.setString("You've beat " + levWOCol);
		window.draw(levelBeat);
	}
	levelDisplay.setString(lev);
	scoreDisplay.setString(s);
	window.draw(scoreDisplay);
	window.draw(scoreHeading);
	window.draw(livesHeading);
	window.draw(levelDisplay);

}

const int ScoreLevelLife::returnLives()
{
	return lives;
}

bool ScoreLevelLife::checkMouseBounds(Vector2f mouse)
{
	return startButton.getGlobalBounds().contains(mouse);
}
void ScoreLevelLife::resetLives()
{
	lives = 3;
}

void ScoreLevelLife::resetScore()
{
	score = 0;
}