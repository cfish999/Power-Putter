#include "door.h"
#include <iostream>

namespace Fish {

	Door::Door(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		// pushes the door frames onto the animation frames stack
		_animationFrames.push_back(_data->assets.GetTexture("Closed Door"));
		_animationFrames.push_back(_data->assets.GetTexture("Opening Door"));
		_animationFrames.push_back(_data->assets.GetTexture("Open Door"));

		_doorSprite.setTexture(_animationFrames.at(_animationIterator));

	}

	void Door::spawnDoor(int x, int y, float scaleX, float scaleY, int rotation)
	{
		// sets the door texture
		sf::Sprite _doorSprite(_data->assets.GetTexture("Closed Door"));

		// the position of the door on the window and its origin
		_doorSprite.setPosition(x, y);
		_doorSprite.setOrigin(sf::Vector2f(_doorSprite.getGlobalBounds().width / 2,
			_doorSprite.getGlobalBounds().height / 2));
		_doorSprite.scale(scaleX, scaleY);
		_doorSprite.rotate(rotation);

		// adds the door sprites onto the door stack 
		_doorSprites.push_back(_doorSprite);
		_doorDirections.push_back(rotation);

		RightAndLeftDoorInstantiation(x,y,scaleX,scaleY,rotation);
		
	}

	void Door::Draw() {

		for (unsigned short int i = 0; i < _doorSprites.size(); i++) {
			_data->window.draw(_doorSprites.at(i));
			// to resize for when I make it an 8x8 grid
			// _data->window.draw(_doorLeftSprites.at(i));
			// _data->window.draw(_doorRightSprites.at(i));
		}
	}

	void Door::Animate(float dt)
	{
		// door opens or closes every 4 seconds 
		if (_doorOpeningClock.getElapsedTime().asSeconds() > DOOR_TIMER) {

			// door animation code 
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

				// animates them all at the same time 
				for (unsigned short int i = 0; i < _doorSprites.size(); i++) {
					// sets the current frame
					_doorSprites.at(i).setTexture(_animationFrames.at(_animationIterator));
				}
				_clock.restart();
			}
		}
	}

	void Door::RightAndLeftDoorInstantiation(int x, int y, float scaleX, float scaleY,int rotation)
	{
		// creates the right door sprite 
		sf::Sprite _openRightDoorSprite(_data->assets.GetTexture("Right Open Door"));
		if (rotation == 0) {
			_openRightDoorSprite.setPosition(x + 105, y);
		}
		else if (rotation == 90) {
			_openRightDoorSprite.setPosition(x, y + 105);
		}
		else if (rotation == 180) {
			_openRightDoorSprite.setPosition(x - 105, y);
		}
		else {
			_openRightDoorSprite.setPosition(x, y - 105);
		}

		// sets the origin,scale and position
		_openRightDoorSprite.setOrigin(sf::Vector2f(_openRightDoorSprite.getGlobalBounds().width / 2,
			_openRightDoorSprite.getGlobalBounds().height / 2));
		_openRightDoorSprite.scale(scaleX, scaleY);
		_openRightDoorSprite.rotate(rotation);
		// makes it invisible 
		_openRightDoorSprite.setColor(sf::Color(0, 0, 0));

		// add to the right door sprite stack
		_doorRightSprites.push_back(_openRightDoorSprite);

		// creates the left door sprite 
		sf::Sprite _openLeftDoorSprite(_data->assets.GetTexture("Left Open Door"));
		if (rotation == 0) {
			_openLeftDoorSprite.setPosition(x - 105, y);
		}
		else if (rotation == 90) {
			_openLeftDoorSprite.setPosition(x, y - 105);
		}
		else if (rotation == 180) {
			_openLeftDoorSprite.setPosition(x + 105, y);
		}
		else {
			_openLeftDoorSprite.setPosition(x, y + 105);
		}

		// sets the origin,scale and position
		_openLeftDoorSprite.setOrigin(sf::Vector2f(_openLeftDoorSprite.getGlobalBounds().width / 2,
			_openLeftDoorSprite.getGlobalBounds().height / 2));
		_openLeftDoorSprite.scale(scaleX, scaleY);
		_openLeftDoorSprite.rotate(rotation);
		// makes it invisible 
		_openLeftDoorSprite.setColor(sf::Color(0, 0, 0));

		// add to the left door sprite stack
		_doorLeftSprites.push_back(_openLeftDoorSprite);

	}

	const std::vector<sf::Sprite>& Door::GetSprites() const
	{
		return _doorSprites;
	}

	const std::vector<sf::Sprite>& Door::GetRightOpenDoors() const
	{
		return _doorRightSprites;
	}

	const std::vector<sf::Sprite>& Door::GetLeftOpenDoors() const
	{
		return _doorLeftSprites;
	}

	const std::vector<int>& Door::GetDirections() const
	{
		return _doorDirections;
	}

}