#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "GeneralUtilities.cpp"
#include "Board.cpp"
#include "CurveLine.cpp"
#include "Background.cpp"

#include "GameScreen.hpp"

GameScreen::GameScreen(int x, int y, int cross, int numOfPices, sf::RenderWindow & window) :
    window(window),
    background("../Textures/grass.jpg", "../Textures/wood.jpg"),
    scoreText(),
    board(&window, sf::Vector2f((x - cross * (std::min(x, y) / (cross + 2))) / 2, (y - cross * (std::min(x, y) / (cross + 2))) / 2), std::min(x, y) / (cross + 2), cross, numOfPices){
    int size = std::min(x, y) / (cross + 2);
    int sizex = (x - cross * size) / 2;
    int sizey = (y - cross * size) / 2;
    windowTexture.create(x, y);
    windowSprite.setTexture(windowTexture);
    background.create(sf::Vector2i(x, y), board.start, size, cross);
    initScoreText();
   // SetCenterPosition(sf::FloatRect(x,y,sizex,sizey));
}

void GameScreen::start() {

    board.init();
    sf::Vector2f cursor;
    sf::Event event;
    int cflag = 0;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cursor = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (board.isIn(cursor)) {
                        Cell * cell = board.cellFromPosition(cursor);
                        highlight(cell->getType());
                        line.addCell(cell);
                        cflag = 1;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int p = line.endConection(3);
                    if (p) {
                        Score += std::pow(1.6, p);
                        updateScoreText();
                    }
                    cleanStaticTexture();
                    cflag = 0;
                    board.update();
                }
            }
            if (event.type == sf::Event::Resized) {
                unsigned int x = event.size.width, y = event.size.height;
                board.resize(x, y);
                windowTexture.create(x, y);
                windowSprite.setTextureRect(sf::IntRect(0, 0, x, y));
                background.create(static_cast<sf::Vector2i> (window.getSize()), board.start, board.cellSize, board.num);
            }
            if (cflag == 1) {
                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2f cursor(event.mouseMove.x, event.mouseMove.y);
                    if (board.isIn(cursor)) {
                        Cell* cell = board.cellFromPosition(cursor);
                        if (!cell->wasVisited() && line.type() == cell->getType() && calcDist(cursor, line.back()->getCenter()) < hypot(cell->getSize(), cell->getSize()) + 1) {
                            line.addCell(cell);
                        }
                    }
                }
            }
        }
        if (cflag) staticDraw();
        else draw();
    }
}

void GameScreen::highlight(int type) {
    window.clear(sf::Color(0, 0, 0, 0));
    background.draw(window);
    board.draw();
    windowTexture.update(window);
    windowSprite.setColor(sf::Color(90, 90, 90, 255));
    window.clear();
    window.draw(windowSprite);
    board.draw(type);
    windowTexture.update(window);
    windowSprite.setColor(sf::Color(255, 255, 255, 255));

}

void GameScreen::cleanStaticTexture() {
    window.clear();
    windowTexture.update(window);
}

void GameScreen::staticDraw() {
    window.clear();
    window.draw(windowSprite);
    line.draw(window);
    window.draw(scoreText);
    window.display();
}

void GameScreen::draw() {
    window.clear(sf::Color(0, 0, 0, 0));
    background.draw(window);
    board.draw();
    window.draw(scoreText);
    window.display();
}

void GameScreen::initScoreText(){
    scoreFont.loadFromFile("../arial.ttf");
    scoreText.setFont( scoreFont );
    scoreText.setString("00000000");
    Score = 0;
}

void GameScreen::updateScoreText(){
    scoreText.setString( std::to_string(Score) );
}

void GameScreen::SetCenterPosition(const sf::FloatRect & bounds){
    sf::FloatRect textBounds = scoreText.getGlobalBounds();
    float x = bounds.left + (bounds.width - textBounds.width)/2;
    float y = bounds.top + (bounds.height -textBounds.height)/2;
    scoreText.setPosition( x, y  );
}
