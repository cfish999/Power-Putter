#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Fish
{
	// inherits from state
	class LevelSelectState : public State
	{
	public:
		LevelSelectState(GameDataRef data); // constructor

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		int currentLevel = 0;

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _selectLevel;
		sf::Sprite _levelSelect;
		sf::Sprite _level1;
		sf::Sprite _level2;
		sf::Sprite _level3;
		sf::Sprite _homeButton;
	};
}