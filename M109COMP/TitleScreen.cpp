#include "TitleScreen.h"
#include <random>
#include <iostream>



TitleScreen::TitleScreen(TextureSystem* ts)
	:flashed(true),
	flashTime(0.0f)
{
	sprite.setTexture(ts->textures[tex_TitleScreen]);
	sf::Vector2u textSize = ts->textures[tex_TitleScreen].getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textSize.x, textSize.y));
	sprite.setPosition(0, 0);

	conitinueSprite.setTexture(ts->textures[tex_Continue]);
	textSize = ts->textures[tex_TitleScreen].getSize();
	conitinueSprite.setTextureRect(sf::IntRect(0, 0, textSize.x, textSize.y));
	conitinueSprite.setOrigin(textSize.x / 2, textSize.y / 2);
	conitinueSprite.setPosition(1920 * 0.5f, 1080 * 0.75f);
}


TitleScreen::~TitleScreen()
{
}

void TitleScreen::Update(float dt)
{
	flashTime += dt;
	//std::cout << (int)flashTime << std::endl;
	if (flashTime > 0.5f)
	{
		
		flashTime = 0;
		conitinueSprite.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	}

}

void TitleScreen::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
	window->draw(conitinueSprite);
}
