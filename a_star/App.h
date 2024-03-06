#pragma once

#include "globals.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Astar.h"
class App
{
private:
	sf::RenderWindow window;
	sf::Font font;
	sf::Text text;
	sf::Event event;
	std::ostringstream grid_string;


	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	sf::Vector2i curStart = sf::Vector2i(0,0); // keeps track of previous start x, y coords so we cant redraw the start
	sf::Vector2i curEnd = sf::Vector2i(0,0); // similar as above

	enum selectionStates {
		start,
		end,
		border,
	};

	selectionStates drawState = border;


	std::vector<std::vector<GLOBALS::NODE::Node>> tileMap;


	void initWindow();
	void initBoard();
	void initFonts();
	void initText();

	void handleEvents();

	void updateMousePositions();
	void updateText();
	void updateCellData();
	void markPaths();
	void drawMap();

	bool checkCellValid();
	void clearAllCells();
	void startAstar();
	
	


public:
	App();
	void update();
	void render();
	bool isRunning();
};

