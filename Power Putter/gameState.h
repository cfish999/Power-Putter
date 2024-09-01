#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "game.h"

namespace Fish
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;

		int _gameState;
	};
}