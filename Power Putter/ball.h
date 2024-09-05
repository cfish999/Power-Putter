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
		void Move(float angle, sf::Vector2f speed);
		const sf::Sprite& GetSprite() const;

		int _ballState;

	private:

		GameDataRef _data;

		sf::Sprite _ballSprite;
		
		sf::Clock _clock;
		sf::Clock _movementClock;

		float _rotation;
		float _slowdown = 1.0;

		int speedX;
		int speedY;
		bool _bounced = false;

	};
}