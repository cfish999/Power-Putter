#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Arrow {
	public:

		Arrow(GameDataRef data);

		void Draw();
		void Update(float dt); 
		const sf::Sprite& GetSprite() const;
		float GetArrowAngle(sf::RenderWindow& window);

		int _arrowState;

	private:

		GameDataRef _data;

		sf::Sprite _arrowSprite;

		sf::Clock _clock;
		sf::Clock _movementClock;

		float _rotation;
		int _rotatingValue = 100;

	};
}