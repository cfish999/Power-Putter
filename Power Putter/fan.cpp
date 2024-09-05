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

		// the position of the fan on the window 
		_fanSprite.setPosition(800, 800);
		_fanSprite.scale(2, 2);

	}

	void Fan::Draw() {

		_data->window.draw(_fanSprite);
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
			_fanSprite.setTexture(_animationFrames.at(_animationIterator));

			_clock.restart();
		}
	}

	const sf::Sprite& Fan::GetSprite() const
	{
		return _fanSprite;
	}

}