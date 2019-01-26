#include "CreditScreen.h"
#include <iostream>
#include <fstream>
#include <algorithm> 

SFML_CreditScreen::SFML_CreditScreen(int windowWidth, int windowHeight)
	:textSpacing(30)
	, textPosition(sf::Vector2f(50,1000))
	, textOpacity(0)
{
	logoTexture.loadFromFile("ZombieLogo.png");
	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(textPosition.x, textPosition.y);


	sfml_Font.loadFromFile("Assets/Fonts/SegoeMarker.ttf");

	std::ifstream inputFile("Assets/MenuInfo/credits-text.txt");

	if (inputFile.is_open())
	{
		sf::Text tempText;
		std::string stringLine;
		

		while (!inputFile.eof())
		{
			std::getline(inputFile, stringLine);
			tempText.setString(stringLine);
			sfml_CreditsText.push_back(tempText);

		}

		inputFile.close();

	}

	logotext.setString("Studio-Z");
	logotext.setFont(sfml_Font);
	logotext.setPosition(300, 540);
	logotext.setFillColor(sf::Color(255, 0, 0, textOpacity));
	
	for (unsigned int i = 0; i < sfml_CreditsText.size(); i++)
	{

		sfml_CreditsText[i].setFont(sfml_Font);
		sfml_CreditsText[i].setPosition(100, 100+i*textSpacing);

	}

}


SFML_CreditScreen::~SFML_CreditScreen()
{
}

void SFML_CreditScreen::Update(float dt)
{
	textPosition.y -= dt*100;
	for (unsigned int i = 0; i < sfml_CreditsText.size(); i++)
	{

		sfml_CreditsText[i].setPosition(textPosition.x, textPosition.y + i*textSpacing);
		std::cout << textPosition.y << std::endl;

	}
	logoSprite.setPosition(textPosition.x, std::max(textPosition.y + sfml_CreditsText.size()*textSpacing+20, 400.0f));
	if (textPosition.y + sfml_CreditsText.size()*textSpacing < 350 && textOpacity <= 255)
	{
		textOpacity += dt * 100;
		textOpacity = std::min(textOpacity, 255.0f);
	}
	logotext.setFillColor(sf::Color(255, 0, 0, textOpacity));

}
void SFML_CreditScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (unsigned int i = 0; i < sfml_CreditsText.size(); i++)
	{

		target.draw(sfml_CreditsText[i]);

	}
	target.draw(logoSprite);
	target.draw(logotext);

}

void SFML_CreditScreen::Reset()
{

	textPosition.y = 1000;
	textOpacity = 0;

}
