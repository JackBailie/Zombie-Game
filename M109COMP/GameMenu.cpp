#include "GameMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


SFML_GameMenu::SFML_GameMenu(std::string filename, int windowWidth, int windowHeight):
	m_GameHasOpened(false),
	mousePressedOnce(false)
{

	std::ifstream inputFile("Assets/MenuInfo/main-menu.txt");

	if (inputFile.is_open())
	{
		std::cout << "good" << std::endl;
		std::string stringLine;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{

			m_backgroundTexture.loadFromFile(stringLine);
			std::cout << stringLine << std::endl;
			m_backgroundSprite.setTexture(m_backgroundTexture);

			sf::Vector2u textureSize = m_backgroundTexture.getSize();
			m_backgroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_backgroundSprite.setPosition(0, 0);
			m_backgroundSprite.setScale(1.2f, 1.2f);

			m_backgroundRect.left = -static_cast<float> (textureSize.x / 2);
			m_backgroundRect.top = -static_cast<float> (textureSize.y / 2);
			m_backgroundRect.width = textureSize.x;
			m_backgroundRect.height = textureSize.y;

		}
		
		
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{

			m_logo.loadFromFile(stringLine);
			m_logoSprite.setTexture(m_logo);
			std::cout << stringLine << std::endl;
			sf::Vector2u textureSize = m_logo.getSize();
			//m_logoSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_logoSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_logoSprite.setPosition(0, m_backgroundTexture.getSize().y / 2);

		}

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_menuFont.loadFromFile(stringLine);
		}
		
		std::string redString;
		std::string greenString;
		std::string blueString;

		int redInt;
		int greenInt;
		int blueInt;

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{

			

			std::istringstream iss(stringLine);
			iss >> redString;
			iss >> greenString;
			iss >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			normalTextColor = sf::Color(redInt, greenInt, blueInt);
		}
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{

			

			std::istringstream iss(stringLine);
			iss >> redString;
			iss >> greenString;
			iss >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			normalOutlineColor = sf::Color(redInt, greenInt, blueInt);
		}
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{



			std::istringstream iss(stringLine);
			iss >> redString;
			iss >> greenString;
			iss >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			highlightedTextColor = sf::Color(redInt, greenInt, blueInt);
		}
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{



			std::istringstream iss(stringLine);
			iss >> redString;
			iss >> greenString;
			iss >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			highlightedOutlineColor = sf::Color(redInt, greenInt, blueInt);
		}
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{		
		}

		sf::Text tempText;
		int textDepth = 50;
		while (!inputFile.eof())
		{
			std::getline(inputFile, stringLine);
			tempText.setFont(m_menuFont);
			tempText.setCharacterSize(50);
			tempText.setString(stringLine);
			tempText.setPosition(20, textDepth);
			tempText.setFillColor(normalTextColor);
			tempText.setOutlineColor(normalOutlineColor);
			tempText.setOutlineThickness(1);
			textDepth += 50;
			m_menuText.push_back(tempText);

		}
		std::cout << "txtdpth " + std::to_string(textDepth) << std::endl;
		m_menuText.at(0).setPosition(20,100);

		for (unsigned int i = 0; i < RAIN_COUNT; i++)
		{

			rain[i] = sf::CircleShape(7);
			rain[i].setPosition(std::rand() % 1920, std::rand() % 1080);
			rain[i].setFillColor(sf::Color(0, 230, 255, 100));

		}
	}
	else
	{
		std::cout << "input file is not good" << std::endl;
	}

}


SFML_GameMenu::~SFML_GameMenu()
{
}

void SFML_GameMenu::Update(float dt, sf::RenderWindow* window, int* state)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	for (int i = 0; i < m_menuText.size(); i++)
	{

		if (mousePos.x > m_menuText.at(i).getPosition().x && mousePos.y > m_menuText.at(i).getPosition().y &&
			mousePos.x < m_menuText.at(i).getPosition().x + m_menuText.at(i).getLocalBounds().width && mousePos.y < m_menuText.at(i).getPosition().y + m_menuText.at(i).getLocalBounds().height)
		{
			m_menuText.at(i).setFillColor(highlightedTextColor);
			m_menuText.at(i).setOutlineColor(highlightedOutlineColor);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				switch (i)
				{
				case 0:
					
					PlayGameClicked(state);
					break;
				case 1:					
					break;
				case 2:
					*state = s_Credits;
					break;
				case 3:
					*state = s_Exit;
					break;
				default:
					break;
				}

			}

		}
		else
		{
			m_menuText.at(i).setFillColor(normalTextColor);
			m_menuText.at(i).setOutlineColor(normalOutlineColor);
		}
		
	}
	for (unsigned int i = 0; i < RAIN_COUNT; i++)
	{
		sf::Vector2f rainpos = rain[i].getPosition();
		rain[i].setPosition(rainpos.x + 150 *dt, rainpos.y + 2000 * dt);
		if (rainpos.y > 1080)
		{
			rain[i].setPosition(std::rand() % 1920, 0);
		}
	}
	if (*state == s_BackStory)
	{
		m_GameHasOpened = true;
	}

}

void SFML_GameMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	//states.transform *= getTransform();
	target.draw(m_backgroundSprite);
	target.draw(m_logoSprite);

	if (m_GameHasOpened)
	{
		target.draw(m_menuText.at(1));
	}
	else
	{
		target.draw(m_menuText.at(0));
	}

	for (int i = 2; i < m_menuText.size(); i++)
	{

		target.draw(m_menuText.at(i));

	}
	for (unsigned int i = 0; i < RAIN_COUNT; i++)
	{
		//target.draw(rain[i]);
	}

}

void SFML_GameMenu::PlayGameClicked(int *state)
{

	if (m_GameHasOpened == false)
	{
		*state = s_BackStory;
	}
	else
	{
		*state = s_GameMode;
	}

}