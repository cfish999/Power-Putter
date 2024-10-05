#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Arrow {
	public:

		Arrow(GameDataRef data);

		void SpawnArrow(int x, int y, float scaleX, float scaleY);
		void Draw();
		void Update(float dt); 
		void MoveToBall(sf::Sprite ball);
		const sf::Sprite& GetSprite() const;
		float GetArrowAngle(sf::RenderWindow& window);

		int _arrowState;

	private:

		GameDataRef _data;

		sf::Sprite _arrowSprite;

		float _rotation;
		int _rotatingValue = 100;

	};
}