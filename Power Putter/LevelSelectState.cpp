#include "LevelSelectState.h"
#include <sstream>
#include "gameState.h"
#include "mainMenuState.h"
#include "DEFINITIONS.h"

#include <iostream>


namespace Fish {
		
	LevelSelectState::LevelSelectState(GameDataRef data) : _data(data) {}

	void LevelSelectState::Init()
	{
		// load the texture of the background
		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);
		this->_data->assets.LoadTexture("Level 1", LEVEL1);
		this->_data->assets.LoadTexture("Level 2", LEVEL2);
		this->_data->assets.LoadTexture("Level 3", LEVEL3);
		this->_data->assets.LoadTexture("Select a Level", SELECT_LEVEL);

		// set the texture
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));
		_level1.setTexture(this->_data->assets.GetTexture("Level 1"));
		_level2.setTexture(this->_data->assets.GetTexture("Level 2"));
		_level3.setTexture(this->_data->assets.GetTexture("Level 3"));
		_selectLevel.setTexture(this->_data->assets.GetTexture("Select a Level"));

		// positions of each button

		_homeButton.setPosition(64, 64);

		_level1.setPosition((SCREEN_WIDTH / 8) - (_level1.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_level1.getGlobalBounds().height / 2));

		_level2.setPosition((SCREEN_WIDTH / 2) - (_level2.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_level2.getGlobalBounds().height / 2));

		_level3.setPosition((SCREEN_WIDTH / 1.2) - (_level3.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_level3.getGlobalBounds().height / 2));

		_selectLevel.setPosition((SCREEN_WIDTH / 2.5) - (_selectLevel.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 5) - (_selectLevel.getGlobalBounds().height / 2));

		// stops the buttons enlarging after every attempt 
		if (_homeButton.getScale().x != 3) {
			_homeButton.scale(3, 3);
			_level1.scale(3, 3);
			_level2.scale(3, 3);
			_level3.scale(3, 3);
			_selectLevel.scale(2, 2);
		}
		
	}

	void LevelSelectState::HandleInput()
	{
		// handles when each button is pressed
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			// check when the play button is clicked
			if (_data->input.IsSpriteClicked(_homeButton, sf::Mouse::Left, _data->window)) {
				// Switches To Game screen by adding it to the top of the game screen tasks 
				// tells the game state to load level 1
				_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}

			// checks when the level 1 is clicked
			if (_data->input.IsSpriteClicked(_level1, sf::Mouse::Left, _data->window)) {
				// Switches To Game screen by adding it to the top of the game screen tasks 
				// tells the game state to load level 1
				_data->machine.AddState(StateRef(new GameState(_data,1)), true);
			}
			// check when the level 2 is clicked
			if (_data->input.IsSpriteClicked(_level2, sf::Mouse::Left, _data->window)) {
				// Switches To Game screen by adding it to the top of the game screen tasks 
				// tells the game state to load level 2
				_data->machine.AddState(StateRef(new GameState(_data, 2)), true);
			}
			// check when the level 3 is clicked
			if (_data->input.IsSpriteClicked(_level3, sf::Mouse::Left, _data->window)) {
				// Switches To Game screen by adding it to the top of the game screen tasks 
				// tells the game state to load level 3
				_data->machine.AddState(StateRef(new GameState(_data, 3)), true);
			}
		}
	}

	void LevelSelectState::Update(float dt)
	{
	}

	void LevelSelectState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);

		this->_data->window.draw(this->_background); // add the background
		this->_data->window.draw(this->_homeButton); // adds the home button so you can navigate back to the home button 
		this->_data->window.draw(this->_selectLevel); // adds the level select
		this->_data->window.draw(this->_level1); // adds level 1
		this->_data->window.draw(this->_level2); // adds level 2
		this->_data->window.draw(this->_level3); // adds the level 3

		this->_data->window.display();
	}
}