#include "power_bar.h"
#include <iostream>

namespace Fish {

	PowerBar::PowerBar(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		// pushes the power bar frames onto the animation frames stack
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 1"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 2"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 3"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 4"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 5"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 6"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 7"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 8"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 9"));
		_animationFrames.push_back(_data->assets.GetTexture("Power Bar 10"));

		_powerBarSprite.setTexture(_animationFrames.at(_animationIterator));

		// the position of the power bar on the window 
		_powerBarSprite.setPosition(0, 700);

	}

	void PowerBar::Draw() {

		_data->window.draw(_powerBarSprite);
	}

	void PowerBar::Animate(float dt) 
	{
		// ball has been shot so we no longer need the animation
		if(powerBarNeeded) {

			if (_clock.getElapsedTime().asSeconds() > POWER_BAR_DURATION / _animationFrames.size()) {

				// increases the animation frames up to the max amount and then when it is reached the frames go back down to look like a power bar
				if (_animationIterator == _animationFrames.size() - 1) {

					rising = false;
				}
				else if (_animationIterator == 0) {

					rising = true;
				}

				if (rising) {
					_animationIterator++;
				}
				else {
					_animationIterator--;
				}

				// sets the current frame 
				_powerBarSprite.setTexture(_animationFrames.at(_animationIterator));

				_clock.restart();
			}
		}
	}

	float PowerBar::GetSpeed()
	{
		// sets the power bar needed to false to stop the animation occurring 
		powerBarNeeded = false;
		float differential = rand() % 100;
		// prevents division by 0 errors
		float addition = (differential+1) / 100;

		return (_animationIterator +1 + addition);

	}


	const sf::Sprite& PowerBar::GetSprite() const
	{
		return _powerBarSprite;
	}

}