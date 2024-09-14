#include "squareObstacles.h"
#include "DEFINITIONS.h"
#include <iostream>

namespace Fish {
	// gets automatically assigned to the data 
	SquareObstacles::SquareObstacles(GameDataRef data) : _data(data) {


	}

	void SquareObstacles::SpawnSquare(int x, int y, float scaleX, float scaleY, int type) {


		// future give it position x and y values to help construct a level
		if (type == 1) {
			sf::Sprite sprite(_data->assets.GetTexture("Wall Main"));
			sprite.setPosition(x, y);

			sf::Vector2f origin = sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
			sprite.setOrigin(origin);

			sprite.scale(scaleX, scaleY);

			squareSprites.push_back(sprite);
		}
		else {
			sf::Sprite sprite(_data->assets.GetTexture("Wall Danger"));
			sprite.setPosition(x, y);

			sf::Vector2f origin = sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
			sprite.setOrigin(origin);

			sprite.scale(scaleX, scaleY);

			squareSprites.push_back(sprite);
		}


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