#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace Fish
{
	struct GameData
	{
		StateMachine machine; 
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef; // reference to all the game data

	class Game
	{
	public:
		Game(int width, int height, std::string title); // constructor

	private:
		// Updates run at 60 frames per second.
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock; // clock to keep frame rates consistent

		GameDataRef _data = std::make_shared<GameData>(); 

		void Run();
	};
}