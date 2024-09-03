#pragma once

#include <SFML/Graphics.hpp>

namespace Fish {

	class Collision {
	public:
		Collision();

		bool CheckTargetAndBallCollision(sf::Sprite sprite1, sf::Sprite sprite2);


	};
}