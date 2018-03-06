#pragma once
#ifndef _GAME_H_
#define _GAME_G_
#include <SFML\Graphics.hpp>
#include "TextureSystem.h"
#include "Player.h"
#include "Background.h"
#include "States.h"
#include "TitleScreen.h"
#include "Zombie.h"

class Game
{
private:
	sf::Font fpsFont;
	sf::Text fpsText;
	Zombie* testZombie;
	
public:
	Game();
	~Game();
	
	int GameState;

	TitleScreen* titleScreen;

	void GameLoop();
	void Update(float dt);
	void Render();
	Player* player;
	sf::RenderWindow* gameWindow;
	TextureSystem* textureSystem;
	BackGround* backGround;
	sf::Clock clock;
	sf::View* view;

};

#endif
