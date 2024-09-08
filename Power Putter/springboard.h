#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Springboard {
	public:

		Springboard(GameDataRef data);

		void SpawnSpringboard(int x, int y, float scaleX, float scaleY, int rotation);
		void Draw();
		void Animate(float dt);
		const std::vector<sf::Sprite>& GetSprites() const;
		const std::vector<int>& GetDirections() const;
		const sf::Sprite& GetSmallSprite() const;
		const sf::Sprite& GetMediumSprite() const;

		unsigned int _animationIterator;

	private:

		GameDataRef _data;

		sf::Sprite _springboardSprite;
		std::vector<sf::Sprite> _springboardSprites;
		std::vector<int> _springboardDirections;
		std::vector<sf::Texture> _animationFrames;
		sf::Sprite _collisionLowSprite;
		sf::Sprite _collisionMediumSprite;



		bool _animation = true;

		sf::Clock _clock;
		sf::Clock _springingClock;

	};
}