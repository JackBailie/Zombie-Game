#ifndef _ANIMATEDSPIRTE_H_
#define _ANIMATEDSPRITE_H_
#include <vector>
#include "TextureSystem.h"
#include <SFML\Graphics.hpp>
#include <math.h>

class AnimatedSprite
{
private:
	bool finished;

public:
	sf::Sprite sprite;
	std::vector<sf::IntRect> Frame;
	bool initialised = false;
	float currentFrame;
	unsigned int frameCount;
	sf::Texture* texture;
	

	AnimatedSprite();
	void Initialise(int textureID, int numFrames, TextureSystem* ts);
	void NewFrame(int x, int y, int width, int height);
	void SetupFrames(int numFrames);
	void SetTexture(sf::Texture *texture);
	void Render(sf::RenderWindow* window);
	void AdvanceFrame(float advanceTime) { currentFrame += advanceTime; }
	void SetFrame(int frame);
	void Update(float dt, float speed);
	void SetOrigin(int xOrigin, int yOrigin);
	bool GetFinished() { return finished; };
	sf::Sprite* GetSprite() { return &sprite; }

};

#endif