#pragma once
//#include "AnimatedSprite.h"
#include "Player.h"
#include <math.h>

const int HEARING_DIST = 350;
const int SEEING_DIST = 1000;

enum zombieStates
{

	zs_walk,
	zs_idle,
	zs_attack,
	zs_max

};

enum zombieAlert
{

	za_notSeen,
	za_Seen

};

enum zombieSandboxStates
{

	zss_Wait,
	zss_WalkForward,
	zss_WalkLeft,
	zss_WalkRight

};

class Zombie : public GameObject
{
private:
	AnimatedSprite* Sprite[zs_max];
	AnimatedSprite* currentAnimation;
	Player* player;
	std::vector<sf::Sprite> bloodSplat;
	int AlertState;
	int health;
	bool dead;
	bool attacking;
	float velocity;
	float animationSpeed;
	int sandboxState;
	float sandboxWaitTime;
	TextureSystem* ts;
public:
	Zombie(TextureSystem* newts, Player* newPlayer, sf::Vector2i startPos);
	~Zombie();
	void Update(float dt, std::vector<Zombie>* otherZombies);
	void BounceOffZombies(std::vector<Zombie>* otherZombies);
	void CheckHit();
	void CheckMeleeAtttacked();
	void Move(float dt);
	void UpdateAnimationsState();
	void RenderBlood(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	bool Attack();
	bool GetAlive() { return !dead; };
	void CreateBlood();
	void KeepInBounds();
	void SandBox(float dt); 
	void CheckAlert();
};

