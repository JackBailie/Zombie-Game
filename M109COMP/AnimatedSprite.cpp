#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite()
{

	

}

void AnimatedSprite::Initialise(int textureID, int numFrames, TextureSystem* ts)
{
	SetTexture(&ts->textures[textureID]);
	SetupFrames(numFrames);
	frameCount = numFrames;
	currentFrame = 0;
	if (sprite.getTexture())
	{
		initialised = true;
	}
	else { std::cout << "failed to initialise" << std::endl; }
}

void AnimatedSprite::NewFrame(int x, int y, int width, int height)
{
	Frame.push_back(sf::IntRect(x, y, width, height));
}

void AnimatedSprite::SetupFrames(int numFrames)
{
	const sf::Texture* tempTexture = sprite.getTexture();
	int frameWidth = tempTexture->getSize().x/numFrames;
	int frameHeight = tempTexture->getSize().y;
	std::cout << frameWidth << std::endl;
	for (int x = 0; x < numFrames; x++)
	{

		NewFrame(x*frameWidth, 0, frameWidth, frameHeight);

	}

}

void AnimatedSprite::SetTexture(sf::Texture* texture)
{
	sprite.setTexture(*texture);
}

void AnimatedSprite::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void AnimatedSprite::SetFrame(int frame)
{
	if (frame >= 0 && frame < Frame.size())
	{
		sprite.setTextureRect(Frame.at(frame));
	}
}

void AnimatedSprite::Update(float dt, float speed)
{
	finished = false;
	AdvanceFrame(dt * speed * 30); //speed of 1 = 30fps
	SetFrame(std::max(std::min(floor(currentFrame), (float)frameCount-1), 0.0f));
	if (currentFrame + dt >= frameCount)
	{
		currentFrame = 0;
		finished = true;
	}
}

void AnimatedSprite::SetOrigin(int xOrigin, int yOrigin)
{

	sprite.setOrigin(xOrigin, yOrigin);

}
