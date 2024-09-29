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
	GameState::GameState(GameDataRef data, int currentLevel) : _data(data), _currentLevel(currentLevel) {}

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


		SetPositionOfComponents(_currentLevel);

		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);
		// set the texture
		_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));
		_homeButton.setPosition(864,32);

		// stops the home button enlarging after every attempt 
		if (_homeButton.getScale().x != 2) {
			_homeButton.scale(2, 2);
		}

		if (!_shotFont.loadFromFile("fonts/Midnight.otf")) {
			std::cerr << "Could  not load font" << std::endl;
			exit(-1);
		}

		// Showcasing the requirements for the stars
		_goldString = "Gold Star: ";
		_silverString = "Silver Star: ";
		_bronzeString = "Bronze Star: ";
		if (_currentLevel == 1) {
			_goldString += std::to_string(GOLD_L1);
			_silverString += std::to_string(SILVER_L1);
			_bronzeString += std::to_string(BRONZE_L1);
		} else if (_currentLevel == 2) {
			_goldString += std::to_string(GOLD_L2);
			_silverString += std::to_string(SILVER_L2);
			_bronzeString += std::to_string(BRONZE_L2);
		} else {
			_goldString += std::to_string(GOLD_L3);
			_silverString += std::to_string(SILVER_L3);
			_bronzeString += std::to_string(BRONZE_L3);
		}

		_goldText.setString(_goldString);
		_goldText.setFont(_shotFont);
		_goldText.setCharacterSize(32);
		_goldText.setPosition(200, 20);

		_silverText.setString(_silverString);
		_silverText.setFont(_shotFont);
		_silverText.setCharacterSize(32);
		_silverText.setPosition(400, 20);

		_bronzeText.setString(_bronzeString);
		_bronzeText.setFont(_shotFont);
		_bronzeText.setCharacterSize(32);
		_bronzeText.setPosition(600, 20);


		
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

			// checks when the home button has been clicked
			if (_data->input.IsSpriteClicked(_homeButton, sf::Mouse::Left, _data->window)) {
				_data->machine.AddState(StateRef(new MainMenuState(_data)));
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
					// sets the power bar needed to false to stop the animation occurring 
					powerBar->powerBarNeeded = false;
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
						if (powerBarSpeeds.y > 0.0) {
							powerBarSpeeds.y *= -1;
						}
						powerBarSpeeds = ball->MovedByWind(arrowAngle, powerBarSpeeds, 1);
					}
					else if (windDirections.at(i) == 90) {
						if (powerBarSpeeds.x < 0.0) {
							powerBarSpeeds.x *= -1;
						}
						powerBarSpeeds = ball->MovedByWind(arrowAngle, powerBarSpeeds, 3);
					}
					else if (windDirections.at(i) == 180) {
						if (powerBarSpeeds.y < 0.0) {
							powerBarSpeeds.y *= -1;
						}
						powerBarSpeeds = ball->MovedByWind(arrowAngle, powerBarSpeeds, 2);
					}
					else {
						if (powerBarSpeeds.x > 0.0) {
							powerBarSpeeds.x *= -1;
						}
						powerBarSpeeds = ball->MovedByWind(arrowAngle, powerBarSpeeds, 4);
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
						powerBarSpeeds = ball->BouncedOffSpringboard(arrowAngle, powerBarSpeeds, 1);
					}
					else if (springboardDirections.at(i) == 90) {
						powerBarSpeeds = ball->BouncedOffSpringboard(arrowAngle, powerBarSpeeds, 3);
					}
					else if (springboardDirections.at(i) == 180) {
						powerBarSpeeds = ball->BouncedOffSpringboard(arrowAngle, powerBarSpeeds, 2);
					}
					else {
						powerBarSpeeds = ball->BouncedOffSpringboard(arrowAngle, powerBarSpeeds, 4);
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
						if (_dullClock.getElapsedTime().asSeconds() > SPRINGBOARD_SLOWDOWN) {
							if (_rectangleCollision == 1) {
								// bounces in y-axis
								powerBarSpeeds.y *= -1;
								ball->CollidedWithSpringboard(arrowAngle, powerBarSpeeds);
								_dullClock.restart();
							}
							else if (_rectangleCollision == 2) {
								// bounces in x-axis
								powerBarSpeeds.x *= -1;
								ball->CollidedWithSpringboard(arrowAngle, powerBarSpeeds);
								_dullClock.restart();
							}
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
			_shots++;
			// checks if the ball has landed on the target
			if (collision.CheckTargetAndBallCollision(ball->GetSprite(), targets->GetTargetSprite(), 
				targets->TargetRadius(), ball->getBallRadius())) {
				if (_currentLevel == 1) {
					if (_shots <= GOLD_L1) {
						_medalTier = 1;
					}
					else if (_shots <= SILVER_L1) {
						_medalTier = 2;
					}
					else if (_shots <= BRONZE_L1) {
						_medalTier = 3;
					}
					else {
						_medalTier = 0;
					}
				}
				else if (_currentLevel == 2) {
					if (_shots <= GOLD_L2) {
						_medalTier = 1;
					}
					else if (_shots <= SILVER_L2) {
						_medalTier = 2;
					}
					else if (_shots <= BRONZE_L2) {
						_medalTier = 3;
					}
					else {
						_medalTier = 0;
					}
				}
				else if(_currentLevel == 3) {
					if (_shots <= GOLD_L3) {
						_medalTier = 1;
					}
					else if (_shots <= SILVER_L3) {
						_medalTier = 2;
					}
					else if (_shots <= BRONZE_L3) {
						_medalTier = 3;
					}
					else {
						_medalTier = 0;
					}
				}
				else {
					std::cerr << "Error Occurred" << std::endl;
				}
				// sends the player to the medal screen 
				_data->machine.AddState(StateRef(new medalScreen(_data, _medalTier, _currentLevel,_shots,_shotFont)), true);
			}
			else {
				if (collision.CheckBoundAreaAndBallCollision(ball->GetSprite(), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))) {
					std::cout << _shots << std::endl;
					arrow->_arrowState = ROTATING;
					arrow->MoveToBall(ball->GetSprite());
					ball->_ballState = BALL_STATE_STILL;
					// sets the power bar needed to true to stop the animation occurring 
					powerBar->powerBarNeeded = true;
					firstClick = true;
					ball->_slowdown = 1.0;
					// call a function for power bar and aim to work again 

				}
				else {
					std::cout << "out of bounds" << std::endl;
					// resets the screen when the ball goes out of bounds  
					firstClick = true;
					ball->_ballState = BALL_STATE_STILL;
					_shots = 0;
					Init();
				}
			}
			
		}

		_shotsHad = "Shot " + std::to_string(_shots);
		_textShots.setString(_shotsHad);
		_textShots.setFont(_shotFont);
		_textShots.setCharacterSize(32);
		_textShots.setPosition(20, 20);


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

	void GameState::SetPositionOfComponents(int levelSelect)
	{

	
		// level 1
		if (levelSelect == 1) {

			// 1st row
			for (int i = 2; i < 6; i++) {
				squareObstacles->SpawnSquare(64 + 128 * i, 64, 1, 1, 1);
			}
			// 2nd row
			squareObstacles->SpawnSquare(320, 192, 1, 1, 1);
			squareObstacles->SpawnSquare(704, 192, 1, 1, 2);
			// 3rd row
			squareObstacles->SpawnSquare(320, 320, 1, 1, 1);
			squareObstacles->SpawnSquare(704, 320, 1, 1, 1);
			// 4th row
			squareObstacles->SpawnSquare(704, 448, 1, 1, 1);
			// 5th row
			squareObstacles->SpawnSquare(704, 560, 1, 1, 2);
			// 6th row
			squareObstacles->SpawnSquare(192, 704, 1, 1, 2);
			// 7th row
			squareObstacles->SpawnSquare(192, 832, 1, 1, 1);
			// 8th row
			for (int i = 1; i < 6; i++) {
				squareObstacles->SpawnSquare(64 + 128 * i, 960, 1, 1, 1);
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
			springboard->SpawnSpringboard(320, 768, 5.408, 3.7647, 90); // right

			springboardSprites = springboard->GetSprites();
			springboardDirections = springboard->GetDirections();

			//spawns a doors
			door->spawnDoor(300, 512, 6.24, 3.368, 90); // right

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
			arrow->SpawnArrow(64, 512, 1.5, 0.5);
			targets->SpawnTarget(896, 384, 1.5, 1.5);
			powerBar->SpawnPowerBar(192, 832, 1.8, 2.7);
		}
		else if(levelSelect == 2) {

			// 1st row
			for (int i = 2; i < 7; i++) {
				squareObstacles->SpawnSquare(64 + 128 * i, 64, 1, 1, 1);
			}
			// 2nd row 
			squareObstacles->SpawnSquare(576, 192, 1, 1, 1);
			squareObstacles->SpawnSquare(832, 192, 1, 1, 2);
			// 3rd row
			squareObstacles->SpawnSquare(224, 336, 0.5, 1, 1);
			squareObstacles->SpawnSquare(832, 320, 1, 1, 1);
			// 4th row 
			squareObstacles->SpawnSquare(224, 448, 0.5, 1, 1);
			squareObstacles->SpawnSquare(320, 448, 1, 1, 2);
			squareObstacles->SpawnSquare(832, 448, 1, 1, 1);
			// 5th row
			squareObstacles->SpawnSquare(320, 576 ,1, 1, 1);
			squareObstacles->SpawnSquare(576, 576, 1, 1, 1);
			// 6th row
			squareObstacles->SpawnSquare(320, 704, 1, 1, 1);
			squareObstacles->SpawnSquare(576, 704, 1, 1, 1);
			// 7th row
			squareObstacles->SpawnSquare(576, 832, 1, 1, 2);
			// 8th row
			squareObstacles->SpawnSquare(64, 960, 1, 1, 1);
			squareObstacles->SpawnSquare(192, 960, 1, 1, 2);
			squareObstacles->SpawnSquare(320, 960, 1, 1, 1);
			for (int i = 4; i < 7; i++) {
				squareObstacles->SpawnSquare(64 + 128 * i, 960, 1, 1, 1);
			}

			// stores a vector of sprites that are squares
			squareSprites = squareObstacles->GetSprites();

			// spawns 2 fans
			fan->SpawnFan(64, 832, 2.56, 2.56, 180); // right
			fan->SpawnFan(704, 192, 2.56, 2.56, 90); // down

			fanSprites = fan->GetSprites();
			fanDirections = fan->GetDirections();

			// spawns 2 winds
			wind->SpawnWind(192, 832, 2.56,1.28, 90);
			wind->SpawnWind(704, 384, 2.56,2.56, 180);

			windSprites = wind->GetSprites();
			windDirections = wind->GetDirections();

			//spawns a door
			door->spawnDoor(576, 384, 6.24, 3.368, 90); // right

			doorSprites = door->GetSprites();
			rightDoorSprites = door->GetRightOpenDoors();
			leftDoorSprites = door->GetLeftOpenDoors();
			doorDirections = door->GetDirections();

			// spawns 2 springs
			springboard->SpawnSpringboard(448, 928, 2.704, 5.565, 0); // up
			springboard->SpawnSpringboard(960, 928, 2.704, 5.565, 0); // up

			springboardSprites = springboard->GetSprites();
			springboardDirections = springboard->GetDirections();


		}
		else if (levelSelect == 3) {

			// 1st row
			squareObstacles->SpawnSquare(704, 64, 1, 1, 1);
			squareObstacles->SpawnSquare(832, 64, 1, 1, 1);

			// 2nd row 
			squareObstacles->SpawnSquare(320, 224, 1, 0.5, 1);
			squareObstacles->SpawnSquare(576, 192, 1, 1, 1);
			squareObstacles->SpawnSquare(832, 192, 1, 1, 1);
			// 3rd row
			squareObstacles->SpawnSquare(320, 320, 1, 1, 1);
			squareObstacles->SpawnSquare(832, 320, 1, 1, 1);
			// 4th row 
			squareObstacles->SpawnSquare(320, 448, 1, 1, 1);
			squareObstacles->SpawnSquare(832, 448, 1, 1, 2);
			// 5th row
			squareObstacles->SpawnSquare(320, 576, 1, 1, 1);
			squareObstacles->SpawnSquare(576, 576, 1, 1, 1);
			// 6th row
			squareObstacles->SpawnSquare(320, 704, 1, 1, 2);
			squareObstacles->SpawnSquare(576, 704, 1, 1, 1);
			// 7th row
			squareObstacles->SpawnSquare(64, 832, 1, 1, 1);
			squareObstacles->SpawnSquare(576, 832, 1, 1, 1);
			squareObstacles->SpawnSquare(832, 832, 1, 1, 1);
			// 8th row
			for (int i = 0; i < 3; i++) {
				squareObstacles->SpawnSquare(64 + 128 * i, 960, 1, 1, 1);
			}
			squareObstacles->SpawnSquare(576, 960, 1, 1, 2);
			squareObstacles->SpawnSquare(832, 960, 1, 1, 1);

			// stores a vector of sprites that are squares
			squareSprites = squareObstacles->GetSprites();

			// spawns 2 fans
			fan->SpawnFan(64, 64, 2.56, 2.56, 180); // right
			fan->SpawnFan(704, 192, 2.56, 2.56, 90); // down

			fanSprites = fan->GetSprites();
			fanDirections = fan->GetDirections();

			// spawns 2 winds
			wind->SpawnWind(256, 64, 2.56, 2.56, 90);
			wind->SpawnWind(704, 384, 2.56, 2.56, 180);

			windSprites = wind->GetSprites();
			windDirections = wind->GetDirections();

			//spawns 2 doors
			door->spawnDoor(576, 384, 6.24, 3.368, 90); // right
			door->spawnDoor(832, 640, 6.24, 3.368, 90); // right

			doorSprites = door->GetSprites();
			rightDoorSprites = door->GetRightOpenDoors();
			leftDoorSprites = door->GetLeftOpenDoors();
			doorDirections = door->GetDirections();

			// spawns a spring
			springboard->SpawnSpringboard(448, 928, 2.704, 5.565, 0); // up

			springboardSprites = springboard->GetSprites();
			springboardDirections = springboard->GetDirections();

			ball->SpawnBall(64, 512, 0.32, 0.32);
			arrow->SpawnArrow(64, 512, 1, 1);
			targets->SpawnTarget(960, 256, 1.25, 1.25);
			powerBar->SpawnPowerBar(192, 832, 1.8, 2.7);
			
		}
		else {
			std::cout << "No More Levels!" << std::endl;
		}


	}

	void GameState::Draw(float dt)
	{
		// draws all the level contents to the screen 
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		squareObstacles->DrawSquares();
		fan->Draw();
		wind->Draw();
		springboard->Draw();
		door->Draw();
		targets->Draw();
		arrow->Draw();
		ball->Draw();
		powerBar->Draw();
		this->_data->window.draw(this->_homeButton);
		this->_data->window.draw(this->_goldText);
		this->_data->window.draw(this->_silverText);
		this->_data->window.draw(this->_bronzeText);
		this->_data->window.draw(this->_textShots);

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
		this->_data->assets.LoadTexture("Target", TARGET);
		this->_data->assets.LoadTexture("Wall Main", WALL_MAIN);
		this->_data->assets.LoadTexture("Wall Danger", WALL_DANGER);
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
