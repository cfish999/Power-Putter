#include "collision.h"
#include <iostream>

namespace Fish {


	Collision::Collision() {

	}

	bool Collision::CheckTargetAndBallCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
		sf::Rect<float> rect1 = sprite1.getGlobalBounds();
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		

		// if the centre of the ball is between the top of the target height and bottom
		if (rect1.getPosition().x < rect2.getPosition().x + (rect2.height / 2) && rect1.getPosition().x > rect2.getPosition().x - (rect2.height / 2)) {

			if (rect1.getPosition().y < rect2.getPosition().y + (rect2.width / 2) && rect1.getPosition().y > rect2.getPosition().y - (rect2.width / 2)) {
				return true;
			}
		}

		return false;
		
		
	}

}