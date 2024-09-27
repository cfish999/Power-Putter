#include "target.h"
#include <iostream>

namespace Fish {

	Target::Target(GameDataRef data) : _data(data) 
	{
		_target.setTexture(this->_data->assets.GetTexture("Target"));

	}

	void Target::SpawnTarget(int x, int y, float scaleX, float scaleY)
	{
		_target.setPosition(x, y);
		sf::Vector2f origin = sf::Vector2f(_target.getGlobalBounds().width / 2, _target.getGlobalBounds().height / 2);
		_target.setOrigin(origin);
		_target.scale(scaleX, scaleY);
		targetRadius = (_target.getGlobalBounds().width * scaleX) / 2;

	}

	void Target::Draw()
	{
		_data->window.draw(_target);
	}

	const sf::Sprite& Target::GetTargetSprite() const
	{
		return _target;
	}



	float Target::TargetRadius()
	{
		return targetRadius;
	}

}