#include "target.h"

namespace Fish {

	Target::Target(GameDataRef data) : _data(data) 
	{
		_goldTarget.setTexture(this->_data->assets.GetTexture("Gold Target"));
		_silverTarget.setTexture(this->_data->assets.GetTexture("Silver Target"));
		_bronzeTarget.setTexture(this->_data->assets.GetTexture("Bronze Target"));

		// figure a way out to automate the difference in positions 
		_goldTarget.setPosition(538,540);
		_silverTarget.setPosition(518,520);
		_bronzeTarget.setPosition(500,500);

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