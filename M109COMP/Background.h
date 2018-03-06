#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include <SFML\Graphics.hpp>
#include "TextureSystem.h"

class BackGround
{

private:
	sf::Sprite sprite;

public:
	BackGround(TextureSystem* ts);
	~BackGround();
	void Render(sf::RenderWindow* window);

};

#endif