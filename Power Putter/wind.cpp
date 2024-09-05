#include "wind.h"

namespace Fish {

	Wind::Wind(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		// pushes the fan frames onto the animation frames stack
		_animationFrames.push_back(_data->assets.GetTexture("Wind Low"));
		_animationFrames.push_back(_data->assets.GetTexture("Wind High"));

		_windSprite.setTexture(_animationFrames.at(_animationIterator));

		// the position of the fan on the window
	
		_windSprite.scale(2, 2);
		_windSprite.setPosition(500, 300);

	}

	void Wind::Draw() {

		_data->window.draw(_windSprite);
	}

	void Wind::Animate(float dt)
	{

		if (_clock.getElapsedTime().asSeconds() > WIND_SPEED / _animationFrames.size()) {

			if (_animationIterator < _animationFrames.size() - 1) {

				_animationIterator++;
			}
			else {
				_animationIterator = 0;
			}

			// sets the current frame 
			_windSprite.setTexture(_animationFrames.at(_animationIterator));

			_clock.restart();
		}
	}

	const sf::Sprite& Wind::GetSprite() const
	{
		return _windSprite;
	}

}