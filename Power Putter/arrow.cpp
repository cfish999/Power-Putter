#include "arrow.h"
#include "ball.h"
#include <iostream>

namespace Fish {

	Arrow::Arrow(GameDataRef data) : _data(data) {

		// set the texture
		_arrowSprite.setTexture(this->_data->assets.GetTexture("Arrow Sprite"));

		// starting position of arrow
		_arrowSprite.setPosition((_data->window.getSize().x / 4) - (_arrowSprite.getGlobalBounds().width / 2) + 110,
			(_data->window.getSize().y / 2) - (_arrowSprite.getGlobalBounds().height / 2) - 40 );

		// scales the sprite up
		_arrowSprite.scale(1.5, 1.5);

		// rotates around the centre of the object which is this 
		sf::Vector2f origin = sf::Vector2f(_arrowSprite.getGlobalBounds().width / 2, _arrowSprite.getGlobalBounds().height / 2);
		_arrowSprite.setOrigin(origin);

		_rotation = 0;
		_arrowState = ROTATING;
	}

	void Arrow::Draw() {

		// arrow disappears once the ball has been shot 
		if (ROTATING == _arrowState) {
			_data->window.draw(_arrowSprite);
		}
	}


	void Arrow::Update(float dt) {

		if (ROTATING == _arrowState) {
			
			_rotation += _rotatingValue * dt;

			// only want to spin 90 degrees each way 
			if (_rotation > 90.0f) {

				_rotatingValue *= -1;
			}
			else if (_rotation < -90.0f) {

				_rotatingValue *= -1;
			}

			_arrowSprite.setRotation(_rotation);
		}		
		
	}

	const sf::Sprite& Arrow::GetSprite() const
	{
		return _arrowSprite;
	}

	float Arrow::GetArrowAngle(sf::RenderWindow& window)
	{
		// gets the angle of the arrow
		return _rotation;
	}

}