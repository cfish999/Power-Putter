#pragma once

#include "SFML\Graphics.hpp"

namespace Fish
{
	class InputManager
	{
	public:
		InputManager() {} // constructor 
		~InputManager() {} // destructor

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
		// add more input functions here when needed

		sf::Vector2i GetMousePosition(sf::RenderWindow& window); // vector of the x and y of the mouse position
	};
}