#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Fan {
	public:

		Fan(GameDataRef data);

		void Draw();
		void Animate(float dt);
		const sf::Sprite& GetSprite() const;

	private:

		GameDataRef _data;

		sf::Sprite _fanSprite;
		std::vector<sf::Texture> _animationFrames;

		unsigned int _animationIterator;

		sf::Clock _clock;
		sf::Clock _movementClock;

	};
}