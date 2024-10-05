#include <sstream>
#include "medalScreen.h"
#include "gameState.h"
#include "mainMenuState.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <fstream>

namespace Fish
{

	medalScreen::medalScreen(GameDataRef data, int medalLevel, int lastLevelPlayed, int shots) : _data(data), _medalLevel(medalLevel),
		_lastLevelPlayed(lastLevelPlayed), _shotsTaken(shots) {}

	void medalScreen::Init()
	{

		// reusing the main menu background as the game over background for the minute 
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));

		// stores the game font in _shotFont
		_font = (this->_data->assets.GetFont("Game Font"));

		// loads the retry texture
		this->_data->assets.LoadTexture("Retry", RETRY);
		_retry.setTexture(this->_data->assets.GetTexture("Retry"));


		StarGiven();
		CheckNextLevel();

		// prevents enlargements 
		if (_homeButton.getScale().x != 3) {
			_homeButton.scale(3, 3);
			_retry.scale(3, 3);
			_statistics.scale(2, 2);
			_medal.scale(3, 3);
			_nextMedal.scale(3, 3);
		}

		// sets the positions of things on the screen 
		_homeButton.setPosition(64, 64);
		_retry.setPosition(794, 64);
		_statistics.setPosition(312, 312);
		_medal.setPosition(560, 460);
		_nextMedal.setPosition(560, 560);

		PlayerShots();
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
		HandleInput();
		Draw(dt);
	}

	void medalScreen::CheckNextLevel()
	{
		// checks wether the next level button is needed
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

	void medalScreen::StarGiven()
	{
		// displays a gold star or statistics to get gold star
		if (_shotsTaken == GOLD_L1 || _shotsTaken == GOLD_L2 || _shotsTaken == GOLD_L3) {
			this->_data->assets.LoadTexture("Gold Statistics", STATISTICS_GOLD);
			_statistics.setTexture(this->_data->assets.GetTexture("Gold Statistics"));
		}
		else {
			this->_data->assets.LoadTexture("Statistics", STATISTICS);
			_statistics.setTexture(this->_data->assets.GetTexture("Statistics"));
		}

		// displays the star achieved by the player
		if (_medalLevel == 1) {
			this->_data->assets.LoadTexture("Gold Star", GOLD_STAR);
			_medal.setTexture(this->_data->assets.GetTexture("Gold Star"));
		}
		else if (_medalLevel == 2) {
			this->_data->assets.LoadTexture("Silver Star", SILVER_STAR);
			_medal.setTexture(this->_data->assets.GetTexture("Silver Star"));
			// next medal (gold)
			this->_data->assets.LoadTexture("Gold Star", GOLD_STAR);
			_nextMedal.setTexture(this->_data->assets.GetTexture("Gold Star"));
		}
		else if (_medalLevel == 3) {
			this->_data->assets.LoadTexture("Bronze Star", BRONZE_STAR);
			_medal.setTexture(this->_data->assets.GetTexture("Bronze Star"));
			// next medal (silver)
			this->_data->assets.LoadTexture("Silver Star", SILVER_STAR);
			_nextMedal.setTexture(this->_data->assets.GetTexture("Silver Star"));

		}
		else {
			this->_data->assets.LoadTexture("Sad Star", SAD_STAR);
			_medal.setTexture(this->_data->assets.GetTexture("Sad Star"));
			// next medal (silver)
			this->_data->assets.LoadTexture("Bronze Star", BRONZE_STAR);
			_nextMedal.setTexture(this->_data->assets.GetTexture("Bronze Star"));
		}
	}

	void medalScreen::PlayerShots()
	{
		// calculates the players' score
		_text = "";
		_text += std::to_string(_shotsTaken);
		_shotsText.setString(_text);
		_shotsText.setFont(_font);
		_shotsText.setCharacterSize(56);
		_shotsText.setPosition(620, 380);
	}

	void medalScreen::Draw(float dt)
	{
		// draws all textures to the window 
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_homeButton);
		this->_data->window.draw(this->_retry);
		this->_data->window.draw(this->_nextLevel);
		this->_data->window.draw(this->_completed);
		this->_data->window.draw(this->_statistics);
		this->_data->window.draw(this->_medal);
		this->_data->window.draw(this->_nextMedal);
		this->_data->window.draw(this->_shotsText);

		this->_data->window.display();
	}
}