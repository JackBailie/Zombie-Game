#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "TextureSystem.h"

const int BACKSTORY_SCROLL_SPEED = 50;

class BackStory
{
private:

	std::string backstoryString;
	sf::Font backstoryFont;
	sf::Text backstoryText;
	sf::Text skipText;
	float scrollPosition;
	std::string newString;
	bool breakonce;
	float backstoryTime;
	sf::Sprite BackGround;
public:
	BackStory(TextureSystem* ts);
	~BackStory();
	void Update(float dt);
	void Render(sf::RenderWindow* window);
};

