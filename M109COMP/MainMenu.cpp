#include "MainMenu.h"



MainMenu::MainMenu(TextureSystem* ts):
	Option(0)
{
	backGroundSprite.setTexture(ts->textures[tex_GameLogo]);
	sf::Vector2u textureSize = ts->textures[tex_GameLogo].getSize();
	backGroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
}


MainMenu::~MainMenu()
{
}

void MainMenu::Update(float dt)
{



}
