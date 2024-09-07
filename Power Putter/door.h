#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Door {
	public:

		Door(GameDataRef data);

		void Draw();
		void Animate(float dt);
		const sf::Sprite& GetDoorSprite() const;
		const sf::Sprite& GetRightOpenDoor() const;
		const sf::Sprite& GetLeftOpenDoor() const;

		unsigned int _animationIterator;

	private:

		GameDataRef _data;

		sf::Sprite _doorSprite;
		sf::Sprite _openRightDoorSprite;
		sf::Sprite _openLeftDoorSprite;
		std::vector<sf::Texture> _animationFrames;

		bool _animation = true;
		bool _reverse = false;

		sf::Clock _clock;
		sf::Clock _doorOpeningClock;

	};
}