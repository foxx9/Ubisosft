#pragma once

#include <map>
#include <vector>

#include "SFML/Graphics.hpp"

namespace Client
{
	struct Frame
	{
		sf::Sprite sprite;
		float time;
	};

	class Animator
	{
	public:
		Animator();
		~Animator();

		void			Play(const char* action);
		void			Play(unsigned long action);

		// Samy: totaly good practice
		void			AddFrame(const char* action, const char* texture, float time);
		void			AddFrame(unsigned long action, unsigned long texture, float time);
		void			AddFrame(const char* action, const char* texture, sf::Color& color, float time);
		void			AddFrame(unsigned long action, unsigned long texture, sf::Color& color, float time);

		void			Tick();

		void			Reset();

		sf::Sprite*		GetCurrent();

		void			ComputeScale();

	protected:
		typedef std::vector<struct Frame> frames_t;
		typedef std::map<unsigned long, frames_t> animations_t;

		animations_t	m_animation;

		struct Frame*	m_currentFrame;
		unsigned long	m_currentAnimationID;
		size_t			m_currentIndex;
		sf::Clock		m_deltaClock;
	};
}