#include "Zombie.h"
#include <iostream>
#include<algorithm>



Zombie::Zombie(TextureSystem* newts, Player* newPlayer, sf::Vector2i startPos) :
	health(100),
	dead(false),
	AlertState(za_notSeen),
	velocity(0),
	animationSpeed(1.0f),
	sandboxState(0),
	sandboxWaitTime(5.0f)
{
	ts = newts;
	SetPos(0, 0);
	Sprite[zs_idle] = new AnimatedSprite;
	Sprite[zs_idle]->Initialise(tex_Zombie_Idle, 17, ts);
	Sprite[zs_idle]->SetOrigin(100, Sprite[zs_idle]->GetSprite()->getTexture()->getSize().y / 2);
	Sprite[zs_idle]->Update(0.1f, 1);
	Sprite[zs_walk] = new AnimatedSprite;
	Sprite[zs_walk]->Initialise(tex_Zombie_Move, 17, ts);
	Sprite[zs_walk]->SetOrigin(100, Sprite[zs_walk]->GetSprite()->getTexture()->getSize().y / 2);
	Sprite[zs_attack] = new AnimatedSprite;
	Sprite[zs_attack]->Initialise(tex_Zombie_Attack, 9, ts);
	Sprite[zs_attack]->SetOrigin(100, Sprite[zs_attack]->GetSprite()->getTexture()->getSize().y / 2);
	currentAnimation = Sprite[zs_idle];
	player = newPlayer;

	SetPos(startPos.x, startPos.y);
	currentAnimation->GetSprite()->setPosition(GetPos());
}


Zombie::~Zombie()
{
	for (int i = 0; i < zs_max; i++)
	{

		if (Sprite[i] != NULL)
		{
			//delete Sprite[i];
			//Sprite[i] = NULL;
		}

	}
}

void Zombie::Update(float dt, std::vector<Zombie>* otherZombies)
{
	if (dead)
	{
		return;
	}
	sf::Vector2f tempPos = player->GetPos();
	int xdist = tempPos.x - GetPos().x;
	int ydist = tempPos.y - GetPos().y;

	
	currentAnimation->Update(dt, animationSpeed);

	UpdateAnimationsState();

	if (health <= 0)
	{
		currentAnimation = Sprite[zs_idle];
		currentAnimation->GetSprite()->setColor(sf::Color(255, 0, 0));
		dead = true;

	}
	CheckHit();
	
	if (AlertState == za_Seen)
	{
		velocity += dt;
		velocity = std::min(velocity, 1.0f);
		Move(dt);
		currentAnimation->GetSprite()->setRotation(std::atan2(ydist, xdist) * 57);
	}
	else if (AlertState == za_notSeen)
	{
		SandBox(dt);
	}
	
	
	BounceOffZombies(otherZombies);
	if (AlertState == za_notSeen)
	{
		CheckAlert();
	}
	if (player->GetMeleeAttacked())
	{

		CheckMeleeAtttacked();

	}
}

void Zombie::BounceOffZombies(std::vector<Zombie>* otherZombies)
{
	for (unsigned int i = 0; i < otherZombies->size(); i++)
	{

		if (&otherZombies->at(i) != this && otherZombies->at(i).GetAlive())
		{
			int xdist = GetPos().x - otherZombies->at(i).GetPos().x;
			int ydist = GetPos().y - otherZombies->at(i).GetPos().y;
			int distance = am::Abs(sqrt(xdist*xdist + ydist*ydist));

			if(distance < 175)
			{
				if (xdist != 0 && ydist != 0)
				{
					SetPos(GetPos().x + 175 / xdist, GetPos().y + 175 / ydist);
				}
			}
		}

	}
}

void Zombie::CheckHit()
{

	for (int i = 0; i < player->bullets.size(); i++)
	{

		float distance = 0;
		float xdist = 0;
		float ydist = 0;

		xdist = GetPos().x - player->bullets.at(i).GetPos().x;
		ydist = GetPos().y - player->bullets.at(i).GetPos().y;
		//if (am::Abs(xdist) < 100 && am::Abs(ydist) < 100)
		{
			distance = sqrt(xdist*xdist + ydist*ydist);

			if (distance < 200)
			{
				CreateBlood();
				velocity = 0;
				health -= player->bullets.at(i).GetDamage();
				player->bullets.erase(player->bullets.begin() + i);
				
				AlertState = za_Seen;

			}
		}

	}

}

void Zombie::CheckMeleeAtttacked()
{
	int xDist = (player->GetPos().x - GetPos().x);
	int yDist = (player->GetPos().y - GetPos().y);
	int dist = sqrt(xDist*xDist + yDist*yDist);
	
	if (dist < 300)
	{
		xDist = -xDist;
		yDist = -yDist;

		float zombieDPlayer = (player->GetRotation() - 180 ) - (std::atan2(yDist, xDist) * 57);
		std::cout << xDist << " " << yDist << " " << zombieDPlayer << std::endl;
		
		if (zombieDPlayer > 160 || zombieDPlayer < -160) {
			health -= player->GetWeapon()->GetMeleeDamage();
			CreateBlood();
			velocity = -0.75f;
			AlertState = za_Seen;
		}
	}
}

void Zombie::Move(float dt)
{
	float rotation = currentAnimation->GetSprite()->getRotation()+90;
	float newPosx = sin( rotation*0.0174533f)/0.0174533f*dt * 10;
	float newPosy = cos(rotation*0.0174533f) / 0.0174533f*dt * 10;
	if (!Attack())
	{
		SetPos(GetPos().x + newPosx * velocity, GetPos().y - newPosy * velocity);
	}
	currentAnimation->GetSprite()->setPosition(GetPos());

}

void Zombie::UpdateAnimationsState()
{
	switch (AlertState)
	{
	case za_notSeen:
		currentAnimation = Sprite[zs_idle];
		animationSpeed = 1.0f;
		break;
	case za_Seen:
		if(attacking)
		{
			currentAnimation = Sprite[zs_attack];
			animationSpeed = 1.0f;
		}
		else
		{
			currentAnimation = Sprite[zs_walk];
			animationSpeed = velocity;
			
		}
		break;
	default:
		break;
	}
}

void Zombie::RenderBlood(sf::RenderWindow * window)
{
	for (unsigned int i = 0; i < bloodSplat.size(); i++)
	{

		window->draw(bloodSplat.at(i));

	}
}

void Zombie::Render(sf::RenderWindow* window)
{
	//if (GetPos().x > player->GetPos().x - 1920 && GetPos().x < player->GetPos().x + 1920 &&
	//	GetPos().y > player->GetPos().y - 1080 && GetPos().y < player->GetPos().y + 1080)
	{
		currentAnimation->Render(window);
	}
}

bool Zombie::Attack()
{
	float distance = 0;
	float xdist = 0;
	float ydist = 0;

	xdist = GetPos().x - player->GetPos().x;
	ydist = GetPos().y - player->GetPos().y;
	attacking = false;

	{
		distance = sqrt(xdist*xdist + ydist*ydist);
		
		if (distance < 100)
		{

			attacking = true;
			if (currentAnimation->GetFinished())
			{
				player->Hurt(0.05f);
			}
			return true;

		}
	}
	return false;
}

void Zombie::CreateBlood()
{
	sf::Sprite tempBlood;
	tempBlood.setTexture(ts->textures[tex_Blood]);
	tempBlood.setPosition(GetPos());
	tempBlood.setTextureRect(sf::IntRect(0, 512 * ((std::rand() % 5) + 1), 512, 512));
	tempBlood.setOrigin(256, 256);
	tempBlood.setColor(sf::Color(255, 255, 255, 180));
	bloodSplat.push_back(tempBlood);
}

void Zombie::KeepInBounds()
{
	sf::Vector2f position = GetPos();

	if (position.x < 0 || position.x > 8000 || position.y < 0 || position.y > 6000)
	{
		if (currentAnimation->GetSprite()->getRotation() < 0)
		{
			currentAnimation->GetSprite()->setRotation(currentAnimation->GetSprite()->getRotation() + 180);
		}
		else
		{
			currentAnimation->GetSprite()->setRotation(currentAnimation->GetSprite()->getRotation() - 180);
		}
	}

	
}

void Zombie::SandBox(float dt)
{

	sandboxWaitTime -= dt;
	if (sandboxWaitTime < 0)
	{
		sandboxState = std::rand() % 4;
		sandboxWaitTime = 5.0f + std::rand() % 5;
		std::cout << sandboxState << std::endl;
	}
	animationSpeed = velocity;
	float newRotation;
	switch (sandboxState)
	{
	default:
	case zss_Wait:
		velocity = 0;
		animationSpeed = 1.0f;
		break;
	case zss_WalkForward:
		currentAnimation = Sprite[zs_walk];
		velocity = 0.2f;
		break;
	case zss_WalkLeft:
		currentAnimation = Sprite[zs_walk];
		velocity = 0.2f;
		newRotation = currentAnimation->GetSprite()->getRotation() - dt*50;
		currentAnimation->GetSprite()->setRotation(newRotation);
		break;
	case zss_WalkRight:
		currentAnimation = Sprite[zs_walk];
		velocity = 0.2f;
		newRotation = currentAnimation->GetSprite()->getRotation() + dt*50;
		currentAnimation->GetSprite()->setRotation(newRotation);
		break;
	}
	
	Move(dt);
	KeepInBounds();
}

void Zombie::CheckAlert()
{
	float rotation = currentAnimation->GetSprite()->getRotation();
	float xdist = GetPos().x - player->GetPos().x;
	float ydist = GetPos().y - player->GetPos().y;
	int playerDist = sqrt(xdist*xdist + ydist*ydist);
	if (playerDist < 0)
	{
		playerDist = -playerDist;
	}
	float playerRot = am::PositionToRotation(sf::Vector2f(xdist, ydist)) - rotation;

	if (playerRot > 135 || playerRot < -135 || playerDist < HEARING_DIST)
	{
		if (playerDist < SEEING_DIST)
		{
			AlertState = za_Seen;
		}
	}

}

