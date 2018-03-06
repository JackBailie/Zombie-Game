#ifndef _TEXTURESYSTEM_H_
#define _TEXTURESYSTEM_H_
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

enum enum_Textures
{

	tex_Blood,
	tex_Bullet,
	tex_BulletSlug,
	tex_Continue,
	tex_Dirt,
	tex_fog,
	tex_GameLogo,
	tex_Hero_Flashlight_Idle,
	tex_Hero_Flashlight_Melee,
	tex_Hero_Flashlight_Move,
	tex_Hero_Knife_Idle,
	tex_Hero_Knife_Melee,
	tex_Hero_Knife_Move,
	tex_Hero_Pistol_Idle,
	tex_Hero_Pistol_Melee,
	tex_Hero_Pistol_Move,
	tex_Hero_Pistol_Reload,
	tex_Hero_Pistol_Shoot,
	tex_Hero_Rifle_Idle,
	tex_Hero_Rifle_Melee,
	tex_Hero_Rifle_Move,
	tex_Hero_Rifle_Reload,
	tex_Hero_Rifle_Shoot,
	tex_Menu,
	tex_TitleScreen,
	tex_Wire,
	tex_Zombie_Attack,
	tex_Zombie_Idle,
	tex_Zombie_Move,
	tex_Max

};

class TextureSystem
{

public:
	TextureSystem();
	sf::Texture LoadTexture(std::string path);
	sf::Texture AquireTexture(int textureID);
	sf::Sprite sprite;

//private:
	void InitialiseTextures();
	
	sf::Texture textures[tex_Max];

};

#endif