#pragma once

#include "entity.h"

#include "SFML/Graphics.hpp"
#include <vector>

namespace Client
{
	struct Cell 
	{
		sf::Sprite sprite;
		size_t x;
		size_t y;
		bool isWalkable;
		bool isDestroyable;
	};

	class World
	{
	public:
		explicit World(size_t x, size_t y);
		~World();

		virtual void	Init();
		virtual void	Tick();
		virtual void	Term();

		virtual void	Draw(sf::RenderWindow* window);

		void			ComputeScale();

		void			GetSize(size_t& x, size_t& y);

		void			GetPixelToBlock(float x, float y, size_t& x_out, size_t& y_out);
		void			GetBlockToPixel(size_t x, size_t y, float& x_out, float& y_out);

		bool			IsBlockWalkable(size_t x, size_t y);
		bool			IsBlockWalkable(float x, float y);

		bool			IsBlockDestroyable(size_t x, size_t y);
		bool			IsBlockDestroyable(float x, float y);

		void			GetUpBlock(size_t x, size_t y, size_t& x_out, size_t& y_out);
		void			GetDownBlock(size_t x, size_t y, size_t& x_out, size_t& y_out);
		void			GetLeftBlock(size_t x, size_t y, size_t& x_out, size_t& y_out);
		void			GetRightBlock(size_t x, size_t y, size_t& x_out, size_t& y_out);

		void			SetSeed();

	protected:
		void			GetCoordinatesFromVector(size_t i, size_t& x, size_t& y);

	protected:
		size_t m_x;
		size_t m_y;

		typedef std::vector<struct Cell> cells_t;
		cells_t m_cells;

	};



}