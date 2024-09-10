#include "target.h"
#include <iostream>

namespace Fish {

	Target::Target(GameDataRef data) : _data(data) 
	{
		_goldTarget.setTexture(this->_data->assets.GetTexture("Gold Target"));
		_silverTarget.setTexture(this->_data->assets.GetTexture("Silver Target"));
		_bronzeTarget.setTexture(this->_data->assets.GetTexture("Bronze Target"));
	}

	void Target::SpawnTarget(int x, int y, float scaleX, float scaleY)
	{
		_goldTarget.setPosition(x, y);
		sf::Vector2f origin = sf::Vector2f(_goldTarget.getGlobalBounds().width / 2, _goldTarget.getGlobalBounds().height / 2);
		_goldTarget.setOrigin(origin);
		_goldTarget.scale(scaleX, scaleY);
		goldRadius = (_goldTarget.getGlobalBounds().width * scaleX) / 2;

		_silverTarget.setPosition(x, y);
		origin = sf::Vector2f(_silverTarget.getGlobalBounds().width / 2, _silverTarget.getGlobalBounds().height / 2);
		_silverTarget.setOrigin(origin);
		silverRadius = (_silverTarget.getGlobalBounds().width * scaleX) / 2;
		_silverTarget.scale(scaleX, scaleY);

		_bronzeTarget.setPosition(x, y);
		origin = sf::Vector2f(_bronzeTarget.getGlobalBounds().width / 2, _bronzeTarget.getGlobalBounds().height / 2);
		_bronzeTarget.setOrigin(origin);
		bronzeRadius = (_bronzeTarget.getGlobalBounds().width * scaleX) / 2;
		_bronzeTarget.scale(scaleX, scaleY);
	}

	void Target::Draw()
	{
		_data->window.draw(_bronzeTarget);
		_data->window.draw(_silverTarget);
		_data->window.draw(_goldTarget);
	}

	const sf::Sprite& Target::GetBronzeSprite() const
	{
		return _bronzeTarget;
	}

	const sf::Sprite& Target::GetSilverSprite() const
	{
		return _silverTarget;
	}

	const sf::Sprite& Target::GetGoldSprite() const
	{
		return _goldTarget;
	}

	float Target::BronzeRadius()
	{
		return bronzeRadius;
	}

	float Target::SilverRadius()
	{
		return silverRadius;
	}

	float Target::GoldRadius()
	{
		return goldRadius;
	}

}