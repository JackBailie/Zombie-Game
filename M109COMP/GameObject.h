#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include <SFML\Graphics.hpp>


class GameObject
{

private:
	sf::Vector2f Position;
	
public:
	void Move(float x, float y);
	void SetPos(float x, float y);
	sf::Vector2f GetPos();

};

#endif // !_GAMEOBJECT_H_
