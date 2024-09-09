#include "target.h"

namespace Fish {

	Target::Target(GameDataRef data) : _data(data) 
	{
		_goldTarget.setTexture(this->_data->assets.GetTexture("Gold Target"));
		_silverTarget.setTexture(this->_data->assets.GetTexture("Silver Target"));
		_bronzeTarget.setTexture(this->_data->assets.GetTexture("Bronze Target"));
	}

	void Target::SpawnTarget(int x, int y)
	{
		_goldTarget.setPosition(x, y);
		sf::Vector2f origin = sf::Vector2f(_goldTarget.getGlobalBounds().width / 2, _goldTarget.getGlobalBounds().height / 2);
		_goldTarget.setOrigin(origin);
		_silverTarget.setPosition(x, y);
		origin = sf::Vector2f(_silverTarget.getGlobalBounds().width / 2, _silverTarget.getGlobalBounds().height / 2);
		_silverTarget.setOrigin(origin);
		_bronzeTarget.setPosition(x, y);
		origin = sf::Vector2f(_bronzeTarget.getGlobalBounds().width / 2, _bronzeTarget.getGlobalBounds().height / 2);
		_bronzeTarget.setOrigin(origin);
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

}