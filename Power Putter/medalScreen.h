#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Fish
{
	class medalScreen : public State
	{
	public:
		medalScreen(GameDataRef data, int medalLevel, int lastLevelPlayed);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _gameOverTitle;
		sf::Sprite _homeButton;
		sf::Sprite _retry;

		int _medalLevel;
		int _lastLevelPlayed;

	};
}