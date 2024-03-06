#include "App.h"
#include <iostream>

App::App() {
	this->initWindow();
	
	this->initBoard();
	this->initFonts();
	this->initText();
}

void App::render() {
	this->window.clear();

	this->drawMap();

	this->window.draw(this->text);


	this->window.display();
}

void App::drawMap() {
	for (int x = 0; x < GLOBALS::MAP::MAP_SIZE; x++)
	{
		for (int y = 0; y < GLOBALS::MAP::MAP_SIZE; y++)
		{
			this->tileMap[x][y].rect.setFillColor(this->tileMap[x][y].color);
			this->window.draw(this->tileMap[x][y].rect);
		}
	}
}


void App::initWindow() {
	this->window.create(sf::VideoMode(GLOBALS::SCREEN::WIDTH, GLOBALS::SCREEN::HEIGHT), "A*");
}

void App::initBoard() {
	//this->tileMap.resize(GLOBALS::MAP::MAP_SIZE, std::vector < sf::RectangleShape>());
	//this->tileMap.

	this->tileMap.resize(GLOBALS::MAP::MAP_SIZE, std::vector <GLOBALS::NODE::Node>());

	for (int x = 0; x < GLOBALS::MAP::MAP_SIZE; x++)
	{
		this->tileMap[x].resize(GLOBALS::MAP::MAP_SIZE, GLOBALS::NODE::Node());

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
			this->tileMap[x][y] = node;

		}
	}
}




void App::initFonts() {
	this->font.loadFromFile("Fonts/RobotoMono-Regular.ttf");
}

void App::initText() {
	this->text.setCharacterSize(15.f);
	this->text.setFillColor(sf::Color::Black);
	this->text.setFont(this->font);
	this->text.setPosition(30, 38.f);
}

void App::handleEvents() {
	while (this->window.pollEvent(this->event)) {
		switch (this->event.type) {
		case sf::Event::Closed: { this->window.close(); }
		}
	}
}

void App::updateText() {
	std::ostringstream ss;
	ss << "Mode: A*" << std::endl << "Diagonals: " << "false" << std::endl;
	//ss << "Hold S + Right Click to Select Start" << std::endl << "Hold E + Right Click to Select End" << std::endl << "ENTER to begin simulation";
//	ss << "GRID:" << " " << this->mousePosGrid.x << " " << this->mousePosGrid.y << std::endl << "TEST: 5";
	this->text.setString(ss.str());
}

void App::updateMousePositions() {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(this->window);
	this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);

	// calculates the grid positions
	if (mousePosView.x >= 0.f)
	{
		mousePosGrid.x = mousePosView.x / GLOBALS::MAP::CELL_SIZE_U;
	}
	if (mousePosView.y >= 0.f)
	{
		mousePosGrid.y = mousePosView.y / GLOBALS::MAP::CELL_SIZE_U;
	}
}

bool App::checkCellValid() {
	return (this->mousePosGrid.x >= 0 && this->mousePosGrid.x <= (GLOBALS::SCREEN::WIDTH / GLOBALS::MAP::CELL_SIZE) - 1 && this->mousePosGrid.y >= 0 && this->mousePosGrid.y <= (GLOBALS::SCREEN::HEIGHT / GLOBALS::MAP::CELL_SIZE) - 1);
}

void App::clearAllCells() {
	this->initBoard();
}

void App::startAstar() {
	Astar pathfinder = Astar(*this);
	pathfinder.pathfind(this->tileMap, this->curStart.x, this->curStart.y, this->curEnd.x, this->curEnd.y);
	//this->markPaths();
}



void App::updateCellData() {

	//std::cout << this->drawState;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { // draw
		if (checkCellValid()) {

			switch (this->drawState) {
			case start:
				// clear old selection
				this->tileMap[this->curStart.x][this->curStart.y].color = sf::Color::White;
				// draw node green
				this->tileMap[this->mousePosGrid.x][this->mousePosGrid.y].color = sf::Color::Green;
				// update the node start properties
				this->tileMap[this->mousePosGrid.x][this->mousePosGrid.y].start = true;

				this->curStart.x = mousePosGrid.x;
				this->curStart.y = mousePosGrid.y;


				break;
			case end:
				// clear old selection
				this->tileMap[this->curEnd.x][this->curEnd.y].color = sf::Color::White;
				// draw node red
				this->tileMap[this->mousePosGrid.x][this->mousePosGrid.y].color = sf::Color::Red;
				// update the nodes end properties 
				this->tileMap[this->mousePosGrid.x][this->mousePosGrid.y].end = true;


				this->curEnd.x = mousePosGrid.x;
				this->curEnd.y = mousePosGrid.y;



				break;
			case border:
				this->tileMap[this->mousePosGrid.x][this->mousePosGrid.y].color = sf::Color::Black;
				// update the nodes traversable properties
				this->tileMap[this->mousePosGrid.x][this->mousePosGrid.y].traversable = false;
				break;


			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { // start simulation ** TODO: put this is a seperate function with buttons
		this->startAstar();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // select start position
		this->drawState = start;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { // select end position
		this->drawState = end;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) { // select borders position
		this->drawState = border;
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
	return this->window.isOpen();
}





