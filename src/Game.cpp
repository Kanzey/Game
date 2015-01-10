#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "GeneralUtilities.cpp"
#include "Board.cpp"
#include "CurveLine.cpp"
#include "Background.cpp"

class Game{
public:
        Background background;
	sf::RenderWindow window;
	sf::Texture windowTexture, backgroundTexture;
	sf::Sprite windowSprite;
        CurveLine line;
	Board board;
	Game( int x, int y, int cross, int numOfPices) : background("../Textures/grass.jpg", "../Textures/wood.jpg") {
		window.create(sf::VideoMode(x ,y), "Game" );
		int size =	std::min(x,y)/(cross+2);
                int sizex = (x-cross*size)/2;
                int sizey = (y-cross*size)/2; 
		board = Board(&window, sf::Vector2f(sizex,sizey), size, cross, numOfPices);
		windowTexture.create(x,y);
		windowSprite.setTexture(windowTexture);
                background.create( sf::Vector2i(x,y) ,board.start , size  ,cross);
	}
        //function handling game events and response to them;
	void start(){
            unsigned long long points = 0;
		board.init();
		//board.update();	
            sf::Vector2f cursor;
		sf::Event event;
		int cflag = 0;
		while(window.isOpen() ){
			while(window.pollEvent(event)){
				if(event.type == sf::Event::Closed){
					window.close();
				}
				if(event.type == sf::Event::MouseButtonPressed){
                                    if( event.mouseButton.button  == sf::Mouse::Left ){
                                        cursor = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					if( board.isIn(cursor)){
                                            Cell * cell = board.cellFromPosition(cursor);
                                            highlight( cell->getType() );
                                            line.addCell(cell);
                                            cflag = 1;
                                        }
                                    }
				}
				if(event.type == sf::Event::MouseButtonReleased){
                                    if( event.mouseButton.button == sf::Mouse::Left ){
                                        int p = line.endConection(3);
                                        points += std::pow(1.6,p);
                                        std::cout << points << std::endl;
                                        cleanStaticTexture();
					cflag = 0;
                                        board.update();
                                    }
				}
                                if(event.type == sf::Event::Resized){
                                    unsigned int x = event.size.width, y = event.size.height;
                                        board.resize(x, y);
                                        windowTexture.create(x, y);
                                        windowSprite.setTextureRect(sf::IntRect(0, 0, x, y));
                                        background.create( static_cast<sf::Vector2i>( window.getSize() ), board.start, board.cellSize, board.num);
                                }
                                if( cflag == 1)
                                   if(event.type == sf::Event::MouseMoved)
                                    {
                                        sf::Vector2f cursor(event.mouseMove.x, event.mouseMove.y);
                                        if(board.isIn(cursor)){
                                            Cell* cell = board.cellFromPosition(cursor);
                                            if( !cell->wasVisited() && line.type() == cell->getType() && calcDist(cursor,line.back()->getCenter()) < hypot(cell->getSize(),cell->getSize())+1 ){
                                                line.addCell(cell);
                                            }
                                        }
                                }
			}
			if( cflag ) staticDraw();
			else 		draw();
		}
	}
        //function higlight elements of given type and store that image in windowTexture; 
        void highlight(int type){
            window.clear(sf::Color(0,0,0,0));
            background.draw( window );
            board.draw();
            windowTexture.update( window );
            windowSprite.setColor(sf::Color(90,90,90,255));
            window.clear();
            window.draw(windowSprite);
            board.draw(type);
            windowTexture.update( window );
            windowSprite.setColor(sf::Color(255,255,255,255));
       //     std::cout << tex.size() << std::endl;
        }
        void cleanStaticTexture(){
            window.clear();
            windowTexture.update(window);
        }
	void staticDraw(){
		window.clear();
		window.draw( windowSprite );
                line.draw(window);
		window.display();
	}
	void draw(){
                
		window.clear(sf::Color(0,0,0,0));
                background.draw(window);
		board.draw();
		window.display();
	}

};


int main(){
	Game game(500,500,8,4);
	game.start();
	return 0;
}
