#include "springboard.h"

namespace Fish {

	Springboard::Springboard(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		// pushes the fan frames onto the animation frames stack
		_animationFrames.push_back(_data->assets.GetTexture("Springboard Low"));
		_animationFrames.push_back(_data->assets.GetTexture("Springboard Medium"));
		_animationFrames.push_back(_data->assets.GetTexture("Springboard High"));

		_springboardSprite.setTexture(_animationFrames.at(_animationIterator));

		// the position of the springboard on the window 
		_springboardSprite.setPosition(100, 500);
		_springboardSprite.setOrigin(sf::Vector2f(_springboardSprite.getGlobalBounds().width / 2,
			_springboardSprite.getGlobalBounds().height / 2));
		_springboardSprite.rotate(90);
		_springboardSprite.scale(3, 3);


		_collisionLowSprite.setTexture(this->_data->assets.GetTexture("Low Springboard Collision"));
		_collisionLowSprite.setPosition(100, 500);
		_collisionLowSprite.setOrigin(sf::Vector2f(_collisionLowSprite.getGlobalBounds().width / 2,
			_collisionLowSprite.getGlobalBounds().height / 2));
		_collisionLowSprite.rotate(90);
		_collisionLowSprite.scale(3, 3);
		// makes it invisible 
		_collisionLowSprite.setColor(sf::Color(0, 0, 0));

		_collisionMediumSprite.setTexture(this->_data->assets.GetTexture("Medium Springboard Collision"));
		_collisionMediumSprite.setPosition(100, 500);
		_collisionMediumSprite.setOrigin(sf::Vector2f(_collisionMediumSprite.getGlobalBounds().width / 2,
			_collisionMediumSprite.getGlobalBounds().height / 2));
		_collisionMediumSprite.rotate(90);
		_collisionMediumSprite.scale(3, 3);
		// makes it invisible 
		_collisionMediumSprite.setColor(sf::Color(0, 0, 0));

		_collisionLargeSprite.setTexture(this->_data->assets.GetTexture("Springboard High"));
		_collisionLargeSprite.setPosition(100, 500);
		_collisionLargeSprite.setOrigin(sf::Vector2f(_collisionLargeSprite.getGlobalBounds().width / 2,
			_collisionLargeSprite.getGlobalBounds().height / 2));
		_collisionLargeSprite.rotate(90);
		_collisionLargeSprite.scale(3, 3);
		// makes it invisible 
		_collisionLargeSprite.setColor(sf::Color(0, 0, 0));

	}

	void Springboard::Draw() {

		_data->window.draw(_springboardSprite);
	}

	void Springboard::Animate(float dt)
	{
		// springs every 3 seconds 
		if (_springingClock.getElapsedTime().asSeconds() > SPRINGBOARD_MOVE) {

			if (_clock.getElapsedTime().asSeconds() > SPRINGBOARD_ANIMATION / _animationFrames.size()) {

				if (_animationIterator < _animationFrames.size() - 1) {

					_animationIterator++;
				}
				else {
					_animationIterator = 0;
				}

				// sets the current frame 
				_springboardSprite.setPosition(100, 500);
				_springboardSprite.setTexture(_animationFrames.at(_animationIterator));

				_clock.restart();

				// only resets when all animations have been completed
				if (_animationIterator == 0) {
					_springingClock.restart();
				}
			}
		}
	}

	const sf::Sprite& Springboard::GetSmallSprite() const
	{
		return _collisionLowSprite;
	}

	const sf::Sprite& Springboard::GetMediumSprite() const
	{
		return _collisionMediumSprite;
	}

	const sf::Sprite& Springboard::GetLargeSprite() const
	{
		return _collisionLargeSprite;
	}

}