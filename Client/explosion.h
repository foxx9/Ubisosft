#pragma once

#include "entity.h"
#include "animator.h"

namespace Client
{
	class Explosion : public Entity
	{
	public:
		Explosion();
		~Explosion();

		virtual void	Init();
		virtual void	Tick();
		virtual void	Term();

		virtual void	Draw(sf::RenderWindow* window);

		virtual Player*	GetOwner();
		virtual void	SetOwner(Player* player);

		virtual bool	IsWalkable() { return true; }

		virtual bool	CanDestroy();
		virtual void	SetPosition(float x, float y);
		virtual void	GetPosition(float& x, float& y);

	private:
		float m_x;
		float m_y;

		Player*			m_owner;
		float			m_timeToExplode;
		Animator		m_animator;
		sf::Clock		m_deltaClock;
		bool			m_isOver;
	};

}