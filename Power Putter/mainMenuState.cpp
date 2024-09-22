#include "mainMenuState.h"
#include <sstream>
#include "gameState.h"
#include "LevelSelectState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace Fish
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		// load the texture of the background
		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND);
		this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON);
		this->_data->assets.LoadTexture("Level Select", LEVEL_SELECT);
		this->_data->assets.LoadTexture("Game Title", GAME_TITLE);

		// set the texture
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		_levelSelect.setTexture(this->_data->assets.GetTexture("Level Select"));
		_gameTitle.setTexture(this->_data->assets.GetTexture("Game Title"));


		_playButton.scale(3, 3);
		_levelSelect.scale(3, 3);
		_gameTitle.scale(3, 3);

		// centred in y axis and x axis
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2.5) - (_playButton.getGlobalBounds().height / 2));
		_levelSelect.setPosition((SCREEN_WIDTH / 2) - (_levelSelect.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 1.5) - (_levelSelect.getGlobalBounds().height / 2));
		_gameTitle.setPosition((SCREEN_WIDTH / 2) - (_levelSelect.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 8) - (_levelSelect.getGlobalBounds().height / 2));
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			// check when the play button is clicked
			if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window)) {
				// Switches To Game screen by adding it to the top of the game screen tasks 
				// tells the game state to load level 1
				_data->machine.AddState(StateRef(new GameState(_data,1)), true);
			}

			// check when the level select button is clicked
			if (_data->input.IsSpriteClicked(_levelSelect, sf::Mouse::Left, _data->window)) {
				// Switches To Game screen by adding it to the top of the game screen tasks 
				// tells the game state to load level 1
				_data->machine.AddState(StateRef(new LevelSelectState(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background); // add the background
		this->_data->window.draw(this->_playButton); // adds the play button 
		this->_data->window.draw(this->_levelSelect); // adds the level select button 
		this->_data->window.draw(this->_gameTitle); // adds the game title  

		this->_data->window.display();
	}
}