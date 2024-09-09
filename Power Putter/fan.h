#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Fan {
	public:

		Fan(GameDataRef data);

		void SpawnFan(int x, int y, float scaleX, float scaleY, int rotation);
		void Draw();
		void Animate(float dt);
		const sf::Sprite& GetSprite() const;
		const std::vector<sf::Sprite>& GetSprites() const;
		const std::vector<int>& GetDirections() const;

	private:

		GameDataRef _data;

		sf::Sprite _fanSprite;
		std::vector<sf::Sprite> _fanSprites;
		std::vector<int> _fanDirection;
		std::vector<sf::Texture> _animationFrames;

		unsigned int _animationIterator;

		sf::Clock _clock;
		sf::Clock _movementClock;

	};
}