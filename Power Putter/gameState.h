#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "ball.h"
#include "arrow.h"
#include "power_bar.h"
#include "target.h"
#include "collision.h"
#include "medalScreen.h"
#include "squareObstacles.h"
#include "fan.h"
#include "wind.h"
#include "springboard.h"
#include "door.h"
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
		void Movement(int axisAffected);
		void SetPositionOfComponents();
		void LoadTextures();

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
		sf::Vector2f powerBarSpeeds;
		// pointer to target objects
		Target* targets;
		// pointer to square objects
		SquareObstacles* squareObstacles;
		std::vector<sf::Sprite> squareSprites;
		// pointer to fan object
		Fan* fan;
		// pointer to wind object
		Wind* wind;
		std::vector<sf::Sprite> windSprites;
		std::vector<int> windDirections;
		// pointer to springboard object
		Springboard* springboard;
		std::vector<sf::Sprite> springboardSprites;
		std::vector<int> springboardDirections;
		// pointer to door object
		Door* door;
		std::vector<sf::Sprite> doorSprites;
		std::vector<sf::Sprite> rightDoorSprites;
		std::vector<sf::Sprite> leftDoorSprites;
		std::vector<int> doorDirections;


		Collision collision;

		int _gameState;
		int _defaultSpeed = 10;
		int _medalTier = 0;
		int _attempts = 3;
		int _squareCollision = 0;
		bool _springboardCollided = false;
		int _springSize = 0;
		int _rectangleCollision = 0;
		int _directionalWind = 0;
		int _doorState = 0;
		float fan_strength = 0;
		bool _effectOnBall = false;
		bool firstClick = true;
	};
}