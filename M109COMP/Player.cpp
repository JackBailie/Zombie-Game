#include "Player.h"
#include <iostream>
#include <algorithm>



Player::Player(TextureSystem* textureSystem) :
	health(1.0f),
	dead(false)
{
	walkingSprite.Initialise(tex_Hero_Flashlight_Move, 20, textureSystem);
	sf::Sprite* tempSprite = walkingSprite.GetSprite();
	tempSprite->setOrigin(100, tempSprite->getTexture()->getSize().y / 2);
	
	idleSprite.Initialise(tex_Hero_Flashlight_Idle, 20, textureSystem);
	tempSprite = idleSprite.GetSprite();
	tempSprite->setOrigin(100, tempSprite->getTexture()->getSize().y / 2);
	
	meleeSprite.Initialise(tex_Hero_Flashlight_Melee, 15, textureSystem);
	tempSprite = meleeSprite.GetSprite();
	tempSprite->setOrigin(100, tempSprite->getTexture()->getSize().y / 2);

	SetPos(100, 100);
	velocity.x = 0;
	velocity.y = 0;
	
	SetUpWeapons(textureSystem);
	ts = textureSystem;
	EquipWeapon(weap_Rifle);

	weaponSelectButtons[weap_FlashLight] = sf::Keyboard::Num1;
	weaponSelectButtons[weap_Knife] = sf::Keyboard::Num2;
	weaponSelectButtons[weap_Pistol] = sf::Keyboard::Num3;
	weaponSelectButtons[weap_Rifle] = sf::Keyboard::Num4;

}

void Player::SetUpWeapons(TextureSystem* textureSystem)
{

	weapons[weap_FlashLight]	= new Weapon(0, 0, 20, false, true, 0, "FlashLight", 0);
	weapons[weap_Knife]			= new Weapon(0, 0, 70, false, true, 0, "Knife", 0);
	weapons[weap_Pistol]		= new Weapon(35, 30, 20, true, true, 18, "G17", 1000);
	weapons[weap_Rifle]			= new Weapon(55, 10000, 20, true, true, 30, "AKM", 600);
	for (int i = 0; i <= weap_Rifle; i++)
	{

		weapons[i]->SetUpSprites(i, textureSystem);

	}
	currentAnimation = &weapons[0]->idleSprite;

}

void Player::Update(float dt, sf::RenderWindow* window, sf::View* view)
{

	currentAnimation->Update(dt, animationspeed);
	UpdateAnimationState();
	UpdateMovement(dt);
	
	currentAnimation->GetSprite()->setPosition(GetPos());
	UpdateRotation(dt, window, view);
	UpdateView(view);
	window->setView(*view);
	equippedWeapon->Update(dt);

	for (unsigned int i = 0; i < bullets.size(); i++)
	{

		bullets.at(i).Update(dt);
		if (bullets.at(i).GetShouldDestroy())
		{

			bullets.erase(bullets.begin() + i);

		}

	}

	if (equippedWeapon->getReloading())
	{
		actionState = 4;
	}
	SelectWeapon();

	if (health < 0.0f)
	{
		Reset();
	}

}

void Player::UpdateMovement(float dt)
{
	float speed = 10.0f;
	float friction = 10;
	float acceleration = 150;
	meleed = false;

	actionState = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		velocity.x += acceleration * dt;
		actionState = 0;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{

		velocity.x -= acceleration * dt;
		actionState = 0;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{

		velocity.y += acceleration * dt;
		actionState = 0;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{

		velocity.y -= acceleration * dt;;
		actionState = 0;

	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Meleeing && equippedWeapon->Shoot(this)|| Shooting)
	{
		float tempRotation = currentAnimation->GetSprite()->getRotation() + 90;
		if (!Shooting)
		{
			Bullet tempBullet(ts, GetPos().x + am::RotationToDirection(tempRotation + 13).x * 180, GetPos().y + am::RotationToDirection(tempRotation + 13).y * 180, tempRotation, equippedWeapon->GetDamage());
			bullets.push_back(tempBullet);
			std::cout << bullets.size() << std::endl;
		}
		actionState = 3;
		Shooting = true;
		
		if (equippedWeapon->shootSprite.GetFinished())
		{
			Shooting = false;
		}

	}
	//std::cout << actionState << std::endl;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !Shooting || Meleeing)
	{
		Meleeing = true;
		actionState = 2;
		if (equippedWeapon->meleeSprite.GetFinished())
		{
			meleed = true;
			Meleeing = false;
		}
	}

	velocity.x = std::min(std::max(velocity.x, -speed),speed);
	velocity.y = std::min(std::max(velocity.y, -speed), speed);
	velocity.x -= velocity.x * dt * friction;
	velocity.y -= velocity.y * dt * friction;

	Move(velocity.x*dt*100, velocity.y*dt*100);
	//std::cout << velocity.x << " " << velocity.y << std::endl;
	KeepInBounds();
	
}

void Player::UpdateRotation(float dt, sf::RenderWindow* window, sf::View* view)
{

	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	int xdist = mousePos.x - window->getSize().x/2;
	int ydist = mousePos.y - window->getSize().y/2;

	currentAnimation->GetSprite()->setRotation(std::atan2(ydist, xdist)*57);

}

void Player::UpdateAnimationSpeed()
{


}

void Player::UpdateView(sf::View* view)
{
	view->setCenter(GetPos().x, GetPos().y);
}

void Player::KeepInBounds()
{

	if(GetPos().x < 0)
	{
		SetPos(0, GetPos().y);
	}

	if (GetPos().x > 8000)
	{
		SetPos(8000, GetPos().y);
	}
	if (GetPos().y < 0)
	{
		SetPos(GetPos().x, 0);
	}

	if (GetPos().y > 6000)
	{
		SetPos(GetPos().x, 6000);
	}

}

void Player::EquipWeapon(int weaponID)
{
	
	if (weapons[weaponID]->IsAvailable())
	{
		equippedWeapon = weapons[weaponID];
	}

}

void Player::SelectWeapon()
{

	for (unsigned int i = 0; i < 4; i++)
	{
		if (sf::Keyboard::isKeyPressed(weaponSelectButtons[i]))
		{
			EquipWeapon(i);
		}
	}

}

void Player::Render(sf::RenderWindow * window)
{

	
	for (unsigned int i = 0; i < bullets.size(); i++)
	{

		bullets.at(i).Render(window);

	}
	currentAnimation->Render(window);

}

bool Player::GetMeleeAttacked()
{
	return meleed;
}

void Player::UpdateAnimationState()
{

	switch (actionState)
	{
	
	case 0:
		currentAnimation = &equippedWeapon->walkSprite;
		animationspeed = std::max(am::Abs(velocity.x/8), am::Abs(velocity.y/8));
		break;
	
	case 1:
		currentAnimation = &equippedWeapon->idleSprite;
		animationspeed = 1;
		break;
	
	case 2:
		currentAnimation = &equippedWeapon->meleeSprite;
		animationspeed = 1;
		break;
	case 3:
		currentAnimation = &equippedWeapon->shootSprite;
		animationspeed = 1.5f;
		break;
	case 4:
		currentAnimation = &equippedWeapon->reloadSprite;
		animationspeed = 1;
		break;
	
	default:
		currentAnimation = &walkingSprite;
		animationspeed = 2;
		break;
	
	}

}

void Player::Reset()
{

	dead = false;
	health = 1.0f;
	SetPos(100, 100);

}