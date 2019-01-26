#include <iostream>
#include "TextureSystem.h"

TextureSystem::TextureSystem()
{
	std::cout << "Loading Textures" << std::endl;
	
	InitialiseTextures();
	
}

//Loads a texture and returns its pointe
sf::Texture TextureSystem::LoadTexture(std::string path)
{
	sf::Texture tempTexture;
	std::string tempPath = "Assets/Textures/" + path;

	if (tempTexture.loadFromFile(tempPath))
	{

		return tempTexture;

	}
	else
	{

		std::cout << "failed to load " << path << std::endl;

	}

	return textures[tex_Hero_Flashlight_Move];
}
//Gets the texture pointer relative to the ID
sf::Texture TextureSystem::AquireTexture(int textureID)
{
	if (textureID < 0 || textureID >= tex_Max)
	{

		std::cout << "No texture with the ID " << textureID << std::endl;
		sf::Texture* NullTexture = new sf::Texture;
		return *NullTexture;

	}
	std::cout << "Returning texture" << std::endl;
	return textures[textureID];
	
}

void TextureSystem::InitialiseTextures()
{

	textures[tex_Blood] = LoadTexture("blood.png");
	textures[tex_Bullet] = LoadTexture("bullet.png");
	textures[tex_BulletSlug] = LoadTexture("bulletslug.png");
	textures[tex_Continue] = LoadTexture("continue.png");
	textures[tex_Dirt] = LoadTexture("dirt.png");
	textures[tex_Dirt].setRepeated(true);
	textures[tex_fog] = LoadTexture("fog.png");
	textures[tex_GameLogo] = LoadTexture("game-logo.png");
	textures[tex_Hero_Flashlight_Idle] = LoadTexture("hero_flashlight_idle.png");
	textures[tex_Hero_Flashlight_Melee] = LoadTexture("hero_flashlight_melee.png");
	textures[tex_Hero_Flashlight_Move] = LoadTexture("hero_flashlight_move.png");
	textures[tex_Hero_Knife_Idle] = LoadTexture("hero_knife_idle.png");
	textures[tex_Hero_Knife_Melee] = LoadTexture("hero_knife_melee.png");
	textures[tex_Hero_Knife_Move] = LoadTexture("hero_knife_move.png");
	textures[tex_Hero_Pistol_Idle] = LoadTexture("hero_pistol_idle.png");
	textures[tex_Hero_Pistol_Melee] = LoadTexture("hero_pistol_melee.png");
	textures[tex_Hero_Pistol_Move] = LoadTexture("hero_pistol_move.png");
	textures[tex_Hero_Pistol_Reload] = LoadTexture("hero_pistol_reload.png");
	textures[tex_Hero_Pistol_Shoot] = LoadTexture("hero_pistol_shoot.png");
	textures[tex_Hero_Rifle_Idle] = LoadTexture("hero_rifle_idle.png");
	textures[tex_Hero_Rifle_Melee] = LoadTexture("hero_rifle_melee.png");
	textures[tex_Hero_Rifle_Move] = LoadTexture("hero_rifle_move.png");
	textures[tex_Hero_Rifle_Reload] = LoadTexture("hero_rifle_reload.png");
	textures[tex_Hero_Rifle_Shoot] = LoadTexture("hero_rifle_shoot.png");
	textures[tex_Menu] = LoadTexture("menu.png");
	textures[tex_TitleScreen] = LoadTexture("title-screen.png");
	textures[tex_Wire] = LoadTexture("wire.png");
	textures[tex_Zombie_Attack] = LoadTexture("zombie-attack.png");
	textures[tex_Zombie_Idle] = LoadTexture("zombie-idle.png");
	textures[tex_Zombie_Move] = LoadTexture("zombie-move.png");
	textures[tex_MetalSlab] = LoadTexture("metalslab.png");

	std::cout << "File loading complete" << std::endl;
	
}
