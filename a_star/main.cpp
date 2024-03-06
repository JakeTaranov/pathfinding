#include "app.h"


int main()
{
	App app;

	while (app.isRunning())
	{
		app.update();

		app.render();
	}

	return EXIT_SUCCESS;
}
























































//void update_board(std::vector<std::vector<sf::RectangleShape>> &tileMap)
//{
//
//	tileMap[1][3].setFillColor(sf::Color::Blue);
//	tileMap[1][4].setFillColor(sf::Color::Blue);
//	tileMap[1][5].setFillColor(sf::Color::Blue);
//
//}
//
//int main() {
//
////	const int WIDTH = 1920;
//
//	sf::Vector2f startPosition;
//	sf::Vector2f endPosition;
//
//	sf::Vector2f prevStart = sf::Vector2f(0.0, 0.0);
//	sf::Vector2f prevEnd = sf::Vector2f(0.0, 0.0);
//
//	// init game
//	float gridSizeF = 10;
//	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
//	float dt = 0.f;
//	sf::Vector2i mousePosScreen = sf::Mouse::getPosition();
//	sf::Vector2i mousePosWindow;
//	sf::Vector2f mousePosView;
//	sf::Vector2i mousePosGrid;
//	sf::Font font;
//	font.loadFromFile("Fonts/RobotoMono-Regular.ttf");
//	sf::Text text;
//	text.setCharacterSize(15.f);
//	text.setFillColor(sf::Color::Black);
//	text.setFont(font);
//	text.setPosition(30, 30.f);
//	text.setString("TEST");
//
//	// 0 = black borders, 1 = Start, 2 = Finish
//	int selectDrawType = 0;
//
//	// init window
//	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Tab");
//	window.setFramerateLimit(120);
//
//
//	// init view
//	sf::View view;
//	view.setSize(1000.f, 1000.f);
//	view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
//	float viewSpeed = 100.f;
//
//	// init game elements 
//	sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));
//	const int mapSize = 100;
//
//	std::vector<std::vector<sf::RectangleShape>> tileMap;
//	
//	tileMap.resize(mapSize, std::vector<sf::RectangleShape>());
//
//	for (int x = 0; x < mapSize; x++)
//	{
//		tileMap[x].resize(mapSize, sf::RectangleShape());
//		for (int y = 0; y < mapSize; y++)
//		{
//			tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
//			tileMap[x][y].setFillColor(sf::Color::White);
//			tileMap[x][y].setOutlineThickness(1.f);
//			tileMap[x][y].setOutlineColor(sf::Color::Black);
//			tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
//		}
//	}
//
//
//	sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));
//	tileSelector.setFillColor(sf::Color::Transparent);
//	tileSelector.setOutlineThickness(1.f);
//	tileSelector.setOutlineColor(sf::Color::Green);
//
//	bool isScrolling = false;
//	sf::Event event;
//	while (window.isOpen())
//	{
//
//		// update mouse positions
//		mousePosScreen = sf::Mouse::getPosition();
//		mousePosWindow = sf::Mouse::getPosition(window);
//		window.setView(view);
//		mousePosView = window.mapPixelToCoords(mousePosWindow);
//
//		// calculates grid positions
//		if (mousePosView.x >= 0.f)
//		{
//			mousePosGrid.x = mousePosView.x / gridSizeU;
//		}
//		if (mousePosView.y >= 0.f)
//		{
//			mousePosGrid.y = mousePosView.y / gridSizeU;
//		}
//
//		// update game elements
//		tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF); // snaps mouse to grid
//
//
//
//		// update ui
//		std::ostringstream ss;
//		ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
//			<< "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
//			<< "View: " << mousePosView.x << " " << mousePosView.y << "\n"
//			<< "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
//
//		text.setString(ss.str());
//
//
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//		}
//		// update input 
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) // set the draw type to borders (0)
//		{
//			selectDrawType = 0;
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) // set the draw type to begin (1)
//		{
//			selectDrawType = 1;
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) // set the draw type to end (2)
//		{
//			selectDrawType = 2;
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // set the draw type to end (2)
//		{
//			update_board(tileMap);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) // Clear board and reset selections
//		{
//			for (int x = 0; x < mapSize; x++)
//			{
//				tileMap[x].resize(mapSize, sf::RectangleShape());
//					for (int y = 0; y < mapSize; y++)
//					{
//						tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
//							tileMap[x][y].setFillColor(sf::Color::White);
//							tileMap[x][y].setOutlineThickness(1.f);
//							tileMap[x][y].setOutlineColor(sf::Color::Black);
//							tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
//					}
//			}
//
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) // run simulation
//		{
//			search(tileMap, startPosition.x, startPosition.y, endPosition.x, endPosition.y);
//		}
//		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) // draw
//		{
//			// check to make sure grid pos is in bound
//			if (mousePosGrid.x >= 0 && mousePosGrid.x < view.getSize().x / gridSizeF && mousePosGrid.y >= 0 && mousePosGrid.y < view.getSize().x / gridSizeF)
//			{
//				// convert to switch ???
//				// draw black borders
//				if (selectDrawType == 0)
//				{
//					tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(sf::Color::Black);
//				}
//				// draw green start
//				else if (selectDrawType == 1)
//				{
//					// clear old greens start
//					tileMap[prevStart.x][prevStart.y].setFillColor(sf::Color::White);
//
//					startPosition.x = mousePosGrid.x;
//					startPosition.y = mousePosGrid.y;
//
//					tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(sf::Color::Green);
//
//					//update prev
//					prevStart.x = mousePosGrid.x;
//					prevStart.y = mousePosGrid.y;
//				}
//				// draw red finish
//				else if (selectDrawType == 2)
//				{
//					// clear old reds finish
//					tileMap[prevEnd.x][prevEnd.y].setFillColor(sf::Color::White);
//
//
//					endPosition.x = mousePosGrid.x;
//					endPosition.y = mousePosGrid.y;
//					tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(sf::Color::Red);
//
//					//update prev
//					prevEnd.x = mousePosGrid.x;
//					prevEnd.y = mousePosGrid.y;
//				}
//			}
//		}
//		// render
//		window.clear();
//
//		// render game elements
//
//		for (int x = 0; x < mapSize; x++)
//		{
//			for (int y = 0; y < mapSize; y++)
//			{
//				window.draw(tileMap[x][y]);
//			}
//		}
//		window.draw(tileSelector);
//
//		// render ui
//		window.draw(text);
//
//		// done drawing
//		window.display();
//
//	}
//	return 0;
//}