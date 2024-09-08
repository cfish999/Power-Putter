#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Door {
	public:

		Door(GameDataRef data);

		void spawnDoor(int x, int y, float scaleX, float scaleY, int rotation);
		void Draw();
		void Animate(float dt);
		const std::vector<sf::Sprite>& GetSprites() const;
		const std::vector<sf::Sprite>& GetRightOpenDoors() const;
		const std::vector<sf::Sprite>& GetLeftOpenDoors() const;
		const std::vector<int>& GetDirections() const;

		unsigned int _animationIterator;

	private:

		GameDataRef _data;

		sf::Sprite _doorSprite;
		sf::Sprite _openRightDoorSprite;
		sf::Sprite _openLeftDoorSprite;
		std::vector<sf::Sprite> _doorSprites;
		std::vector<sf::Sprite> _doorRightSprites;
		std::vector<sf::Sprite> _doorLeftSprites;
		std::vector<int> _doorDirections;
		std::vector<sf::Texture> _animationFrames;

		bool _animation = true;
		bool _reverse = false;

		sf::Clock _clock;
		sf::Clock _doorOpeningClock;

	};
}