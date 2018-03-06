#include "Weapon.h"
#include <iostream>

Weapon::Weapon(int newDamage, int newAmmo, int newMeleeDamage, bool newRanged, bool newAvailable, int newMagSize)
{

	damage = newDamage;
	ammo = newAmmo;
	meleeDamage = newMeleeDamage;
	ranged = newRanged;
	available = newAvailable;
	magSize = newMagSize;
	nextFireTime = 0;

	if (!fireSoundBuffer.loadFromFile("Assets/Sounds/ak47-1.wav"))
	{

		std::cout << "Failed to load sound file" << std::endl;

	}
	fireSound.setBuffer(fireSoundBuffer);
	fireSound.setVolume(3);

}

//Assigns all of the weapons a unique player sprite
void Weapon::SetUpSprites(int weapon, TextureSystem* textureSystem)
{

	switch (weapon)
	{

	case weap_FlashLight:
		walkSprite.Initialise(tex_Hero_Flashlight_Move, 20, textureSystem);
		idleSprite.Initialise(tex_Hero_Flashlight_Idle, 20, textureSystem);
		meleeSprite.Initialise(tex_Hero_Flashlight_Melee, 15, textureSystem);
		break;
	case weap_Knife:
		walkSprite.Initialise(tex_Hero_Knife_Move, 20, textureSystem);
		idleSprite.Initialise(tex_Hero_Knife_Idle, 20, textureSystem);
		meleeSprite.Initialise(tex_Hero_Knife_Melee, 15, textureSystem);
		break;
	case weap_Pistol:
		walkSprite.Initialise(tex_Hero_Pistol_Move, 20, textureSystem);
		idleSprite.Initialise(tex_Hero_Pistol_Idle, 20, textureSystem);
		meleeSprite.Initialise(tex_Hero_Pistol_Melee, 15, textureSystem);
		shootSprite.Initialise(tex_Hero_Pistol_Shoot, 3, textureSystem);
		reloadSprite.Initialise(tex_Hero_Pistol_Reload, 15, textureSystem);
		break;
	default:
	case weap_Rifle:
		walkSprite.Initialise(tex_Hero_Rifle_Move, 20, textureSystem);
		idleSprite.Initialise(tex_Hero_Rifle_Idle, 20, textureSystem);
		meleeSprite.Initialise(tex_Hero_Rifle_Melee, 15, textureSystem);
		shootSprite.Initialise(tex_Hero_Rifle_Shoot, 3, textureSystem);
		reloadSprite.Initialise(tex_Hero_Rifle_Reload, 20, textureSystem);
		break;
	
	}
	walkSprite.SetOrigin(100, walkSprite.GetSprite()->getTexture()->getSize().y / 2);
	idleSprite.SetOrigin(100, idleSprite.GetSprite()->getTexture()->getSize().y / 2);
	meleeSprite.SetOrigin(100, meleeSprite.GetSprite()->getTexture()->getSize().y / 2);
	if (ranged)
	{
		shootSprite.SetOrigin(100, shootSprite.GetSprite()->getTexture()->getSize().y / 2);
		reloadSprite.SetOrigin(100, reloadSprite.GetSprite()->getTexture()->getSize().y / 2);
	}

}

void Weapon::Update(float dt)
{

	nextFireTime -= dt;
	//std::cout << nextFireTime << std::endl;

}

bool Weapon::Shoot(Player* player)
{

	if (!CanShoot())
	{

		return false;
		if (!ranged)
		{

			return false;

		}

	}
	//weapon has fired successfully
	nextFireTime = 1.0f/600*60;
	fireSound.stop();
	fireSound.play();
	return true;

}

bool Weapon::CanShoot()
{
	if (ammo <= 0 || nextFireTime > 0)
	{
		return false;
	}
	return true;

}



