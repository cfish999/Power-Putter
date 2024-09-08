#include "wind.h"

namespace Fish {

	Wind::Wind(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		// pushes the fan frames onto the animation frames stack
		_animationFrames.push_back(_data->assets.GetTexture("Wind Low"));
		_animationFrames.push_back(_data->assets.GetTexture("Wind High"));

		_windSprite.setTexture(_animationFrames.at(_animationIterator));

	}

	void Wind::SpawnWind(int x, int y, float scaleX, float scaleY, int rotation)
	{
		sf::Sprite _windSprite(_data->assets.GetTexture("Wind High"));

		// the position of the wind on the window
		_windSprite.setPosition(x, y);

		sf::Vector2f origin = sf::Vector2f(_windSprite.getGlobalBounds().width / 2, _windSprite.getGlobalBounds().height / 2);
		_windSprite.setOrigin(origin);

		_windSprite.scale(scaleX, scaleY);
		_windSprite.rotate(rotation);

		// pushes the wind sprite and its direction (used for later collisions)
		_windSprites.push_back(_windSprite);
		_windDirections.push_back(rotation);
		
	}

	void Wind::Draw() {

		for (unsigned short int i = 0; i < _windSprites.size(); i++) {

			// draws all of the wind currently stored in the vector onto the screen 
			_data->window.draw(_windSprites.at(i));
		}
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

			// animates them all at the same time 
			for (unsigned short int i = 0; i < _windSprites.size(); i++) {

				// sets the current frame 
				_windSprites.at(i).setTexture(_animationFrames.at(_animationIterator));

			}
			_clock.restart();

		}
	}

	const std::vector<sf::Sprite>& Wind::GetSprites() const
	{
		return _windSprites;
	}

	const std::vector<int>& Wind::GetDirections() const
	{
		return _windDirections;
	}

}