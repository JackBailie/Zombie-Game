#include "Bullet.h"
#include <math.h>
#include<iostream>


Bullet::Bullet(TextureSystem* ts, float posx, float posy, float rotation, int newDamage):
lifeTime(0)
{

	texture = &ts->textures[tex_BulletSlug];
	sprite.setTexture(*texture);
	sprite.setScale(2, 2);
	pos.x = posx;
	pos.y = posy;
	sprite.setPosition(pos.x, pos.y);
	sprite.setRotation(rotation);
	Damage = newDamage;

}


Bullet::~Bullet()
{
}

void Bullet::SetTexture(TextureSystem* ts)
{

	

}

void Bullet::Update(float dt)
{
	
	pos.x += ((dt * BULLET_SPEED)*sin((sprite.getRotation())*0.0174533f))*3.14f / 180;
	pos.y -= ((dt * BULLET_SPEED)*cos((sprite.getRotation())*0.0174533f))*3.14f / 180;
	lifeTime += dt;
	sprite.setPosition(pos);

}

bool Bullet::GetShouldDestroy()
{
	if (lifeTime > 5.0f)
	{

		return true;

	}
	return false;
}

void Bullet::Render(sf::RenderWindow* window)
{

	window->draw(sprite);

}