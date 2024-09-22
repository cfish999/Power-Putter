#include <sstream>
#include "medalScreen.h"
#include "gameState.h"
#include "mainMenuState.h"
#include "DEFINITIONS.h"

#include <iostream>
#include <fstream>

namespace Fish
{
	medalScreen::medalScreen(GameDataRef data, int medalLevel, int lastLevelPlayed) : _data(data), _medalLevel(medalLevel) ,
		_lastLevelPlayed(lastLevelPlayed) {}

	void medalScreen::Init()
	{

		this->_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE);

		// reusing the main menu background as the game over background for the minute 
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
		_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));

		this->_data->assets.LoadTexture("Retry", RETRY);
		_retry.setTexture(this->_data->assets.GetTexture("Retry"));

		// centres it
		_gameOverTitle.setPosition(_data->window.getSize().x / 2.25 - _gameOverTitle.getGlobalBounds().width / 2,
			_data->window.getSize().y / 2 - _gameOverTitle.getGlobalBounds().height / 2);

		if (_homeButton.getScale().x != 3) {
			_homeButton.scale(3, 3);
			_retry.scale(3, 3);
			_gameOverTitle.scale(3, 3);
		}

		_homeButton.setPosition(64, 64);
		_retry.setPosition(794, 64);

	}

	void medalScreen::HandleInput()
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
			// checks when the home button has been clicked
			if (_data->input.IsSpriteClicked(_retry, sf::Mouse::Left, _data->window)) {
				_data->machine.AddState(StateRef(new GameState(_data,_lastLevelPlayed)));
			}
		}
	}

	void medalScreen::Update(float dt)
	{

	}

	void medalScreen::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_gameOverTitle);
		this->_data->window.draw(this->_homeButton);
		this->_data->window.draw(this->_retry);

		this->_data->window.display();
	}
}