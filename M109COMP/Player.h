#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "GameObject.h"
#include "TextureSystem.h"
#include <SFML\Graphics.hpp>
#include "Weapon.h"
#include "Bullet.h"
#include <vector>
#include "adMath.h"

//class Weapon;

class Player : public GameObject
{

private:
	AnimatedSprite walkingSprite;
	AnimatedSprite idleSprite;
	AnimatedSprite meleeSprite;
	AnimatedSprite* currentAnimation;
	bool Shooting = false;
	bool Meleeing = false;
	bool meleed;
	Weapon* weapons[4];
	sf::Keyboard::Key weaponSelectButtons[4];
	TextureSystem* ts;
	float health;
	bool dead;

	Weapon* equippedWeapon;
	

	sf::Vector2f velocity;
	int actionState = 0;
	void UpdateAnimationState();
	float animationspeed;
	void SetUpWeapons(TextureSystem* textureSystem);

public:
	Player(TextureSystem* textureSystem);
	void Update(float dt, sf::RenderWindow* window, sf::View* view);
	void UpdateMovement(float dt);
	void UpdateRotation(float dt, sf::RenderWindow* window, sf::View* view);
	void UpdateAnimationSpeed();
	void UpdateView(sf::View* view);
	void KeepInBounds();
	void EquipWeapon(int weaponID);
	void SelectWeapon();
	Weapon* GetWeapon() { return equippedWeapon; };
	void Render(sf::RenderWindow* window);
	bool GetMeleeAttacked();
	void Hurt(float value) { health -= value; };
	float GetHealth() { return health; };
	float GetRotation() { return currentAnimation->GetSprite()->getRotation(); };
	void Shoot();
	void SetActionState(int num) { actionState = num; };
	void Reset();

	std::vector<Bullet> bullets;
	

};

#endif