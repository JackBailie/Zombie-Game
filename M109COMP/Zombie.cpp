#include "Zombie.h"



Zombie::Zombie(TextureSystem* ts, Player* newPlayer) :
	health(20),
	dead(false),
	AlertState(za_notSeen)
{
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
	Sprite[zs_walk]->SetOrigin(100, Sprite[zs_walk]->GetSprite()->getTexture()->getSize().y / 2);
	currentAnimation = Sprite[zs_walk];
	player = newPlayer;
}


Zombie::~Zombie()
{
	for (int i = 0; i < zs_max; i++)
	{

		delete Sprite[i];

	}
}

void Zombie::Update(float dt)
{
	if (dead)
	{
		return;
	}
	sf::Vector2f tempPos = player->GetPos();
	int xdist = tempPos.x - GetPos().x;
	int ydist = tempPos.y - GetPos().y;

	currentAnimation->GetSprite()->setRotation(std::atan2(ydist, xdist) * 57);
	currentAnimation->Update(dt, 1);

	if (health <= 0)
	{
		currentAnimation = Sprite[zs_idle];
		currentAnimation->GetSprite()->setColor(sf::Color(255, 0, 0));
		dead = true;

	}
	CheckHit();
	UpdateAnimationsState();
	if (AlertState == za_Seen)
	{
		Move(dt);
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

		distance = sqrt(xdist*xdist + ydist*ydist);

		if (distance < 50)
		{

			health -= 1;
			player->bullets.erase(player->bullets.begin() + i);
			AlertState = za_Seen;

		}

	}

}

void Zombie::Move(float dt)
{
	float rotation = currentAnimation->GetSprite()->getRotation()+90;
	float newPosx = sin( rotation*0.0174533f)/0.0174533f*dt * 10;
	float newPosy = cos(rotation*0.0174533f) / 0.0174533f*dt * 10;

	SetPos(GetPos().x+newPosx, GetPos().y - newPosy);
	currentAnimation->GetSprite()->setPosition(GetPos());

}

void Zombie::UpdateAnimationsState()
{
	switch (AlertState)
	{
	case za_notSeen:
		currentAnimation = Sprite[zs_idle];
		break;
	case za_Seen:
		currentAnimation = Sprite[zs_walk];
		break;
	default:
		break;
	}
}

void Zombie::Render(sf::RenderWindow* window)
{

	currentAnimation->Render(window);

}

