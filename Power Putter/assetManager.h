#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace Fish
{
	class AssetManager
	{
	public:
		AssetManager() { } // constructor
		~AssetManager() { } // destructor

		void LoadTexture(std::string name, std::string fileName);
		sf::Texture& GetTexture(std::string name);

		void LoadFont(std::string name, std::string fileName);
		sf::Font& GetFont(std::string name);

	private:
		std::map<std::string, sf::Texture> _textures; // stores a map of the textures
		std::map<std::string, sf::Font> _fonts; // stores a map of the fonts
	};
}