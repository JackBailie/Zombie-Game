#pragma once
#include<SFML\Graphics.hpp>
#include"TextureSystem.h"

const int BULLET_SPEED = 200000;

class Bullet
{
private:
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::Vector2f pos;
	float lifeTime;

public:
	Bullet(TextureSystem* ts, float posx, float posy, float rotation);
	~Bullet();
	void SetPos(float x, float y) { pos.x = x; pos.y = y; };
	sf::Vector2f GetPos() { return pos; };
	void SetRotation(float rotation) { sprite.setRotation(rotation); };
	void SetTexture(TextureSystem* ts);
	void Update(float dt);
	bool GetShouldDestroy();
	void Render(sf::RenderWindow* window);
};

