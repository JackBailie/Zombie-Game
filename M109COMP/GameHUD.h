#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
#include"Zombie.h"

const int HEALTHBAR_SIZE = 300;

class GameHUD
{
private:
	sf::RectangleShape healthBar;
	sf::RectangleShape ammoBar;
	sf::Font font;
	sf::Text weaponText;
	sf::Text ammoText;
	sf::Text zombieCount;


public:
	GameHUD();
	~GameHUD();
	void Update(float dt, Player* player, std::vector<Zombie> zombies);
	void Render(sf::RenderWindow* window);
};

