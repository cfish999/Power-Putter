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
		
		LoadTextures();

		ball = new Ball(_data);
		arrow = new Arrow(_data);
		powerBar = new PowerBar(_data);
		targets = new Target(_data);
		squareObstacles = new SquareObstacles(_data);
		fan = new Fan(_data);
		wind = new Wind(_data);
		springboard = new Springboard(_data);
		door = new Door(_data);

		SetPositionOfComponents();

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

				if (_squareCollision == 1) {
					// bounces in y-axis
					Movement(_squareCollision);
				}
				else if (_squareCollision == 2) {
					// _squaresCollision is 2 so bounces in x-axis
					Movement(_squareCollision);
				}

			}

			for (unsigned short int i = 0; i < windSprites.size(); i++) {
				// blows the ball in the direction the wind is blowing  
				if (collision.CheckBallAndWindCollision(ball->GetSprite(), windSprites.at(i))) {

					if (windDirections.at(i) == 0) {
						ball->MovedByWind(arrowAngle, powerBarSpeeds, 1);
						if (powerBarSpeeds.y > 0.0) {
							powerBarSpeeds.y  *= -1;
						}
					}
					else if (windDirections.at(i) == 90) {
						ball->MovedByWind(arrowAngle, powerBarSpeeds, 3);
						if (powerBarSpeeds.x < 0.0) {
							powerBarSpeeds.x *= -1;
						}
					}
					else if (windDirections.at(i) == 180) {
						ball->MovedByWind(arrowAngle, powerBarSpeeds, 2);
						if (powerBarSpeeds.y < 0.0) {
							powerBarSpeeds.y *= -1;
						}
					}
					else {
						ball->MovedByWind(arrowAngle, powerBarSpeeds, 4);
						if (powerBarSpeeds.x > 0.0) {
							powerBarSpeeds.x *= -1;
						}
					}
				}
			}

			// checks for springboard collisions
			_springSize = springboard->_animationIterator;

			// medium setting so springs off
			for (unsigned short int i = 0; i < springboardSprites.size(); i++) {

				if (_springSize == 1) {
					_springboardCollided = collision.CheckBallAndSpringSideCollision(ball->GetSprite(), springboardSprites.at(i),
						springboardDirections.at(i));
				}
				// large setting so springs off
				else if (_springSize == 2) {
					_springboardCollided = collision.CheckBallAndSpringSideCollision(ball->GetSprite(), springboardSprites.at(i),
						springboardDirections.at(i));
				}

				if (_springboardCollided) {
					// bounces off whatever axis it is facing and a set speed
					
					// 1 = up, 2 = down, 3 = right , 4 = left
					if (springboardDirections.at(i) == 0) {
						ball->BouncedOffSpringboard(arrowAngle, powerBarSpeeds, 1);
					}
					else if (springboardDirections.at(i) == 90) {
						ball->BouncedOffSpringboard(arrowAngle, powerBarSpeeds, 3);
					}
					else if (springboardDirections.at(i) == 180) {
						ball->BouncedOffSpringboard(arrowAngle, powerBarSpeeds, 2);
					}
					else {
						ball->BouncedOffSpringboard(arrowAngle, powerBarSpeeds, 4);
					}
				}
				else {
					for (unsigned short int i = 0; i < springboardSprites.size(); i++) {
						// smallest spring setting so no bounce just reflect 
						if (_springSize == 0) {
							// small collision
							_rectangleCollision = collision.CheckBallAndSpringboardCollision(ball->GetSprite(), springboardSprites.at(i), 64, 192);

						}
						else if (_springSize == 1) {
							// medium collision
							_rectangleCollision = collision.CheckBallAndSpringboardCollision(ball->GetSprite(), springboardSprites.at(i), 64, 192);
						}
						else {
							_rectangleCollision = collision.CheckBallAndRectangleCollision(ball->GetSprite(), springboardSprites.at(i));
						}
						if (_rectangleCollision == 1) {
							// bounces in y-axis
							powerBarSpeeds.y *= -1;
							ball->CollidedWithSpringboard(arrowAngle, powerBarSpeeds);
						}
						else if (_rectangleCollision == 2) {
							// bounces in x-axis
							powerBarSpeeds.x *= -1;
						}
					}
				}
			}

			_doorState = door->_animationIterator;

			for (unsigned short int i = 0; i < doorSprites.size(); i++) {
				if (_doorState == 0 || _doorState == 1) {
					_rectangleCollision = collision.CheckBallAndRectangleCollision(ball->GetSprite(), doorSprites.at(i));
					if (_rectangleCollision > 0) {
						Movement(_rectangleCollision);
					}
				}
				else {
					_rectangleCollision = collision.CheckBallAndRectangleCollision(ball->GetSprite(), leftDoorSprites.at(i));
					if (_rectangleCollision > 0) {
						Movement(_rectangleCollision);
					}

					_rectangleCollision = collision.CheckBallAndRectangleCollision(ball->GetSprite(), rightDoorSprites.at(i));

					if (_rectangleCollision > 0) {
						Movement(_rectangleCollision);
					}
				}
			}
			

			// moves the ball in the direction it was aimed
			ball->Move(arrowAngle, powerBarSpeeds);

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
			ball->Move(arrowAngle, powerBarSpeeds);
			ball->Move(arrowAngle, powerBarSpeeds);
		}
		else {
			// bounces in x-axis
			powerBarSpeeds.x *= -1;
			ball->Move(arrowAngle, powerBarSpeeds);
			ball->Move(arrowAngle, powerBarSpeeds);
		}
	}

	void GameState::SetPositionOfComponents()
	{
		// 1st row
		for (int i = 2; i < 6; i++) {
			squareObstacles->SpawnSquare(64+128*i, 64, 2, 2);
		}
		// 2nd row
		squareObstacles->SpawnSquare(320,192, 2, 2);
		squareObstacles->SpawnSquare(704, 192, 2, 2);
		// 3rd row
		squareObstacles->SpawnSquare(320, 320, 2, 2);
		squareObstacles->SpawnSquare(704, 320, 2, 2);
		// 4th row
		squareObstacles->SpawnSquare(704, 448, 2, 2);
		// 5th row
		squareObstacles->SpawnSquare(704, 576, 2, 2);
		// 6th row
		squareObstacles->SpawnSquare(192, 704, 2, 2);
		// 7th row
		squareObstacles->SpawnSquare(192, 832, 2, 2);
		// 8th row
		for (int i = 1; i < 6; i++) {
			squareObstacles->SpawnSquare(64+128*i, 960, 2, 2);
		}

		// stores a vector of sprites that are squares
		squareSprites = squareObstacles->GetSprites();

		// spawns  3 winds each covering 3 tiles vertically, 1 horizontally
		wind->SpawnWind(448, 448, 1.28, 3.84, 180);
		wind->SpawnWind(832, 704, 1.28, 3.84, 0);
		wind->SpawnWind(960, 704, 1.28, 3.84, 0);

		windSprites = wind->GetSprites();
		windDirections = wind->GetDirections();

		// spawns a springs
		springboard->SpawnSpringboard(352, 768, 5.408, 3.7647, 90); // right

		springboardSprites = springboard->GetSprites();
		springboardDirections = springboard->GetDirections();

		//spawns a doors
		door->spawnDoor(300,512,6.24,3.368,90); // right

		doorSprites = door->GetSprites();
		rightDoorSprites = door->GetRightOpenDoors();
		leftDoorSprites = door->GetLeftOpenDoors();
		doorDirections = door->GetDirections();

		// spawns 3 fans
		fan->SpawnFan(448, 192, 2.56, 2.56, 180); // down
		fan->SpawnFan(832, 960, 2.56, 2.56, 0); // up
		fan->SpawnFan(960, 960, 2.56, 2.56, 0); // up


		fanSprites = fan->GetSprites();
		fanDirections = fan->GetDirections();

		ball->SpawnBall(64, 512, 0.615, 0.667);
		arrow->SpawnArrow(64, 512, 1.5, 1.5);
		targets->SpawnTarget(896, 256);
		powerBar->SpawnPowerBar(192, 832, 1.8, 2.7);

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


	void GameState::LoadTextures()
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
		this->_data->assets.LoadTexture("Closed Door", DOOR_CLOSED);
		this->_data->assets.LoadTexture("Opening Door", DOOR_OPENING);
		this->_data->assets.LoadTexture("Open Door", DOOR_OPEN);
		this->_data->assets.LoadTexture("Left Open Door", LEFT_OPEN_DOOR);
		this->_data->assets.LoadTexture("Right Open Door", RIGHT_OPEN_DOOR);
	}

}
