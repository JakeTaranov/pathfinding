#pragma once
#include <SFML/Graphics.hpp>
#include "globals.hpp"

class App;

class Astar
{
private:
	App& app;

public: 
	Astar(App& appInstance);
	int x;
	std::vector<std::vector<int>> findAdjacentCells(int x, int y, std::vector<std::vector<GLOBALS::NODE::Node>> tileMap, bool diagonals);
	double calculateDistance(GLOBALS::NODE::Node* curNode, GLOBALS::NODE::Node* destNode);
	void reconstructPath(std::map<GLOBALS::NODE::Node*, GLOBALS::NODE::Node*>& cameFrom, std::vector<std::vector<GLOBALS::NODE::Node>>& tileMap, GLOBALS::NODE::Node* curNode);
	void pathfind(std::vector<std::vector<GLOBALS::NODE::Node>>& tileMap, int sx, int sy, int ex, int ey, bool diagonals);
};


