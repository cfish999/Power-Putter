#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Fish
{
	class medalScreen : public State
	{
	public:
		medalScreen(GameDataRef data, int medalLevel, int lastLevelPlayed, int shots, sf::Font font);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _homeButton;
		sf::Sprite _retry;
		sf::Sprite _medal;
		sf::Sprite _nextLevel;
		sf::Sprite _completed;
		sf::Sprite _statistics;

		int _medalLevel;
		int _lastLevelPlayed;
		int _shotsTaken = 0;
		sf::Font _font;
		sf::Text _shotsText;
		std::string _text;

	};
}