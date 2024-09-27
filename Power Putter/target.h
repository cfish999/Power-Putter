#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Target {
	public:

		Target(GameDataRef data);

		void SpawnTarget(int x, int y, float scaleX, float scaleY);
		void Draw();
		const sf::Sprite& GetTargetSprite() const;
		float TargetRadius();

	private:

		GameDataRef _data;

		sf::Sprite _target;

		float targetRadius;
	};
}