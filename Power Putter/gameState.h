#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "ball.h"
#include "arrow.h"
#include "power_bar.h"
#include "target.h"
#include "collision.h"
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

		// pointer to a ball object
		Ball* ball;
		// pointer to arrow object
		Arrow* arrow;
		float arrowAngle;
		// pointer to power bar object
		PowerBar* powerBar;
		float powerBarSpeed;
		// pointer to target objects
		Target* targets;
		
		Collision collision;

		int _gameState;
		int _defaultSpeed = 10;
		bool firstClick = true;
	};
}