#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "AnimatedSprite.h"
#include<string>
#include<SFML\Audio.hpp>

class Player;

enum e_Weapon
{

	weap_FlashLight,
	weap_Knife,
	weap_Pistol,
	weap_Rifle

};

class Weapon
{

private:
	int damage;
	int meleeDamage;
	int ammo;
	bool ranged;
	bool available;
	int magSize;
	float nextFireTime;
	sf::SoundBuffer fireSoundBuffer;
	sf::Sound fireSound;
	
public:
	AnimatedSprite walkSprite;
	AnimatedSprite idleSprite;
	AnimatedSprite shootSprite;
	AnimatedSprite meleeSprite;
	AnimatedSprite reloadSprite;


	Weapon(int newDamage, int newAmmo, int newMeleeDamage,bool newRanged, bool newAvailable, int newMagSize);
	void SetUpSprites(int weapon, TextureSystem* textureSystem);
	void Update(float dt);
	bool Shoot(Player* player);
	bool CanShoot();
	bool IsAvailable() { return available; }


};

class FlashLight : public Weapon
{
public:
	FlashLight();

};

#endif