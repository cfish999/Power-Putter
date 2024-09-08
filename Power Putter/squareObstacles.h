#pragma once

#include <SFML/Graphics.hpp>
// passing in data objects to access stuff like the window
#include "game.h"
// stores our sprites in a vector
#include <vector>

namespace Fish {

	class SquareObstacles {

	public:

		SquareObstacles(GameDataRef data);
		void SpawnSquare(int x,int y,int scaleX, int scaleY);
		void DrawSquares();
		const std::vector<sf::Sprite>& GetSprites() const;


	private:

		GameDataRef _data;
		std::vector<sf::Sprite> squareSprites;
	};

}