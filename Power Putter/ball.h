#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Ball {
	public:

		Ball(GameDataRef data);

		void Draw();
		void Update(float dt);
		void Move(float speed);
		const sf::Sprite& GetSprite() const;

		int _ballState;

	private:

		GameDataRef _data;

		sf::Sprite _ballSprite;
		std::vector<sf::Texture> _animationFrames;

		unsigned int _animationIterator;

		sf::Clock _clock;
		sf::Clock _movementClock;

		float _rotation;
		float _slowdown = 1.0;

	};
}