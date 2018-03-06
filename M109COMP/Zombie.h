#pragma once
//#include "AnimatedSprite.h"
#include "Player.h"
#include <math.h>

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

class Zombie : public GameObject
{
private:
	AnimatedSprite* Sprite[zs_max];
	AnimatedSprite* currentAnimation;
	Player* player;
	int AlertState;
	int health;
	bool dead;
public:
	Zombie(TextureSystem* ts, Player* newPlayer);
	~Zombie();
	void Update(float dt);
	void CheckHit();
	void Move(float dt);
	void UpdateAnimationsState();
	void Render(sf::RenderWindow* window);
};

