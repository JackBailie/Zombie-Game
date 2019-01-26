#include "BackStory.h"
#include <fstream>
#include <iostream>
#include <math.h>



BackStory::BackStory(TextureSystem* ts):
	scrollPosition(0.0f),
	breakonce(false),
	backstoryTime(0.0f)
{

	std::ifstream inputFile("Assets/MenuInfo/back-story.txt");



	if (inputFile.is_open()) 
	{

		std::string tempLine;
		std::getline(inputFile, tempLine);
		backstoryFont.loadFromFile("Assets/Fonts/SegoeMarker.ttf");
		backstoryText.setString("");
		backstoryText.setCharacterSize(35);
		backstoryText.setFont(backstoryFont);
		
		skipText.setFont(backstoryFont);
		skipText.setCharacterSize(35);
		skipText.setString("Press Space To Skip!");
		skipText.setOrigin(skipText.getLocalBounds().width / 2, 0);
		skipText.setPosition(1920 / 2, 1080 - 150);

		
		backstoryText.setPosition(100, 100);
		std::getline(inputFile, backstoryString);
		while (!inputFile.eof())
		{

			std::getline(inputFile, tempLine);
			backstoryString = backstoryString + "\n" + tempLine;


		}
		

	}
	BackGround.setTexture(ts->textures[tex_MetalSlab]);
	float xscale = 1920/BackGround.getTexture()->getSize().x;
	float yscale = 1080/BackGround.getTexture()->getSize().y;
	BackGround.setScale(1.5f, 1.5f);

}


BackStory::~BackStory()
{
}

void BackStory::Update(float dt)
{

	scrollPosition += dt * BACKSTORY_SCROLL_SPEED;
	scrollPosition = std::min(scrollPosition, float(backstoryString.length()));
	backstoryTime += dt*2;
	char underscore;
	int shoudUnderscore = floor(backstoryTime);

	if (shoudUnderscore % 2 == 1)
	{
		underscore = '|';
	}
	else
	{
		underscore = ' ';
	}

	skipText.setFillColor(sf::Color(255, 255, 255, (sin(backstoryTime)+1)*255/2));

	newString = backstoryString.substr(0, floor(scrollPosition)) + underscore;

	if (backstoryText.getLocalBounds().width + 200 > 1920 && !breakonce)
	{
		breakonce = true;
		for (int i = floor(scrollPosition) - 3; i > 0; i--)
		{
			if (backstoryString.at(i) == ' ')
			{
				
				backstoryString.insert(floor(i), "\n");
				break;
				
			}
		}
	}
	else
	{
		breakonce = false;
	}

	backstoryText.setString(newString);
}

void BackStory::Render(sf::RenderWindow * window)
{
	window->draw(BackGround);
	window->draw(backstoryText);
	window->draw(skipText);
}
