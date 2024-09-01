#include "InputManager.h"

namespace Fish
{
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		// is the corresponding button pressed
		if (sf::Mouse::isButtonPressed(button))
		{
			// draw a rectangle around the sprite
			sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

			// if the mouse is within the sprite's area it has been clicked
			if (playButtonRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}

		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		// gets the mouse position from the window 
		return sf::Mouse::getPosition(window);
	}
}
