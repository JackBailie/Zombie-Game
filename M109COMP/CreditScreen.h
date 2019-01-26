#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
class SFML_CreditScreen :
	public sf::Drawable
{
private:
	sf::Texture	logoTexture;
	sf::Sprite	logoSprite;
	sf::Text logotext;
	float textOpacity;
	std::vector<sf::Text> sfml_CreditsText;
	sf::Font sfml_Font;
	
	sf::Vector2f textPosition;
	float textSpacing;

public:
	SFML_CreditScreen(int windowWidth, int windowHeight);
	~SFML_CreditScreen();
	void Update(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Reset();
	
};

