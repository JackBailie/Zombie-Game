#include "Background.h"



BackGround::BackGround(TextureSystem* ts)
{
	backsprite.setTexture(ts->textures[tex_Dirt]);
	backsprite.setTextureRect(sf::IntRect(0, 0, 18000, 16000));
	backsprite.setPosition(-10000, -10000);
	backsprite.setScale(1.1f, 1.1f);
	
	sprite.setTexture(ts->textures[tex_Dirt]);
	sprite.setTextureRect(sf::IntRect(0, 0, 8000, 6000));
	sprite.setPosition(0, 0);

	leftsprite.setTexture(ts->textures[tex_Dirt]);
	leftsprite.setPosition(-125, 0);
	leftsprite.setTextureRect(sf::IntRect(0, 0, 500, 6000));
	leftsprite.setScale(0.25f, 1);
	leftsprite.setColor(sf::Color(200, 200, 200));

	rightsprite.setTexture(ts->textures[tex_Dirt]);
	rightsprite.setPosition(8125, 0);
	rightsprite.setTextureRect(sf::IntRect(0, 0, 500, 6000));
	rightsprite.setScale(0.25f, 1);
	rightsprite.setColor(sf::Color(200, 200, 200));

	topsprite.setTexture(ts->textures[tex_Dirt]);
	topsprite.setPosition(0, -125);
	topsprite.setTextureRect(sf::IntRect(0, 0, 8000, 500));
	topsprite.setScale(1, 0.25f);
	topsprite.setColor(sf::Color(200, 200, 200));
	
	bottomsprite.setTexture(ts->textures[tex_Dirt]);
	bottomsprite.setPosition(0, 6125);
	bottomsprite.setTextureRect(sf::IntRect(0, 0, 8000, 500));
	bottomsprite.setScale(1, 0.25f);
	bottomsprite.setColor(sf::Color(200, 200, 200));
}

BackGround::~BackGround()
{
}

void BackGround::Render(sf::RenderWindow * window)
{
	window->draw(backsprite);
	window->draw(sprite);
	window->draw(leftsprite);
	window->draw(rightsprite);
	window->draw(topsprite);
	window->draw(bottomsprite);
	
}
