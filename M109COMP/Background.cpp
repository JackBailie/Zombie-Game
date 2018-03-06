#include "Background.h"



BackGround::BackGround(TextureSystem* ts)
{
	sprite.setTexture(ts->textures[tex_Dirt]);
	sprite.setTextureRect(sf::IntRect(0, 0, 10000, 10000));
	sprite.setPosition(-5000, -5000);
}

BackGround::~BackGround()
{
}

void BackGround::Render(sf::RenderWindow * window)
{
	window->draw(sprite);
}
