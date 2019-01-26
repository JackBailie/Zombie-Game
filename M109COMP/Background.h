#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include <SFML\Graphics.hpp>
#include "TextureSystem.h"

class BackGround
{

private:
	sf::Sprite backsprite;
	sf::Sprite sprite;
	sf::Sprite leftsprite;
	sf::Sprite rightsprite;
	sf::Sprite topsprite;
	sf::Sprite bottomsprite;

public:
	BackGround(TextureSystem* ts);
	~BackGround();
	void Render(sf::RenderWindow* window);

};

#endif