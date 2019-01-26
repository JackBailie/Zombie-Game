#include "Game.h"
#include <iostream>

Game::Game()
	:GameState(s_TitleScreen),
	gameMenu("Assets/MenuInfo/main-menu.txt", 1920, 1080),
	creditscreen(1920, 1080),
	zoomLevel(1.0f),
	m_Exit(false)
{
	gameWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "M109COMP", sf::Style::Fullscreen);
	
	sf::Text tempLoad;
	fpsFont.loadFromFile("Assets/Fonts/SegoeMarker.ttf");
	tempLoad.setFont(fpsFont);
	tempLoad.setString("Loading...");
	tempLoad.setPosition(1280 / 2, 720 / 2);
	tempLoad.setOrigin(tempLoad.getLocalBounds().width/2, tempLoad.getLocalBounds().height / 2);
	gameWindow->draw(tempLoad);
	gameWindow->display();
	
	textureSystem = new TextureSystem();
	titleScreen = new TitleScreen(textureSystem);
	player = new Player(textureSystem);
	view = new sf::View(sf::FloatRect(0, 0, 1920, 1080));
	hudView = sf::View(sf::FloatRect(0, 0, 1920, 1080));
	gameWindow->setView(*view);
	backGround = new BackGround(textureSystem);
	backStory = new BackStory(textureSystem);
	for (unsigned int i = 0; i < 100; i++)
	{

		Zombies.push_back(Zombie(textureSystem, player, sf::Vector2i(std::rand() % 8000, std::rand() % 6000)));

	}


	
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
		
		while (gameWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || m_Exit)
			{

				gameWindow->close();

			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (GameState == s_TitleScreen)
				{
					GameState = s_MainMenu;
				}

			}

			
			
		}
		if (deltaTime > 1.0f / FPS_LIMIT)
		{
			clock.restart();
			Update(deltaTime);
			
		}
		Render();

	}

}

void Game::Update(float dt)
{

	int fps = int(1.0f/dt);
	fpsText.setString("fps: " + std::to_string(fps));

	switch (GameState)
	{
	case s_TitleScreen:
		titleScreen->Update(dt);
		break;
	case s_MainMenu:
		gameMenu.Update(dt, gameWindow, &GameState);
		break;
	case s_GameMode:
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{

			view->setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
			GameState = s_MainMenu;
			break;

		}
		
		player->Update(dt, gameWindow, view);
		for (unsigned int i = 0; i < Zombies.size(); i++)
		{
			Zombies.at(i).Update(dt, &Zombies);
		}
		HUD.Update(dt, player, Zombies);
		Zoom(dt);
			

		break;
	case s_BackStory:
		backStory->Update(dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			GameState = s_GameMode;
		}
		break;
	case s_Credits:
		creditscreen.Update(dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{

			GameState = s_MainMenu;
			creditscreen.Reset();

		}
		break;
	case s_PauseMenu:
		break;
	case s_Exit:
		m_Exit = true;
		break;
	}
	

}

void Game::Zoom(float dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
	{
		zoomLevel += dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
	{
		zoomLevel -= dt;
	}
	zoomLevel = std::max(0.5f, zoomLevel);
	view->setSize(sf::Vector2f(1920 * zoomLevel, 1080 * zoomLevel));

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
		gameWindow->draw(gameMenu);
		break;
	case s_GameMode:
		gameWindow->setView(*view);
		backGround->Render(gameWindow);
		for (unsigned int i = 0; i < Zombies.size(); i++)
		{
			Zombies.at(i).RenderBlood(gameWindow);
		}
		player->Render(gameWindow);
		gameWindow->draw(textureSystem->sprite);
		for (unsigned int i = 0; i < Zombies.size(); i++)
		{
			Zombies.at(i).Render(gameWindow);
		}		
		RenderHUD();
		break;
	case s_BackStory:
		titleScreen->Render(gameWindow);
		backStory->Render(gameWindow);
		break;
	case s_Credits:
		gameWindow->draw(creditscreen);
		break;
	case s_PauseMenu:
		break;
	}
	gameWindow->draw(fpsText);
	
	
	gameWindow->display();

}

void Game::RenderHUD()
{
	gameWindow->setView(hudView);
	HUD.Render(gameWindow);
}
