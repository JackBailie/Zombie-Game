#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "AnimatedSprite.h"
#include<string>
#include<SFML\Audio.hpp>
#include"adMath.h"

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
	std::string name;
	int damage;
	int meleeDamage;
	int ammo;
	bool ranged;
	bool available;
	int magSize;
	int magContents;
	float nextFireTime;
	bool reloading;
	sf::SoundBuffer fireSoundBuffer;
	sf::Sound fireSound;
	int rateOfFire;
	
public:
	AnimatedSprite walkSprite;
	AnimatedSprite idleSprite;
	AnimatedSprite shootSprite;
	AnimatedSprite meleeSprite;
	AnimatedSprite reloadSprite;


	Weapon(int newDamage, int newAmmo, int newMeleeDamage,bool newRanged, bool newAvailable, int newMagSize, std::string newName, int rof);
	void SetUpSprites(int weapon, TextureSystem* textureSystem);
	void Update(float dt);
	bool Shoot(Player* player);
	bool CanShoot();
	bool IsAvailable() { return available; }
	void SetName(std::string newName) { name = newName; };
	void Reload();
	bool getReloading() { return reloading; };
	int getMagContents() { return magContents; };
	int getAmmo() { return ammo; };
	int GetMeleeDamage() { return meleeDamage; };
	int GetDamage() { return damage; };
	std::string GetName() { return name; };


};

class FlashLight : public Weapon
{
public:
	FlashLight();

};

#endif