#pragma once
#include <SFML\Graphics.hpp>
#include "TextureSystem.h"

class TitleScreen
{
private:
	sf::Sprite sprite;
	sf::Sprite conitinueSprite;
	bool flashed;
	float flashTime;

public:
	TitleScreen(TextureSystem* ts);
	~TitleScreen();
	void Update(float dt);
	void Render(sf::RenderWindow* window);
};

