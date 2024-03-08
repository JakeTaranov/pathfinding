#pragma once

#include "globals.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Astar.h"
class App
{
private:
	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Text m_text;
	sf::Event m_event;
	std::ostringstream m_grid_string;


	sf::Vector2i m_mousePosScreen;
	sf::Vector2i m_mousePosWindow;
	sf::Vector2f m_mousePosView;
	sf::Vector2i m_mousePosGrid;

	sf::Vector2i m_curStart = sf::Vector2i(0,0); // keeps track of previous start x, y coords so we cant redraw the start
	sf::Vector2i m_curEnd = sf::Vector2i(0,0); // similar as above

	enum selectionStates {
		start,
		end,
		border,
	};

	//sf::Vector3<sf::String> drawStateMap = sf::Vector3<sf::String>("Start", "End", "Borders");


	const char* m_drawStateMap[3] = { "Start", "End", "Borders" };

	selectionStates m_drawState = border;

	bool m_diagonals = false;

	std::vector<std::vector<GLOBALS::NODE::Node>> m_tileMap;


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

