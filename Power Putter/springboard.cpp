#include "springboard.h"

namespace Fish {

	Springboard::Springboard(GameDataRef data) : _data(data) {

		_animationIterator = 0;

		// pushes the springboard frames onto the animation frames stack
		_animationFrames.push_back(_data->assets.GetTexture("Springboard Low"));
		_animationFrames.push_back(_data->assets.GetTexture("Springboard Medium"));
		_animationFrames.push_back(_data->assets.GetTexture("Springboard High"));

		_springboardSprite.setTexture(_animationFrames.at(_animationIterator));

	}

	void Springboard::SpawnSpringboard(int x, int y, float scaleX, float scaleY, int rotation)
	{
		sf::Sprite _springboardSprite(_data->assets.GetTexture("Springboard Low"));

		// the position of the wind on the window
		_springboardSprite.setPosition(x, y);

		sf::Vector2f origin = sf::Vector2f(_springboardSprite.getGlobalBounds().width / 2, _springboardSprite.getGlobalBounds().height / 2);
		_springboardSprite.setOrigin(origin);

		_springboardSprite.scale(scaleX, scaleY);
		_springboardSprite.rotate(rotation);

		// pushes the springboard sprite and its direction (used for later collisions)
		_springboardSprites.push_back(_springboardSprite);
		_springboardDirections.push_back(rotation);

	}

	void Springboard::Draw() {

		for (unsigned short int i = 0; i < _springboardSprites.size(); i++) {
			// draws all of the springboards currently stored in the vector onto the screen 
			_data->window.draw(_springboardSprites.at(i));
		}
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

				// animates them all at the same time 
				for (unsigned short int i = 0; i < _springboardSprites.size(); i++) {
					// sets the current frame 
					_springboardSprites.at(i).setTexture(_animationFrames.at(_animationIterator));
				}

				_clock.restart();

				// only resets when all animations have been completed
				if (_animationIterator == 0) {
					_springingClock.restart();
				}
			}
		}
	}

	const std::vector<sf::Sprite>& Springboard::GetSprites() const
	{
		return _springboardSprites;
	}

	const std::vector<int>& Springboard::GetDirections() const
	{
		return _springboardDirections;
	}

}