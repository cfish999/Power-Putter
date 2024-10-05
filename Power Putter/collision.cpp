#include "collision.h"
#include <iostream>

namespace Fish {


	Collision::Collision() {

	}

	bool Collision::CheckTargetAndBallCollision(sf::Sprite sprite1, sf::Sprite sprite2, float radiusTarget, float radiusBall) {
		
		// uses circle collision to detect hitting the target
		sf::Vector2f distance(sprite1.getPosition().x - sprite2.getPosition().x, sprite1.getPosition().y - sprite2.getPosition().y);
		float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y);

		float radius = (radiusTarget + radiusBall) * (radiusTarget + radiusBall);

		// circles have overlapped i.e ball has landed on the target
		if (distanceSquared < radius) {
			return true;
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

		// descales so the wind does not immediately blow the ball so it allos the ball to get blown more centrally
		sprite2.scale(0.6, 0.6);
		sf::Rect<float> rect1 = sprite1.getGlobalBounds();
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		// collision detection
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

	bool Collision::CheckBallAndSpringSideCollision(sf::Sprite sprite1, sf::Sprite sprite2, int direction)
	{
		// using AABB for collisions 
		sf::Vector2i delta(abs(sprite2.getPosition().x - sprite1.getPosition().x),
			abs(sprite2.getPosition().y - sprite1.getPosition().y));

		sf::Vector2f overlap((sprite1.getGlobalBounds().height / 2) + (sprite2.getGlobalBounds().height / 2) - delta.x,
			(sprite1.getGlobalBounds().width / 2) + (sprite2.getGlobalBounds().width / 2) - delta.y);

		if (overlap.x > 0.0 && overlap.y > 0.0) {

			if (direction == 0 || direction == 180) {
				if (overlap.x < overlap.y) {
					// does spring off the x axis 
					return true;
				}
			}
			else {
				if (overlap.x < overlap.y) {
					// does spring off the y axis 
					return true;
				}
			}

		}

		// doesn't spring of the x or y axis 
		return false;
	}

	float Collision::CheckDistanceFromFan(sf::Sprite sprite1, sf::Sprite sprite2, int direction)
	{
		float distance;
		if (direction == 1) {
			// for up it is (fan.y - ball.y)
			distance = sprite2.getGlobalBounds().getPosition().y - sprite1.getGlobalBounds().getPosition().y;
		}
		else if (direction == 2) {
			// for down it is (ball.y - fan.y)
			distance = sprite1.getGlobalBounds().getPosition().y - sprite2.getGlobalBounds().getPosition().y;
		}
		else if (direction == 3) {
			// for right it is (ball.x - fan.x)
			distance = sprite1.getGlobalBounds().getPosition().x - sprite2.getGlobalBounds().getPosition().x;
		}
		else {
			// for left it is (fan.x - ball.x)
			distance = sprite2.getGlobalBounds().getPosition().y - sprite1.getGlobalBounds().getPosition().y;
		}

		float fanStrength = 1 / distance;

		return  fanStrength;
	}

	int Collision::CheckBallAndSpringboardCollision(sf::Sprite sprite1, sf::Sprite sprite2,float width, float height)
	{
		// using AABB for collisions 
		sf::Vector2i delta(abs(sprite2.getPosition().x - sprite1.getPosition().x),
			abs(sprite2.getPosition().y - sprite1.getPosition().y));

		sf::Vector2f overlap((sprite1.getGlobalBounds().width / 2) + (width/2) - delta.x,
			(sprite1.getGlobalBounds().height / 2) + (height/2) - delta.y);

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



}