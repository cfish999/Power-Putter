#include "mainMenuState.h"
#include <sstream>
#include "gameState.h"
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

		// set the texture
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
	}

	void MainMenuState::HandleInput()
	{
		// check when the play button is clicked
	}

	void MainMenuState::Update(float dt)
	{

	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background); // add the background

		this->_data->window.display();
	}
}