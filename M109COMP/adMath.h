#ifndef _ADMATH_H_
#define _ADMATH_H_

#include<SFML\Graphics.hpp>
#include<cmath>
//this is a file with a few wee extra math functions that makes life easier for myself
namespace am
{

	int Sign(float number);
	float Abs(float number);
	

	sf::Vector2f RotationToDirection(float Rotation);
	float PositionToRotation(sf::Vector2f pos);
	

	float Clamp(float val, float min, float max);
	

}

#endif