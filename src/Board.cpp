#include "Board.hpp"

Board::Board(sf::RenderWindow* window, sf::Vector2f start, int cellSize, int num, int numOfPices  )
	:num(num), window(window), start(start), size(num*cellSize), cellSize(cellSize) {
	objectTextures = ObjectTextures(3,"../Textures/Textures.txt");
	gridOfCells = GridOfCells( num );
	gridOfCells.setPosition(start,cellSize);
}
        
void Board::init(){
	int s = 0;
	for (GridOfCells::iterator i = gridOfCells.begin(); i != gridOfCells.end(); ++i)
		for (ColumnOfCells::iterator k = i->begin(); k != i->end(); ++k)
			k->set( objectTextures.random() );
}

void Board::resize(int x, int y){
	cellSize = std::min(x,y)/(num+2);
	size = cellSize * num;
	start = sf::Vector2f((x-size)/2,(y-size)/2);
	gridOfCells.setPosition(start, cellSize);
	sf::View view(sf::FloatRect(0,0,x,y));
	window->setView(view);
	gridOfCells.updateScale();
}
        
bool Board::isIn(sf::Vector2f cursor){
	return  cursor.x > start.x && cursor.y > start.y  && cursor.x < start.x + size &&  cursor.y < start.y + size ;
}

bool Board::isSameType(Cell* a, Cell* b){  
	return a->getType() == b->getType();
}        

sf::Vector2f Board::cellCenter(sf::Vector2i pos){ 
	sf::Vector2f center;
	center.x = start.x + pos.x*size + size/2;
	center.y = start.y + pos.y*size + size/2;
	return center;
}

sf::Vector2i Board::cellNum(sf::Vector2f cursor){	
	return sf::Vector2i(int(cursor.x-start.x)/cellSize, int(cursor.y-start.y)/cellSize);
}

sf::Vector2f Board::cellCenter(sf::Vector2f cursor){ 
	return cellCenter(cellNum(cursor));
}

Cell* Board::getCell(sf::Vector2i  num){
	return & gridOfCells[num.x][num.y];
}

Cell* Board::getCell(sf::Vector2f cords){
    return getCell( cellNum(cords) );
}
        
Cell* Board::cellFromPosition(sf::Vector2f cursor){ 
	sf::Vector2i pos = cellNum(cursor);
	return &gridOfCells[pos.x][pos.y];
}

void Board::draw(){
	gridOfCells.draw(*window);
}

void Board::draw(int type){  
	gridOfCells.draw(type, *window);
}

void Board::update(){
	gridOfCells.update( objectTextures );
}
 
