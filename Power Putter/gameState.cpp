#include <sstream>
#include "gameState.h"
#include "mainMenuState.h"
#include "ball.h"
#include "arrow.h"
#include "power_bar.h"
#include "target.h"
#include "collision.h"
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

		
		ball = new Ball(_data);
		arrow = new Arrow(_data);
		powerBar = new PowerBar(_data);
		targets = new Target(_data);



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
			ball->Move(arrowAngle,powerBarSpeed);
		}

		if (ball->_ballState == BALL_STATE_STILL) {
			
			// must be ball then target for sprites to work 
			if (collision.CheckTargetAndBallCollision(ball->GetSprite(), targets->GetGoldSprite())) {
				std::cout << "gold medal" << std::endl;
			}
			else if (collision.CheckTargetAndBallCollision(ball->GetSprite(), targets->GetSilverSprite())) {
				std::cout << "silver medal" << std::endl;
			}
			else if (collision.CheckTargetAndBallCollision(ball->GetSprite(), targets->GetBronzeSprite())) {
				std::cout << "bronze medal" << std::endl;
			}
			else {
				std::cout << "no medal!" << std::endl;
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

		this->_data->window.display();
	}
}
