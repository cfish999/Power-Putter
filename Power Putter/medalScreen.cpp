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

		if (_shotsTaken == GOLD_L1 || _shotsTaken == GOLD_L2 || _shotsTaken == GOLD_L3) {
			this->_data->assets.LoadTexture("Gold Statistics", STATISTICS_GOLD);
			_statistics.setTexture(this->_data->assets.GetTexture("Gold Statistics"));
		}
		else {
			this->_data->assets.LoadTexture("Statistics", STATISTICS);
			_statistics.setTexture(this->_data->assets.GetTexture("Statistics"));
		}


		if (_medalLevel == 1) {
			this->_data->assets.LoadTexture("Gold Star", GOLD_STAR);
			_medal.setTexture(this->_data->assets.GetTexture("Gold Star"));
		}
		else if (_medalLevel == 2) {
			this->_data->assets.LoadTexture("Silver Star", SILVER_STAR);
			_medal.setTexture(this->_data->assets.GetTexture("Silver Star"));
		}
		else if (_medalLevel == 3) {
			this->_data->assets.LoadTexture("Bronze Star", BRONZE_STAR);
			_medal.setTexture(this->_data->assets.GetTexture("Bronze Star"));
		}
		else {
			// do nothing
		}

		if (_homeButton.getScale().x != 3) {
			_homeButton.scale(3, 3);
			_retry.scale(3, 3);
			_statistics.scale(2, 2);
			_medal.scale(3, 3);
		}


		_homeButton.setPosition(64, 64);
		_retry.setPosition(794, 64);
		_statistics.setPosition(312, 312);
		_medal.setPosition(560, 460);

		// calculating the score
		_text = "";
		_text += std::to_string(_shotsTaken);
		_shotsText.setString(_text);
		_shotsText.setFont(_font);
		_shotsText.setCharacterSize(56);
		_shotsText.setPosition(620, 380);

		if (_lastLevelPlayed != 3) {
			this->_data->assets.LoadTexture("Next Level", NEXT_LEVEL);
			_nextLevel.setTexture(this->_data->assets.GetTexture("Next Level"));
			_nextLevel.setPosition(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 1.2);
			_nextLevel.scale(1.5, 1.5);
		}
		else {
			// put All levels complete 
			this->_data->assets.LoadTexture("Completed", COMPLETED);
			_completed.setTexture(this->_data->assets.GetTexture("Completed"));
			_completed.setPosition(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 1.2);
			_completed.scale(2, 2);
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
		this->_data->window.draw(this->_nextLevel);
		this->_data->window.draw(this->_completed);
		this->_data->window.draw(this->_statistics);
		this->_data->window.draw(this->_medal);
		this->_data->window.draw(this->_shotsText);

		this->_data->window.display();
	}
}