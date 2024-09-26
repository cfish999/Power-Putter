#include <sstream>
#include "medalScreen.h"
#include "gameState.h"
#include "mainMenuState.h"
#include "DEFINITIONS.h"

#include <iostream>
#include <fstream>

namespace Fish
{
	medalScreen::medalScreen(GameDataRef data, int medalLevel, int lastLevelPlayed, int shots, sf::Font font) : _data(data), _medalLevel(medalLevel),
		_lastLevelPlayed(lastLevelPlayed), _shotsTaken(shots), _font(font) {}

	void medalScreen::Init()
	{

		// reusing the main menu background as the game over background for the minute 
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));

		this->_data->assets.LoadTexture("Retry", RETRY);
		_retry.setTexture(this->_data->assets.GetTexture("Retry"));


		if (_homeButton.getScale().x != 3) {
			_homeButton.scale(3, 3);
			_retry.scale(3, 3);
		}


		_homeButton.setPosition(64, 64);
		_retry.setPosition(794, 64);

		if (_medalLevel > 0) {
			this->_data->assets.LoadTexture("Gold Star", GOLD_STAR);
			_medal.setTexture(this->_data->assets.GetTexture("Gold Star"));
		}

		_medal.setPosition(SCREEN_WIDTH / 2 - _medal.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - _medal.getGlobalBounds().height / 2);

		// calculating the score
		_text = "Shots: ";
		_text += std::to_string(_shotsTaken);
		_shotsText.setString(_text);
		_shotsText.setFont(_font);
		_shotsText.setCharacterSize(56);
		_shotsText.setPosition(300, 300);

		if (_lastLevelPlayed != 3) {
			// put next button in 
			// last level played +1 aswell 
			this->_data->assets.LoadTexture("Next Level", NEXT_LEVEL);
			_nextLevel.setTexture(this->_data->assets.GetTexture("Next Level"));
			_nextLevel.setPosition(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 1.5);
			_nextLevel.scale(2, 2);
		}
		else {
			// put All levels complete 
		}
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
			// checks when the home button has been clicked
			if (_data->input.IsSpriteClicked(_nextLevel, sf::Mouse::Left, _data->window)) {
				_data->machine.AddState(StateRef(new GameState(_data, _lastLevelPlayed+1)));
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
		this->_data->window.draw(this->_homeButton);
		this->_data->window.draw(this->_retry);
		this->_data->window.draw(this->_medal);
		this->_data->window.draw(this->_shotsText);
		this->_data->window.draw(this->_nextLevel);

		this->_data->window.display();
	}
}