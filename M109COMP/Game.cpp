#include "Game.h"
#include <iostream>

Game::Game()
	:GameState(s_TitleScreen)
	
{
	gameWindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "Window");
	textureSystem = new TextureSystem();
	titleScreen = new TitleScreen(textureSystem);
	player = new Player(textureSystem);
	view = new sf::View(sf::FloatRect(0, 0, 1920, 1080));
	gameWindow->setView(*view);
	backGround = new BackGround(textureSystem);
	testZombie = new Zombie(textureSystem, player);


	fpsFont.loadFromFile("Assets/Fonts/SegoeMarker.ttf");
	fpsText.setFont(fpsFont);
	fpsText.setString("FPS: " + 0);
}

Game::~Game()
{
	delete gameWindow;
	delete textureSystem;
	delete view;
}

void Game::GameLoop()
{

	sf::Event event;

	while (gameWindow->isOpen())
	{
		float deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		while (gameWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{

				gameWindow->close();

			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (GameState == s_TitleScreen)
				{
					GameState = s_GameMode;
				}

			}

			
			
		}

		Update(deltaTime);
		Render();

	}

}

void Game::Update(float dt)
{

	int fps = 1.0f/dt;
	fpsText.setString("fps: " + std::to_string(fps));

	switch (GameState)
	{
	case s_TitleScreen:
		titleScreen->Update(dt);
		break;
	case s_MainMenu:
		break;
	case s_GameMode:
		player->Update(dt, gameWindow, view);
		testZombie->Update(dt);
		break;
	case s_PauseMenu:
		break;
	}
	

}

void Game::Render()
{
	gameWindow->clear();

	switch (GameState)
	{
	case s_TitleScreen:
		titleScreen->Render(gameWindow);
		break;
	case s_MainMenu:
		break;
	case s_GameMode:
		backGround->Render(gameWindow);
		player->Render(gameWindow);
		gameWindow->draw(textureSystem->sprite);
		testZombie->Render(gameWindow);
		break;
	case s_PauseMenu:
		break;
	}
	gameWindow->draw(fpsText);
	
	
	gameWindow->display();

}