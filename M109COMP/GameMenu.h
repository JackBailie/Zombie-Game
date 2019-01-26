#pragma once
#include <SFML\Graphics.hpp>
#include "States.h"

const int RAIN_COUNT = 300;

class SFML_GameMenu :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_GameMenu(std::string filename, int windowWidth, int windowHeight);
	~SFML_GameMenu();

	void Update(float dt, sf::RenderWindow* window, int* state);

private:

	sf::Texture		m_logo;
	sf::Sprite		m_logoSprite;

	sf::Texture		m_backgroundTexture;
	sf::Sprite		m_backgroundSprite;
	sf::FloatRect	m_backgroundRect;

	sf::Font		m_menuFont;
	std::vector<sf::Text> m_menuText;

	sf::Color normalTextColor;
	sf::Color normalOutlineColor;
	sf::Color highlightedTextColor;
	sf::Color highlightedOutlineColor;

	bool m_GameHasOpened;
	bool mousePressedOnce;

	void PlayGameClicked(int* state);

	sf::CircleShape rain[RAIN_COUNT];

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

