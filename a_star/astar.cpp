#include "globals.hpp"
#include "Astar.h"
#include "App.h"
#include <iostream>
#include <queue>

// TODO
// - figure out pointer stuff 
// - update as we go through a*, keep track of closed and open nodes -> pass astar a reference to the window OR create a draw map function in App and call from reference of app.
// - possible performace increase, check to make sure we are not looking at a already visited cell
// - figure out why it is so slow
// - add diagonals
//
//


Astar::Astar(App& appInstance) : app(appInstance) {}


// returns the adjacents cells of (x, y) 
// TODO: Add diagonal
std::vector<std::vector<int>> Astar::findAdjacentCells(int col, int row, std::vector<std::vector<GLOBALS::NODE::Node>> tileMap, bool diagonals) {
	std::vector<std::vector<int>> adjCells;


	//if (diagonals) {
	//	// diag top left
	//	if (row - 1 >= 0 && col - 1 >= 0 && tileMap[col - 1][row - 1].traversable) {
	//		adjCells.push_back({ row - 1 , col - 1 });
	//	}
	//	// diag top right
	//	if (row + 1 >= 0 && col - 1 >= 0 && tileMap[col - 1][row + 1].traversable) {
	//		adjCells.push_back({ row + 1 , col - 1 });
	//	}
	//	// diag bottom left
	//	if (row - 1 >= 0 && col + 1 >= 0 && tileMap[col + 1][row - 1].traversable) {
	//		adjCells.push_back({ row - 1 , col + 1 });
	//	}
	//	// diag bottom right
	//	if (row + 1 >= 0 && col + 1 >= 0 && tileMap[col + 1][row + 1].traversable) {
	//		adjCells.push_back({ row + 1 , col + 1 });
	//	}
	//}
	// left
	if (row - 1 >= 0 && tileMap[col][row-1].traversable) {
		adjCells.push_back({ row - 1 , col });
	}
	// right
	if (row + 1 < GLOBALS::MAP::MAP_SIZE && tileMap[col][row+1].traversable) {
		adjCells.push_back({ row + 1, col });
	}
	// top
	if (col - 1 >= 0 && tileMap[col-1][row].traversable) {
		adjCells.push_back({ row, col - 1 });
	}
	// bottom
	if (col + 1 < GLOBALS::MAP::MAP_SIZE && tileMap[col+1][row].traversable) {
		adjCells.push_back({ row, col + 1 });
	}

	return adjCells;
}

double Astar::calculateDistance(GLOBALS::NODE::Node* curNode, GLOBALS::NODE::Node* destNode) {
	return std::sqrt(std::pow(curNode->row - destNode->row, 2) + std::powf(curNode->col - destNode->col, 2));
}


void Astar::reconstructPath(std::map<GLOBALS::NODE::Node*, GLOBALS::NODE::Node*>& cameFrom, std::vector<std::vector<GLOBALS::NODE::Node>>& tileMap, GLOBALS::NODE::Node* current) {
	std::vector<GLOBALS::NODE::Node> path;
	GLOBALS::NODE::Node* cur = current;
	while (cameFrom.find(cur) != cameFrom.end()) {
		tileMap[cur->col][cur->row].color = sf::Color::Yellow; // path
		cur = cameFrom.at(cur);
	}

}

struct CompareNodes {
	// Comparison function for priority_queue
	bool operator()(const GLOBALS::NODE::Node* a, const GLOBALS::NODE::Node* b) const {
		return a->fCost > b->fCost;
	}
};

// note that x and y are flipped
void Astar::pathfind(std::vector<std::vector<GLOBALS::NODE::Node>>& tileMap, int sCol, int sRow, int eCol, int eRow) {

	//std::vector<GLOBALS::NODE::Node*> openList;
	std::vector<GLOBALS::NODE::Node*> closedList;
	std::priority_queue<GLOBALS::NODE::Node*, std::vector<GLOBALS::NODE::Node*>, CompareNodes> openList;

	GLOBALS::NODE::Node* endNode = &tileMap[eCol][eRow];

	bool diagonals = true;
	tileMap[sCol][sRow].gCost = 0;
	tileMap[sCol][sRow].fCost = 0;

	openList.push(&tileMap[sCol][sRow]);

//	std::cout << openList[0]->gCost << std::endl;
	std::vector<std::vector<int>> adjCellsOfsRowsCol;
	std::map<GLOBALS::NODE::Node*, GLOBALS::NODE::Node*> cameFrom;
	bool found = false;

	std::cout << "STARTING" << std::endl;

	while (openList.size() > 0) {


		// using min heap this gives us the node with the current lowst fScore
		GLOBALS::NODE::Node* curNode = openList.top(); 
		openList.pop(); // then remove it from the open set
		

		tileMap[curNode->col][curNode->row].traversable = false;

		// dont want to color the starting node
		if (!tileMap[curNode->col][curNode->row].start) {
			tileMap[curNode->col][curNode->row].color = sf::Color::Blue; // visited
		}

		//std::cout << openList.size() << std::endl;
		for (auto& adjCell : Astar::findAdjacentCells(curNode->col, curNode->row, tileMap, diagonals)) {

		
			GLOBALS::NODE::Node* adjCellTileMap = &tileMap[adjCell[1]][adjCell[0]];

			// check if we are at the end node
			if ((adjCellTileMap->row == eRow) && (adjCellTileMap->col == eCol)) {
				// TODO: add path reconstruction & end break loop
				this->reconstructPath(cameFrom, tileMap, curNode);
				found = true;
				break;
			}

	;
			if (adjCellTileMap->traversable) {
				double curGCost = curNode->gCost + this->calculateDistance(curNode, adjCellTileMap);

				
				tileMap[adjCellTileMap->col][adjCellTileMap->row].color = sf::Color::Cyan;

				if (curGCost < adjCellTileMap->gCost) {
					//std::cout << adjCellTileMap.col << adjCellTileMap.row << std::endl;
					cameFrom[adjCellTileMap] = curNode;

					adjCellTileMap->parent = curNode;
					adjCellTileMap->gCost = curGCost;
					adjCellTileMap->hCost = this->calculateDistance(adjCellTileMap, endNode);
					adjCellTileMap->fCost = adjCellTileMap->gCost + adjCellTileMap->hCost;

					// check if not in open set and add to openset
					if (!adjCellTileMap->openSet) {
						adjCellTileMap->openSet = true;
						openList.push(adjCellTileMap);

					}
				}
			}
		}
		if (found) {
			break;
		}
		app.render();
	}
}