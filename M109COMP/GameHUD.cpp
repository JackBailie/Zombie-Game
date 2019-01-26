#include "GameHUD.h"
#include <iostream>
#include <algorithm>



GameHUD::GameHUD()
{
	healthBar.setPosition(sf::Vector2f(1920 - HEALTHBAR_SIZE, 0));
	healthBar.setSize(sf::Vector2f(HEALTHBAR_SIZE, 30));
	healthBar.setFillColor(sf::Color(0, 255, 0));
	ammoBar.setPosition(1920 - 150, 1080 - 110);
	ammoBar.setSize(sf::Vector2f(140, 100));
	ammoBar.setFillColor(sf::Color(40, 40, 40));
	font.loadFromFile("Assets/Fonts/SegoeMarker.ttf");
	weaponText.setFont(font);
	weaponText.setString("AKM");
	weaponText.setPosition(1920 - 140, 1080 - 100);
	ammoText.setFont(font);
	ammoText.setString(sf::String("ammo"));
	ammoText.setPosition(1920 - 140, 1080 - 50);
	zombieCount.setFont(font);
	zombieCount.setString("Zombies Left: 0");
	zombieCount.setPosition(10, 100);
}


GameHUD::~GameHUD()
{
}

void GameHUD::Update(float dt, Player* player, std::vector<Zombie> zombies)
{
	int zombieCountnum = 0;
	float tempHealth = player->GetHealth();
	float redColor = am::Clamp(255 - 255 * tempHealth * 2 + 255, (float)0, (float)255);
	float greenColor = am::Clamp(255 * tempHealth * 2, (float)0, (float)255);

	if (player->GetWeapon()->getMagContents() <= 0)
	{
		ammoText.setFillColor(sf::Color(255, 0, 0));
	}
	else
	{
		ammoText.setFillColor(sf::Color(255, 255, 255));
	}

	weaponText.setString(player->GetWeapon()->GetName());
	ammoText.setString(std::to_string(player->GetWeapon()->getMagContents()) + "/" + std::to_string(player->GetWeapon()->getAmmo()));
	healthBar.setSize(sf::Vector2f(HEALTHBAR_SIZE*tempHealth, 30));
	healthBar.setFillColor(sf::Color(redColor,greenColor,0));
	
	for (unsigned int i = 0; i < zombies.size(); i++)
	{
		if (zombies.at(i).GetAlive())
		{
			zombieCountnum++;
		}
	}
	zombieCount.setString("Zombies Left: " + std::to_string(zombieCountnum));

}

void GameHUD::Render(sf::RenderWindow* window)
{

	window->draw(healthBar);
	window->draw(ammoBar);
	window->draw(weaponText);
	window->draw(ammoText);
	window->draw(zombieCount);

}
