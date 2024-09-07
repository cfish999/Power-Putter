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
			// if the centre of the ball is between the rightmost of the target width and leftmost of the target width
			if (rect1.getPosition().y < rect2.getPosition().y + (rect2.width / 2) && rect1.getPosition().y > rect2.getPosition().y - (rect2.width / 2)) {
				return true;
			}
		}

		return false;
		
		
	}


	bool Collision::CheckBoundAreaAndBallCollision(sf::Sprite sprite1, sf::Vector2f window)
	{
		sf::Rect<float> rect1 = sprite1.getGlobalBounds();

		// if the centre of the ball is between the top of the window height and bottom
		if (rect1.getPosition().x < window.x && rect1.getPosition().x > 0) {
			// if the centre of the ball is between the rightmost of the window width and leftmost of the window width
			if (rect1.getPosition().y < window.y && rect1.getPosition().y > 0) {
				return true;
			}
		}

		return false;
	}

	int Collision::CheckBallAndSquareCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		// using AABB for collisions 
		sf::Vector2i delta (abs(sprite2.getPosition().x - sprite1.getPosition().x), 
			abs(sprite2.getPosition().y - sprite1.getPosition().y));

		sf::Vector2f overlap((sprite1.getGlobalBounds().height / 2) + (sprite2.getGlobalBounds().height / 2) - delta.x,
			(sprite1.getGlobalBounds().width / 2) + (sprite2.getGlobalBounds().width / 2) - delta.y);

		if (overlap.x > 0.0 && overlap.y > 0.0) {
			
			if (overlap.x > overlap.y) {
				return 1;
			}
			else {
				return 2;
			}
		}

		return 0;
	}

	bool Collision::CheckBallAndWindCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{

		sf::Rect<float> rect1 = sprite1.getGlobalBounds();
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		// if it collides
		if (rect1.intersects(rect2)) {
			return true;
		}
		else {
			return false;
		}
	}

	int Collision::CheckBallAndRectangleCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		// using AABB for collisions 
		sf::Vector2i delta(abs(sprite2.getPosition().x - sprite1.getPosition().x),
			abs(sprite2.getPosition().y - sprite1.getPosition().y));

		sf::Vector2f overlap((sprite1.getGlobalBounds().width / 2) + (sprite2.getGlobalBounds().width / 2) - delta.x,
			(sprite1.getGlobalBounds().height / 2) + (sprite2.getGlobalBounds().height / 2) - delta.y);

		if (overlap.x > 0.0 && overlap.y > 0.0) {

			if (overlap.x > overlap.y) {
				return 1;
			}
			else {
				return 2;
			}
		}

		return 0;
	}

	bool Collision::CheckBallAndSpringSideCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		// checks for direction bouncing off the right (height) 
		// using AABB for collisions 
		sf::Vector2i delta(abs(sprite2.getPosition().x - sprite1.getPosition().x),
			abs(sprite2.getPosition().y - sprite1.getPosition().y));

		sf::Vector2f overlap((sprite1.getGlobalBounds().height / 2) + (sprite2.getGlobalBounds().height / 2) - delta.x,
			(sprite1.getGlobalBounds().width / 2) + (sprite2.getGlobalBounds().width / 2) - delta.y);

		if (overlap.x > 0.0 && overlap.y > 0.0) {

			if (overlap.x < overlap.y) {
				// does spring off the x axis 
				return true;
			}

		}

		// doesn't spring of the x axis 
		return false;
	}



}