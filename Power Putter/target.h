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
		const sf::Sprite& GetBronzeSprite() const;
		const sf::Sprite& GetSilverSprite() const;
		const sf::Sprite& GetGoldSprite() const;
		float BronzeRadius();
		float SilverRadius();
		float GoldRadius();

	private:

		GameDataRef _data;

		sf::Sprite _goldTarget;
		sf::Sprite _silverTarget;
		sf::Sprite _bronzeTarget;

		float goldRadius;
		float silverRadius;
		float bronzeRadius;
	};
}