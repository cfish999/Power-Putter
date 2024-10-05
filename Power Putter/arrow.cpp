#include "arrow.h"
#include "ball.h"
#include <iostream>

namespace Fish {

	Arrow::Arrow(GameDataRef data) : _data(data) {

		// sets the arrow texture
		_arrowSprite.setTexture(this->_data->assets.GetTexture("Arrow Sprite"));

	}

	void Arrow::SpawnArrow(int x,int y,float scaleX, float scaleY)
	{
		// starting position of the arrow
		_arrowSprite.setPosition(x,y);

		// rotates around the centre of the object which enables rotation around the ball
		sf::Vector2f origin = sf::Vector2f(_arrowSprite.getGlobalBounds().width / 2 - 40, _arrowSprite.getGlobalBounds().height / 2 );
		_arrowSprite.setOrigin(origin);

		// scales the sprite up
		_arrowSprite.scale(scaleX, scaleY);

		_rotation = 0;
		_arrowState = ROTATING;
	}

	void Arrow::Draw() {

		// arrow disappears once the ball has been shot 
		if (SHOT != _arrowState) {
			_data->window.draw(_arrowSprite);
		}
	}


	void Arrow::Update(float dt) {

		if (ROTATING == _arrowState) {
			
			// spins 360 degrees
			_rotation += _rotatingValue * dt;
			

			_arrowSprite.setRotation(_rotation);
		}		


		
	}

	void Arrow::MoveToBall(sf::Sprite ball)
	{
		// sets the position of the arrow as the origin of the ball
		_arrowSprite.setPosition(ball.getPosition().x, ball.getPosition().y);
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