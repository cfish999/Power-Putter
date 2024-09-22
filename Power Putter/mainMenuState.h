#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Fish
{
	// inherits from state
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data); // constructor

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		int currentLevel = 0;

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _title;
		sf::Sprite _levelSelect;
		sf::Sprite _playButton;
		sf::Sprite _gameTitle;
	};
}