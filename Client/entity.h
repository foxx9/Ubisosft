#pragma once

namespace sf
{
	class RenderWindow;
}

namespace Client
{
	class Player;

	class Entity
	{
	public:
		virtual void	Init() = 0;
		virtual void	Tick() = 0;
		virtual void	Term() = 0;

		virtual bool	CanDestroy() = 0;

		virtual void	SetOwner(Player* player) = 0;
		virtual Player*	GetOwner() = 0;

		virtual void	SetPosition(float x, float y) = 0;
		virtual void	GetPosition(float& x, float& y) = 0;

		virtual bool	IsWalkable() = 0;

		virtual void	Draw(sf::RenderWindow* window) = 0;
	};
}