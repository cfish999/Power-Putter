#include "squareObstacles.h"
#include "DEFINITIONS.h"
#include <iostream>

namespace Fish {
	// gets automatically assigned to the data 
	SquareObstacles::SquareObstacles(GameDataRef data) : _data(data) {


	}

	void SquareObstacles::SpawnSquare(int x, int y, int scaleX, int scaleY) {

		// future give it position x and y values to help construct a level
		sf::Sprite sprite(_data->assets.GetTexture("Square"));

		sprite.setPosition(x,y);

		sf::Vector2f origin = sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		sprite.setOrigin(origin);

		sprite.scale(scaleX, scaleY);

		squareSprites.push_back(sprite);

	}

	void SquareObstacles::DrawSquares() {
		for (unsigned short int i = 0; i < squareSprites.size(); i++) {

			// draws all of the squares currently stored in the vector onto the screen 
			_data->window.draw(squareSprites.at(i));
		}
	}

	const std::vector<sf::Sprite>& SquareObstacles::GetSprites() const {

		return squareSprites;
	}

}