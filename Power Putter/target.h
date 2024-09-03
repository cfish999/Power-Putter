#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "game.h"

namespace Fish {

	class Target {
	public:

		Target(GameDataRef data);

		void Draw();
		const sf::Sprite& GetBronzeSprite() const;
		const sf::Sprite& GetSilverSprite() const;
		const sf::Sprite& GetGoldSprite() const;

	private:

		GameDataRef _data;

		sf::Sprite _goldTarget;
		sf::Sprite _silverTarget;
		sf::Sprite _bronzeTarget;
	};
}