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
#include "fan.h"
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
		this->_data->assets.LoadTexture("Fan Frame 1", FAN_1);
		this->_data->assets.LoadTexture("Fan Frame 2", FAN_2);
		this->_data->assets.LoadTexture("Fan Frame 3", FAN_3);
		this->_data->assets.LoadTexture("Fan Frame 4", FAN_4);
		this->_data->assets.LoadTexture("Wind Low", WIND_LOW);
		this->_data->assets.LoadTexture("Wind High", WIND_HIGH);
		this->_data->assets.LoadTexture("Springboard Low", SPRINGBOARD_LOW);
		this->_data->assets.LoadTexture("Springboard Medium", SPRINGBOARD_MED);
		this->_data->assets.LoadTexture("Springboard High", SPRINGBOARD_HIGH);
		this->_data->assets.LoadTexture("Low Springboard Collision", SPRINGBOARD_COLLISION_LOW);
		this->_data->assets.LoadTexture("Medium Springboard Collision", SPRINGBOARD_COLLISION_MEDIUM);
		this->_data->assets.LoadTexture("Closed Door", DOOR_CLOSED);
		this->_data->assets.LoadTexture("Opening Door", DOOR_OPENING);
		this->_data->assets.LoadTexture("Open Door", DOOR_OPEN);
		this->_data->assets.LoadTexture("Left Open Door", LEFT_OPEN_DOOR);
		this->_data->assets.LoadTexture("Right Open Door", RIGHT_OPEN_DOOR);
		
		ball = new Ball(_data);
		arrow = new Arrow(_data);
		powerBar = new PowerBar(_data);
		targets = new Target(_data);
		squareObstacles = new SquareObstacles(_data);
		fan = new Fan(_data);
		wind = new Wind(_data);
		springboard = new Springboard(_data);
		door = new Door(_data);

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
		fan->Animate(dt);
		wind->Animate(dt);
		springboard->Animate(dt);
		door->Animate(dt);

		// moves the ball only when direction and power bar strength has been set
		if (arrow->_arrowState == SHOT) {

			// check whether it bounces off the square obstacles
			for (unsigned short int i = 0; i < squareSprites.size(); i++) {  
				// checks the ball has not collided with any of the square obstacles
				_squareCollision = collision.CheckBallAndSquareCollision(ball->GetSprite(), squareSprites.at(i));

				if(_squareCollision == 1) {
					// bounces in y-axis
					powerBarSpeeds.y *= -1;
					ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall,0,0);
					ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall,0,0);
				}
				else if(_squareCollision == 2) {
					// _squaresCollision is 2 so bounces in x-axis
					powerBarSpeeds.x *= -1;
					ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall,0,0);
					ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall,0,0);
				}

			}

			// blows the ball upwards 
			if (collision.CheckBallAndWindCollision(ball->GetSprite(), wind->GetSprite())) {
				_effectOnBall = true;
				ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall,1,10);
				_effectOnBall = false;
			}

			// checks for springboard collisions
			_springSize = springboard->_animationIterator;

			// medium setting so springs off
			if (_springSize == 1) {
				_springboardCollided = collision.CheckBallAndSpringSideCollision(ball->GetSprite(), springboard->GetMediumSprite());
			}
			// large setting so springs off
			else if(_springSize == 2){
				_springboardCollided = collision.CheckBallAndSpringSideCollision(ball->GetSprite(), springboard->GetLargeSprite());
			}

			if (_springboardCollided) {
				// bounces off whatever axis it is facing and a set speed
				_effectOnBall = true;
				// sort out the springboard speeds
				ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall, 3, 25);
				_effectOnBall = false;
			}

			// smallest spring setting so no bounce just reflect 
			_rectangleCollision = collision.CheckBallAndRectangleCollision(ball->GetSprite(), springboard->GetSmallSprite());
			if (_rectangleCollision == 1) {
				// bounces in y-axis
				Movement(_rectangleCollision);
			}
			else if (_rectangleCollision == 2) {
				// bounces in x-axis
				Movement(_rectangleCollision);
			}

			_doorState = door->_animationIterator;
			if (_doorState == 0 || _doorState == 1) {
				_rectangleCollision = collision.CheckBallAndRectangleCollision(ball->GetSprite(), door->GetDoorSprite());
				if (_rectangleCollision > 0) {
					Movement(_rectangleCollision);
				}
			}
			else {
				_rectangleCollision = collision.CheckBallAndRectangleCollision(ball->GetSprite(), door->GetLeftOpenDoor());

				if (_rectangleCollision > 0) {
					Movement(_rectangleCollision);
				}

				_rectangleCollision = collision.CheckBallAndRectangleCollision(ball->GetSprite(), door->GetRightOpenDoor());

				if (_rectangleCollision > 0) {
					Movement(_rectangleCollision);
				}
			}
			

			// moves the ball in the direction it was aimed
			ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall, 0, 0);

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
				ball->_ballState = BALL_STATE_STILL;
				Init();
			}
		}

	}

	void GameState::Movement(int axisAffected)
	{
		if (axisAffected == 1) {
			// bounces in y-axis
			powerBarSpeeds.y *= -1;
			ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall, 0, 0);
			ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall, 0, 0);
		}
		else {
			// bounces in x-axis
			powerBarSpeeds.x *= -1;
			ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall, 0, 0);
			ball->Move(arrowAngle, powerBarSpeeds, _effectOnBall, 0, 0);
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
		fan->Draw();
		wind->Draw();
		springboard->Draw();
		door->Draw();

		this->_data->window.display();
	}
}
