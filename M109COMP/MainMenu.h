#pragma once
#include <SFML\Graphics.hpp>
#include "TextureSystem.h"



class MainMenu
{
private:
	sf::Sprite backGroundSprite;
	unsigned int Option;
public:
	MainMenu(TextureSystem* ts);
	~MainMenu();
	void Update(float dt);
	void Render();
};

