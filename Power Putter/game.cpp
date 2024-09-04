#include "game.h"
#include "mainMenuState.h"

#include <stdlib.h>
#include <time.h>

namespace Fish
{
	Game::Game(int width, int height, std::string title)
	{
		// seeds the random generator 
		srand(time(NULL));

		// creates the window 
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		// adds the first state 
		_data->machine.AddState(StateRef(new MainMenuState(this->_data)));

		this->Run();
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		// while the window is opene (program is running)
		while (this->_data->window.isOpen())
		{
			// process state changes all the time
			this->_data->machine.ProcessStateChanges();

			// calculate time to keep frame rates consistent and keep everything running smoothly 
			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);

				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}