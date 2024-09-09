#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class PowerBar {
	public:

		PowerBar(GameDataRef data);

		void SpawnPowerBar(int x, int y, float scaleX, float scaleY);
		void Draw();
		void Animate(float dt);
		float GetSpeed();
		const sf::Sprite& GetSprite() const;

	private:

		GameDataRef _data;

		sf::Sprite _powerBarSprite;
		std::vector<sf::Texture> _animationFrames;

		unsigned int _animationIterator;
		bool rising = true;
		bool powerBarNeeded = true;
		int posY = 0;
		int posX = 0;

		sf::Clock _clock;
		sf::Clock _movementClock;

	};
}