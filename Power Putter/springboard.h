#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Springboard {
	public:

		Springboard(GameDataRef data);

		void Draw();
		void Animate(float dt);
		int SpringboardHeight();
		const sf::Sprite& GetSmallSprite() const;
		const sf::Sprite& GetMediumSprite() const;
		const sf::Sprite& GetLargeSprite() const;

		unsigned int _animationIterator;

	private:

		GameDataRef _data;

		sf::Sprite _springboardSprite;
		sf::Sprite _collisionLowSprite;
		sf::Sprite _collisionMediumSprite;
		sf::Sprite _collisionLargeSprite;
		std::vector<sf::Texture> _animationFrames;

		bool _animation = true;

		sf::Clock _clock;
		sf::Clock _springingClock;

	};
}