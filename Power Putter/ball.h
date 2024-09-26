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
		sf::Vector2f MovedByWind(float angle, sf::Vector2f speed, int direction);
		void CollidedWithSpringboard(float angle, sf::Vector2f speed);
		sf::Vector2f BouncedOffSpringboard(float angle, sf::Vector2f speed, int direction);
		const sf::Sprite& GetSprite() const;
		float getBallRadius();

		int _ballState;
		float _slowdown = 1.0;

	private:

		GameDataRef _data;

		sf::Sprite _ballSprite;
		
		sf::Clock _clock;
		sf::Clock _movementClock;

		sf::Vector2f speeds;

		float _rotation;
		float _ballRadius;

		int speedX;
		int speedY;
		bool _bounced = false;

	};
}