#pragma once

#include "entity.h"

#include "animator.h"


namespace Client
{
	class Player;

	class Bomb : public Entity
	{
	public:
		Bomb();
		~Bomb();

		void Init();
		void Tick();
		void Term();

		bool CanDestroy();
		Player*	GetOwner();

		void SetOwner(Player* player);

		bool IsWalkable() { return false; }

		void SetTimeToExplode(float timeToExplode);
		void SetDistance(size_t distance);

		void Draw(sf::RenderWindow* window);

		void SetPosition(float x, float y);
		void GetPosition(float& x, float& y);

	protected:
		void Explode(float center_x, float center_y, size_t distance, int direction);

	private:
		float		m_x;
		float		m_y;
		bool		m_isOver;
		Player*		m_owner;
		Animator	m_animator;
		size_t		m_distance;
		float		m_timeToExplode;
		sf::Clock	m_deltaClock;
	};

}