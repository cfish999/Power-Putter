#include <sstream>
#include "gameState.h"
#include "mainMenuState.h"
#include "ball.h"
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
		
		ball = new Ball(_data);


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
				// The ball has been hit so should rotate and move now 
				ball->_ballState = BALL_STATE_MOVING;
			}
		}
	}

	void GameState::Update(float dt)
	{
		ball->Update(dt);
		ball->Move(_defaultSpeed);
	}

	void GameState::Draw(float dt)
	{
		// draws all the level contents to the screen 
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		ball->Draw();

		this->_data->window.display();
	}
}
