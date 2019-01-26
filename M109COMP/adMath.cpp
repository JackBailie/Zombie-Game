#include"adMath.h"

int am::Sign(float number)
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


float am::Abs(float number)
{

	if (number < 0)
	{

		return -number;

	}

	return number;

}

sf::Vector2f am::RotationToDirection(float Rotation)
{

	sf::Vector2f tempDirection;
	tempDirection.x = sin(Rotation*0.0174533f);
	tempDirection.y = -cos(Rotation*0.0174533f);
	return tempDirection;

}

float am::PositionToRotation(sf::Vector2f pos)
{
	float rotation = std::atan2(pos.y, pos.x) * 57;


	return rotation;
}

float am::Clamp(float val, float min, float max)
{

	if (val < min)
	{
		return min;
	}
	else if (val > max)
	{
		return max;
	}
	else
	{
		return val;
	}

}