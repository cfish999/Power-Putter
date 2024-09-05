#include <sstream>
#include "gameState.h"
#include "mainMenuState.h"
#include "ball.h"
#include "arrow.h"
#include "power_bar.h"
#include "target.h"
#include "collision.h"
#include "medalScreen.h"
#include "squareObstacles.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace Fish
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init()
	{
		
		this->_data->assets.LoadTexture("Ball Sprite", BALL_FRAME_FILEPATH);
		this->_data->assets.LoadTexture("Arrow Sprite", ARROW_FILEPATH);
		this->_data->assets.LoadTexture("Power Bar 1", POWER_BAR_FRAME1);
		this->_data->assets.LoadTexture("Power Bar 2", POWER_BAR_FRAME2);
		this->_data->assets.LoadTexture("Power Bar 3", POWER_BAR_FRAME3);
		this->_data->assets.LoadTexture("Power Bar 4", POWER_BAR_FRAME4);
		this->_data->assets.LoadTexture("Power Bar 5", POWER_BAR_FRAME5);
		this->_data->assets.LoadTexture("Power Bar 6", POWER_BAR_FRAME6);
		this->_data->assets.LoadTexture("Power Bar 7", POWER_BAR_FRAME7);
		this->_data->assets.LoadTexture("Power Bar 8", POWER_BAR_FRAME8);
		this->_data->assets.LoadTexture("Power Bar 9", POWER_BAR_FRAME9);
		this->_data->assets.LoadTexture("Power Bar 10", POWER_BAR_FRAME10);
		this->_data->assets.LoadTexture("Gold Target", GOLD_TARGET);
		this->_data->assets.LoadTexture("Silver Target", SILVER_TARGET);
		this->_data->assets.LoadTexture("Bronze Target", BRONZE_TARGET);
		this->_data->assets.LoadTexture("Square", SQUARE_OBSTACLE);
		
		ball = new Ball(_data);
		arrow = new Arrow(_data);
		powerBar = new PowerBar(_data);
		targets = new Target(_data);
		squareObstacles = new SquareObstacles(_data);

		// spawns 1 square
		squareObstacles->SpawnSquare();
		// stores a vector of sprites that are squares
		squareSprites = squareObstacles->GetSprites();

		// at the minute we are reusing the background asset as we have not created a game screen background yet 
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));

	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			// check when the background has been clicked 
			if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window)) {

				// first click sets the direction of the ball
				if (firstClick) {
					arrow->_arrowState = NOT_ROTATING;
					arrowAngle = arrow->GetArrowAngle(_data->window);
					firstClick = false;
			}	// second sets the speed of the ball
				else {
					arrow->_arrowState = SHOT;
					ball->_ballState = BALL_STATE_MOVING;
					powerBarSpeed = powerBar->GetSpeed();
					// allows us to do the bouncing calculation easily 
					sf::Vector2f powerBarVelocity (powerBarSpeed, powerBarSpeed);
					powerBarSpeeds = powerBarVelocity;
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		ball->Update(dt);
		arrow->Update(dt);
		powerBar->Animate(dt);

		// moves the ball only when direction and power bar strength has been set
		if (arrow->_arrowState == SHOT) {

			for (unsigned short int i = 0; i < squareSprites.size(); i++) {
				// checks the ball has not collided with any of the square obstacles
				_squareCollision = collision.CheckBallAndSquareCollision(ball->GetSprite(), squareSprites.at(i));
				std::cout << _squareCollision << std::endl;

				if (_squareCollision == 0) {
					// moves without bouncing 
					ball->Move(arrowAngle, powerBarSpeeds);
				}
				else if(_squareCollision == 1) {
					// bounces in y-axis
					powerBarSpeeds.y *= -1;
					ball->Move(arrowAngle, powerBarSpeeds);
					ball->Move(arrowAngle, powerBarSpeeds);
				}
				else {
					// _squaresCollision is 2 so bounces in x-axis
					powerBarSpeeds.x *= -1;
					ball->Move(arrowAngle, powerBarSpeeds);
					ball->Move(arrowAngle, powerBarSpeeds);
				}

			}
		}

		if (ball->_ballState == BALL_STATE_STOPPED) {
			
			// must be ball then target for sprites to work for collision
			// the following sets the players best medal out of their 3 tries
			if (collision.CheckTargetAndBallCollision(ball->GetSprite(), targets->GetGoldSprite())) {
				std::cout << "gold medal" << std::endl;
				_medalTier = 3;
				// straight to the next level if gold medal is achieved first or second try
				_data->machine.AddState(StateRef(new medalScreen(_data, _medalTier)), true);
			}
			else if (collision.CheckTargetAndBallCollision(ball->GetSprite(), targets->GetSilverSprite())) {
				std::cout << "silver medal" << std::endl;
				if (_medalTier < 2) {
					_medalTier = 2;
				}
			}
			else if (collision.CheckTargetAndBallCollision(ball->GetSprite(), targets->GetBronzeSprite())) {
				std::cout << "bronze medal" << std::endl;
				if (_medalTier < 1) {
					_medalTier = 1;
				}
			}
			else {
				if (collision.CheckBoundAreaAndBallCollision(ball->GetSprite(), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))) {
					std::cout << "missed" << std::endl;
				}
				else {
					std::cout << "out of bounds" << std::endl;
				}
			}

			// makes the player have one less attempt as they have just used one
			_attempts--;
			
			// when all attempts have been used up go to the medal screen 
			if (_attempts == 0) {
				_data->machine.AddState(StateRef(new medalScreen(_data, _medalTier)), true);
			}
			else {
				// resets the screen for future attempts 
				firstClick = true;
				Init();
			}
		}

	}

	void GameState::Draw(float dt)
	{
		// draws all the level contents to the screen 
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		targets->Draw();
		arrow->Draw();
		ball->Draw();
		powerBar->Draw();
		squareObstacles->DrawSquares();

		this->_data->window.display();
	}
}
