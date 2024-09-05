#include "squareObstacles.h"
#include "DEFINITIONS.h"
#include <iostream>

namespace Fish {
	// gets automatically assigned to the data 
	SquareObstacles::SquareObstacles(GameDataRef data) : _data(data) {


	}

	void SquareObstacles::SpawnSquare() {

		// future give it position x and y values to help construct a level
		sf::Sprite sprite(_data->assets.GetTexture("Square"));

		sprite.setPosition(200,200);

		sf::Vector2f origin = sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		sprite.setOrigin(origin);

		sprite.scale(3, 3);

		squareSprites.push_back(sprite);

		sf::Sprite sprite2(_data->assets.GetTexture("Square"));

		sprite2.setPosition(200, 700);

		sf::Vector2f origin2 = sf::Vector2f(sprite2.getGlobalBounds().width / 2, sprite2.getGlobalBounds().height / 2);
		sprite2.setOrigin(origin2);

		sprite2.scale(3, 3);

		squareSprites.push_back(sprite2);

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