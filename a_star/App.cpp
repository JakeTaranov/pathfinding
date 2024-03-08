#include "App.h"
#include <iostream>

App::App() {
	this->initWindow();
	
	this->initBoard();
	this->initFonts();
	this->initText();
}

void App::render() {
	this->m_window.clear();

	this->drawMap();

	this->m_window.draw(this->m_text);


	this->m_window.display();
}

void App::drawMap() {
	for (int x = 0; x < GLOBALS::MAP::MAP_SIZE; x++)
	{
		for (int y = 0; y < GLOBALS::MAP::MAP_SIZE; y++)
		{
			this->m_tileMap[x][y].rect.setFillColor(this->m_tileMap[x][y].color);
			this->m_window.draw(this->m_tileMap[x][y].rect);
		}
	}
}


void App::initWindow() {
	this->m_window.create(sf::VideoMode(GLOBALS::SCREEN::WIDTH, GLOBALS::SCREEN::HEIGHT), "A*");
}

void App::initBoard() {
	//this->tileMap.resize(GLOBALS::MAP::MAP_SIZE, std::vector < sf::RectangleShape>());
	//this->tileMap.

	this->m_tileMap.resize(GLOBALS::MAP::MAP_SIZE, std::vector <GLOBALS::NODE::Node>());

	for (int x = 0; x < GLOBALS::MAP::MAP_SIZE; x++)
	{
		this->m_tileMap[x].resize(GLOBALS::MAP::MAP_SIZE, GLOBALS::NODE::Node());

		for (int y = 0; y < GLOBALS::MAP::MAP_SIZE; y++)
		{
			GLOBALS::NODE::Node node;
			// set the display attributes
			node.rect.setSize(sf::Vector2f(GLOBALS::MAP::CELL_SIZE, GLOBALS::MAP::CELL_SIZE));
			node.rect.setFillColor(node.color);
			node.rect.setOutlineThickness(1.f);
			node.rect.setOutlineColor(sf::Color::Black);
			node.rect.setPosition(x * GLOBALS::MAP::CELL_SIZE, y * GLOBALS::MAP::CELL_SIZE); 

			node.row = y;
			node.col = x;
			// add node to tile map
			this->m_tileMap[x][y] = node;

		}
	}
}




void App::initFonts() {
	this->m_font.loadFromFile("Fonts/RobotoMono-Regular.ttf");
}

void App::initText() {
	this->m_text.setCharacterSize(15.f);
	this->m_text.setFillColor(sf::Color::Black);
	this->m_text.setFont(this->m_font);
	this->m_text.setPosition(30, 38.f);
}

void App::handleEvents() {
	while (this->m_window.pollEvent(this->m_event)) {
		switch (this->m_event.type) {
		case sf::Event::Closed: { this->m_window.close(); }
		}
	}
}

void App::updateText() {
	std::ostringstream ss;
	ss << "Mode: A*" << std::endl << "Diagonals: " << std::boolalpha << this->m_diagonals << std::endl;
	ss << "Draw Mode: " << this->m_drawStateMap[this->m_drawState] << std::endl;

	//ss << "Hold S + Right Click to Select Start" << std::endl << "Hold E + Right Click to Select End" << std::endl << "ENTER to begin simulation";
//	ss << "GRID:" << " " << this->mousePosGrid.x << " " << this->mousePosGrid.y << std::endl << "TEST: 5";
	this->m_text.setString(ss.str());
}

void App::updateMousePositions() {
	this->m_mousePosScreen = sf::Mouse::getPosition();
	this->m_mousePosWindow = sf::Mouse::getPosition(this->m_window);
	this->m_mousePosView = m_window.mapPixelToCoords(this->m_mousePosWindow);

	// calculates the grid positions
	if (m_mousePosView.x >= 0.f)
	{
		m_mousePosGrid.x = m_mousePosView.x / GLOBALS::MAP::CELL_SIZE_U;
	}
	if (m_mousePosView.y >= 0.f)
	{
		m_mousePosGrid.y = m_mousePosView.y / GLOBALS::MAP::CELL_SIZE_U;
	}
}

bool App::checkCellValid() {
	return (this->m_mousePosGrid.x >= 0 && this->m_mousePosGrid.x <= (GLOBALS::SCREEN::WIDTH / GLOBALS::MAP::CELL_SIZE) - 1 && this->m_mousePosGrid.y >= 0 && this->m_mousePosGrid.y <= (GLOBALS::SCREEN::HEIGHT / GLOBALS::MAP::CELL_SIZE) - 1);
}

void App::clearAllCells() {
	this->initBoard();
}

void App::startAstar() {
	Astar pathfinder = Astar(*this);
	pathfinder.pathfind(this->m_tileMap, this->m_curStart.x, this->m_curStart.y, this->m_curEnd.x, this->m_curEnd.y, this->m_diagonals);
	//this->markPaths();
}



void App::updateCellData() {

	//std::cout << this->drawState;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { // draw
		if (checkCellValid()) {

			switch (this->m_drawState) {
			case start:
				// clear old selection
				this->m_tileMap[this->m_curStart.x][this->m_curStart.y].color = sf::Color::White;
				// draw node green
				this->m_tileMap[this->m_mousePosGrid.x][this->m_mousePosGrid.y].color = sf::Color::Green;
				// update the node start properties
				this->m_tileMap[this->m_mousePosGrid.x][this->m_mousePosGrid.y].start = true;

				this->m_curStart.x = m_mousePosGrid.x;
				this->m_curStart.y = m_mousePosGrid.y;


				break;
			case end:
				// clear old selection
				this->m_tileMap[this->m_curEnd.x][this->m_curEnd.y].color = sf::Color::White;
				// draw node red
				this->m_tileMap[this->m_mousePosGrid.x][this->m_mousePosGrid.y].color = sf::Color::Red;
				// update the nodes end properties 
				this->m_tileMap[this->m_mousePosGrid.x][this->m_mousePosGrid.y].end = true;


				this->m_curEnd.x = m_mousePosGrid.x;
				this->m_curEnd.y = m_mousePosGrid.y;

				break;
			case border:
				this->m_tileMap[this->m_mousePosGrid.x][this->m_mousePosGrid.y].color = sf::Color::Black;
				// update the nodes traversable properties
				this->m_tileMap[this->m_mousePosGrid.x][this->m_mousePosGrid.y].traversable = false;
				break;


			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { // start simulation ** TODO: put this is a seperate function with buttons
		this->startAstar();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // select start position
		this->m_drawState = start;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { // select end position
		this->m_drawState = end;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) { // select borders position
		this->m_drawState = border;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // select diagonals 
		this->m_diagonals = !this->m_diagonals;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) { // clear all cells
		this->clearAllCells();
	}
}



void App::update() {
	this->handleEvents();
	this->updateMousePositions();
	this->updateCellData();
	this->updateText();
}


bool App::isRunning() {
	return this->m_window.isOpen();
}





