#include "door.h"

namespace Fish {

	Door::Door(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		// pushes the fan frames onto the animation frames stack
		_animationFrames.push_back(_data->assets.GetTexture("Closed Door"));
		_animationFrames.push_back(_data->assets.GetTexture("Opening Door"));
		_animationFrames.push_back(_data->assets.GetTexture("Open Door"));

		_doorSprite.setTexture(_animationFrames.at(_animationIterator));

		// the position of the springboard on the window 
		_doorSprite.setPosition(450,450);
		_doorSprite.setOrigin(sf::Vector2f(_doorSprite.getGlobalBounds().width / 2,
			_doorSprite.getGlobalBounds().height / 2));
		_doorSprite.rotate(90);
		_doorSprite.scale(8, 8);

		_openRightDoorSprite.setTexture(this->_data->assets.GetTexture("Right Open Door"));
		_openRightDoorSprite.setPosition(450, 450 + 130);
		_openRightDoorSprite.setOrigin(sf::Vector2f(_openRightDoorSprite.getGlobalBounds().width / 2,
			_openRightDoorSprite.getGlobalBounds().height / 2));
		_openRightDoorSprite.rotate(90);
		_openRightDoorSprite.scale(8, 8);
		// makes it invisible 
		_openRightDoorSprite.setColor(sf::Color(0, 0, 0));

		_openLeftDoorSprite.setTexture(this->_data->assets.GetTexture("Left Open Door"));
		_openLeftDoorSprite.setPosition(450, 450 - 130);
		_openLeftDoorSprite.setOrigin(sf::Vector2f(_openLeftDoorSprite.getGlobalBounds().width / 2,
			_openLeftDoorSprite.getGlobalBounds().height / 2));
		_openLeftDoorSprite.rotate(90);
		_openLeftDoorSprite.scale(8, 8);
		// makes it invisible 
		_openLeftDoorSprite.setColor(sf::Color(0, 0, 0));

	}

	void Door::Draw() {

		_data->window.draw(_doorSprite);
	}

	void Door::Animate(float dt)
	{
		// door opens or closes every 4 seconds 
		if (_doorOpeningClock.getElapsedTime().asSeconds() > DOOR_TIMER) {

			if (_clock.getElapsedTime().asSeconds() > DOOR_ANIMATION / _animationFrames.size()) {

				if (!_reverse) {
					if (_animationIterator == 2) {

						_reverse = true;
						// only resets when all animations have been completed
						_doorOpeningClock.restart();
					}
					else {
						_animationIterator++;
					}
				}
				else {
					if (_animationIterator == 0) {

						_reverse = false;
						// only resets when all animations have been completed
						_doorOpeningClock.restart();
					}
					else {
						_animationIterator--;
					}
				}

				// sets the current frame 
				_doorSprite.setPosition(450, 450);
				_doorSprite.setTexture(_animationFrames.at(_animationIterator));

				_clock.restart();

			}
		}
	}

	const sf::Sprite& Door::GetDoorSprite() const
	{
		return _doorSprite;
	}

	const sf::Sprite& Door::GetRightOpenDoor() const
	{
		return _openRightDoorSprite;
	}

	const sf::Sprite& Door::GetLeftOpenDoor() const
	{
		return _openLeftDoorSprite;
	}

	

}