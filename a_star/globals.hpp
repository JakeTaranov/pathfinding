#pragma once
#include <SFML/Graphics.hpp>

namespace GLOBALS
{
	namespace MAP
	{
		constexpr int CELL_SIZE = 20;
		constexpr unsigned CELL_SIZE_U = static_cast<unsigned>(CELL_SIZE);
		constexpr int MAP_SIZE = 100;

		
		enum Cell
		{
			Visited,
			Empty,
			Wall,
			Start,
			Finish,
			Path
		};

	}
	
	namespace SCREEN
	{
		constexpr int WIDTH = 1000;
		constexpr int HEIGHT = 1000;
	}

	namespace NODE
	{
		struct Node {
			int row;
			int col;
			double fCost = std::numeric_limits<double>::max();
			double gCost = std::numeric_limits<double>::max();;
			double hCost = -1;
			bool traversable = true;
			bool openSet = false;
			bool path = false;
			bool start = false;
			bool end = false;
			Node* parent = nullptr;
			sf::RectangleShape rect; // for display
			sf::Color color = sf::Color::White;

			bool operator<(const Node& other) const {
				return gCost < other.gCost;
			}
			bool operator==(const Node& other) const {
				// You can customize the equality logic based on your requirements
				return (row == other.row) && (col == other.col);
			}

		};
	}
}