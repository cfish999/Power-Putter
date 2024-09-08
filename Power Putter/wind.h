#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Wind {
	public:

		Wind(GameDataRef data);

		void SpawnWind(int x,int y, float scaleX,float scaleY, int rotation);
		void Draw();
		void Animate(float dt);
		const std::vector<sf::Sprite>& GetSprites() const;
		const std::vector<int>& GetDirections() const;

	private:

		GameDataRef _data;

		sf::Sprite _windSprite;
		std::vector<sf::Sprite> _windSprites;
		std::vector<int> _windDirections;
		std::vector<sf::Texture> _animationFrames;

		unsigned int _animationIterator;

		sf::Clock _clock;
		sf::Clock _movementClock;

	};
}