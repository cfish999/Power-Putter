#include <sstream>
#include "medalScreen.h"
#include "gameState.h"
#include "mainMenuState.h"
#include "DEFINITIONS.h"

#include <iostream>
#include <fstream>

namespace Fish
{
	medalScreen::medalScreen(GameDataRef data, int medalLevel) : _data(data), _medalLevel(medalLevel)
	{

	}

	void medalScreen::Init()
	{

		this->_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE);

		// reusing the main menu background as the game over background for the minute 
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));

		// centres it
		_gameOverTitle.setPosition(_data->window.getSize().x / 2 - _gameOverTitle.getGlobalBounds().width / 2,
			_data->window.getSize().y / 2 - _gameOverTitle.getGlobalBounds().height / 2);

	}

	void medalScreen::HandleInput()
	{

	}

	void medalScreen::Update(float dt)
	{

	}

	void medalScreen::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_gameOverTitle);

		this->_data->window.display();
	}
}