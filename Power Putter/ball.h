#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Ball {
	public:

		Ball(GameDataRef data);

		void SpawnBall(int x,int y, float scaleX, float scaleY);
		void Draw();
		void Update(float dt);
		void Move(float angle, sf::Vector2f speed);
		void MovedByWind(float angle, sf::Vector2f speed, int direction);
		void CollidedWithSpringboard(float angle, sf::Vector2f speed);
		void BouncedOffSpringboard(float angle, sf::Vector2f speed, int direction);
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