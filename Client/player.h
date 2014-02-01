#pragma once

#include "entity.h"

#include "animator.h"

namespace Client
{
	class Player : public Entity
	{
	public:
		Player();
		~Player();

		virtual void	Init();
		virtual void	Tick();
		virtual void	Term();

		virtual void	Draw(sf::RenderWindow* window);

		virtual Player*	GetOwner() { return nullptr; }
		virtual void	SetOwner(Player* player) { (void)player; }

		bool			IsWalkable() { return true; }
		void			SetColor(sf::Color color);

		void			ComputeScale();

		void			SetTarget(float x, float y);

		void			SetPosition(float x, float y);
		void			GetPosition(float& x, float& y);

		void			SpawnBomb();
		void			IncMaxBomb();
		void			IncBomb();
		void			DecBomb();

		bool			CanDestroy();
		

	protected:
		void			BuildAnimation();

	private:
		float			m_x;
		float			m_y;

		float			m_speed;
		size_t			m_bombDistance;

		float			m_blockTarget_x;
		float			m_blockTarget_y;
		float			m_direction_x;
		float			m_direction_y;

		size_t			m_currentBomb;
		size_t			m_maxBomb;

		sf::Color		m_color;

		Animator		m_animator;
		sf::Clock		m_deltaClock;

	};


}