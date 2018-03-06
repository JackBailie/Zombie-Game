#include "GameObject.h"

void GameObject::Move(float x, float y)
{

	Position.x += x;
	Position.y += y;

}

void GameObject::SetPos(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

sf::Vector2f GameObject::GetPos()
{
	return Position;
}
