#ifndef BOARD_HPP
#define BOARD_HPP

#include "Board/Cell.cpp"
#include "Board/ObjectTextures.cpp"
#include "Board/ColumnOfCells.cpp"
#include "Board/GridOfCells.cpp"

class Board{
public:
	sf::Vector2f start;
	int size, num, cellSize;
	sf::RenderWindow * window;
	GridOfCells gridOfCells;
    sf::Texture wood, grass;
	ObjectTextures objectTextures;	

	Board() { }
	Board(sf::RenderWindow* window, sf::Vector2f start, int cellSize, int num, int numOfPices  );

	void init();
	void resize(int x, int y); 

	Cell* getCell(sf::Vector2i  num);
	Cell* getCell(sf::Vector2f cords);

	// is cursor in game board
	bool isIn(sf::Vector2f cursor);

    // are cells these same type
	bool isSameType(Cell* a, Cell* b);

    // return cell center cordinates from Column and Row number;
	sf::Vector2f cellCenter(sf::Vector2i pos);

    //return Colum and Row number from cordinates;
	sf::Vector2i cellNum(sf::Vector2f cursor);

    //return cell center cordinates from cordinates
	sf::Vector2f cellCenter(sf::Vector2f cursor);
 
    //return poiter to cell over point given by cordinates
	Cell* cellFromPosition(sf::Vector2f cursor);

    //draw content of grid
	void draw();

    //draw only cells of given type;
    void draw(int type);
    void update();
        
}; 

#endif
