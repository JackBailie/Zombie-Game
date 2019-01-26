#ifndef _GAME_H_
#define _GAME_G_
#include <SFML\Graphics.hpp>
#include <random>
#include "TextureSystem.h"
#include "Player.h"
#include "Background.h"
#include "States.h"
#include "TitleScreen.h"
#include "Zombie.h"
#include "GameHUD.h"
#include "GameMenu.h"
#include "CreditScreen.h"
#include "BackStory.h"

const int FPS_LIMIT = 60;

class Game
{
private:
	sf::Font fpsFont;
	sf::Text fpsText;
	std::vector<Zombie> Zombies;
	std::vector<int> Numbers;
	GameHUD HUD;
	SFML_GameMenu gameMenu;
	SFML_CreditScreen creditscreen;
	BackStory* backStory;
	float zoomLevel;
	bool m_Exit;
	
public:
	Game();
	~Game();
	
	int GameState;

	TitleScreen* titleScreen;

	void GameLoop();
	void Update(float dt);
	void Render();
	void RenderHUD();
	void Zoom(float dt);
	Player* player;
	sf::RenderWindow* gameWindow;
	TextureSystem* textureSystem;
	BackGround* backGround;
	sf::Clock clock;
	sf::View* view;
	sf::View hudView;

};

#endif
