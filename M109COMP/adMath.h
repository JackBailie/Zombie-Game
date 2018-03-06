#ifndef _ADMATH_H_
#define _ADMATH_H_

#include<SFML\Graphics.hpp>
//this is a file with a few wee extra math functions that makes life easier for myself
namespace am
{

	int Sign(float number)
	{

		if (number > 0)
		{
			return 1;
		}
		else
		{

			return -1;

		}

	}
	float Abs(float number)
	{

		if (number < 0)
		{

			return -number;

		}

		return number;

	}

	sf::Vector2f RotationToDirection(float Rotation)
	{

		sf::Vector2f tempDirection;
		tempDirection.x = sin(Rotation*0.0174533f);
		tempDirection.y = -cos(Rotation*0.0174533f);
		return tempDirection;

	}

}

#endif