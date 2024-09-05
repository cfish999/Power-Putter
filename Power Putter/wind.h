#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Wind {
	public:

		Wind(GameDataRef data);

		void Draw();
		void Animate(float dt);
		const sf::Sprite& GetSprite() const;

	private:

		GameDataRef _data;

		sf::Sprite _windSprite;
		std::vector<sf::Texture> _animationFrames;

		unsigned int _animationIterator;

		sf::Clock _clock;
		sf::Clock _movementClock;

	};
}