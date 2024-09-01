#include <SFML/Graphics.hpp>
#include "AssetManager.h"

namespace Fish
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		// loads a texture in
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
		}
	}

	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		// returns the texture from the texture map 
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		// loads a font in 
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	sf::Font& AssetManager::GetFont(std::string name)
	{
		// returns a font from the font map
		return this->_fonts.at(name);
	}
}