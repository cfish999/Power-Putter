#include "ball.h"
#include "DEFINITIONS.h"
#include <iostream>


namespace Fish {

	Ball::Ball(GameDataRef data) : _data(data) {

		_ballSprite.setTexture(this->_data->assets.GetTexture("Ball Sprite"));
	}

	void Ball::SpawnBall(int x, int y, float scaleX, float scaleY)
	{
		
		// starting position of ball
		_ballSprite.setPosition(x, y);

		// rotates around the centre of the object which is this 
		sf::Vector2f origin = sf::Vector2f(_ballSprite.getGlobalBounds().width / 2, _ballSprite.getGlobalBounds().height / 2);
		_ballSprite.setOrigin(origin);

		_ballSprite.scale(scaleX, scaleY);

		_ballState = BALL_STATE_STILL;

		_rotation = 0;
	}

	void Ball::Draw() {

		_data->window.draw(_ballSprite);
	}

	void Ball::Update(float dt) 
	{

		if (BALL_STATE_MOVING == _ballState) {

			// rotates right
			_rotation += ROTATION_SPEED * dt;


			_ballSprite.setRotation(_rotation);
		}

		// check for when vector of movement comes to 0 the ball will stop 

	}

	void Ball::Move(float angle,sf::Vector2f speed,bool effectOnBall, int direction, float force)
	{

		if (_ballState == BALL_STATE_MOVING) {
			
			// calculation to work out the directions it moves
			float radians = 2 * PI * (angle / 360);

			if (!effectOnBall) {
				// it moves corresponding to the direction given and the slowdown of the natural terrain (will implement speed and different terrains soon)
				_ballSprite.move(speed.x * cos(radians) * _slowdown, speed.y * sin(radians) * _slowdown);
				// slows down the ball over time 
				_slowdown -= 0.01;

			}
			else {
				// force is strength of projection
				// 1 = up, 2 = down, 3 = right , 4 = left
				if (direction == 1) {
					_ballSprite.move(speed.x * cos(radians) * _slowdown, speed.y * sin(radians) * force);
				}
				else if (direction == 2) {
					_ballSprite.move(speed.x * cos(radians) * _slowdown, speed.y * sin(radians) * force);
				}
				else if (direction == 3) {
					_ballSprite.move(speed.x * cos(radians) * force, speed.y * sin(radians) * _slowdown);
				}
				else {
					_ballSprite.move(speed.x * cos(radians) * force, speed.y * sin(radians) * _slowdown);
				}
			}

		}
		

		// when the ball has stopped moving set the state to stopped
		if (_slowdown < 0.0) {
			if (_ballState != BALL_STATE_STILL) {
				_ballState = BALL_STATE_STOPPED;
			}
		}

	}


	const sf::Sprite& Ball::GetSprite() const
	{
		return _ballSprite;
	}

}