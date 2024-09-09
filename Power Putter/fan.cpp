#include "fan.h"

namespace Fish {

	Fan::Fan(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		// pushes the fan frames onto the animation frames stack
		_animationFrames.push_back(_data->assets.GetTexture("Fan Frame 1"));
		_animationFrames.push_back(_data->assets.GetTexture("Fan Frame 2"));
		_animationFrames.push_back(_data->assets.GetTexture("Fan Frame 3"));
		_animationFrames.push_back(_data->assets.GetTexture("Fan Frame 4"));

		_fanSprite.setTexture(_animationFrames.at(_animationIterator));

	}

	void Fan::SpawnFan(int x, int y, float scaleX, float scaleY, int rotation)
	{
		sf::Sprite _fanSprite(_data->assets.GetTexture("Fan Frame 1"));

		// the position of the fan on the window 
		_fanSprite.setPosition(x, y);

		sf::Vector2f origin = sf::Vector2f(_fanSprite.getGlobalBounds().width / 2, _fanSprite.getGlobalBounds().height / 2);
		_fanSprite.setOrigin(origin);

		_fanSprite.scale(scaleX, scaleY);
		_fanSprite.rotate(rotation);

		// stores the fan sprite and its direction (used for later collisions)
		_fanSprites.push_back(_fanSprite);
		_fanDirection.push_back(rotation);


	}

	void Fan::Draw() {

		// draws all of the fans stored in the vector 
		for (unsigned short int i = 0; i < _fanSprites.size(); i++) {
			_data->window.draw(_fanSprites.at(i));
		}
	}


	void Fan::Animate(float dt)
	{
	
		if (_clock.getElapsedTime().asSeconds() > FAN_SPIN_SPEED / _animationFrames.size()) {

			if (_animationIterator < _animationFrames.size() - 1) {

				_animationIterator++;
			}
			else {
				_animationIterator = 0;
			}

			// sets the current frame 
			for (unsigned short int i = 0; i < _fanSprites.size(); i++) {
				_fanSprites.at(i).setTexture(_animationFrames.at(_animationIterator));
			}


			_clock.restart();
		}
	}

	const sf::Sprite& Fan::GetSprite() const
	{
		return _fanSprite;
	}

	const std::vector<sf::Sprite>& Fan::GetSprites() const
	{
		return _fanSprites;
	}

	const std::vector<int>& Fan::GetDirections() const
	{
		return _fanDirection;
	}

}