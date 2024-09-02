#include "ball.h"
#include <iostream>

namespace Fish {

	Ball::Ball(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		_animationFrames.push_back(_data->assets.GetTexture("Ball Sprite"));

		_ballSprite.setTexture(_animationFrames.at(_animationIterator));

		_ballSprite.setPosition((_data->window.getSize().x / 4) - (_ballSprite.getGlobalBounds().width / 2),
			(_data->window.getSize().y / 2) - (_ballSprite.getGlobalBounds().height / 2));

		_ballState = BALL_STATE_STILL;

		// rotates around the centre of the object which is this 
		sf::Vector2f origin = sf::Vector2f(_ballSprite.getGlobalBounds().width / 2, _ballSprite.getGlobalBounds().height / 2);
		_ballSprite.setOrigin(origin);

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

	void Ball::Move(float speed)
	{

		if (_ballState == BALL_STATE_MOVING) {

			// move corresponding to the speed given and the slowdown of the natural terrain 
			_ballSprite.move(0.5 * speed * _slowdown, 0);
			// slows down the ball over time 
			_slowdown -= 0.01;
		}
		else {
			// when it is no longer in the moving state the slowdown state gets reset 
			_slowdown = 1.0;
		}

		// when the ball has stopped moving set the state to still 
		if (_slowdown < 0.0) {
			_ballState = BALL_STATE_STILL;
			
		}

	}


	const sf::Sprite& Ball::GetSprite() const
	{
		return _ballSprite;
	}

}