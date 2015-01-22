#include "CurveLine.hpp"

void CurveLine::addCell(Cell* cell){
	cell->setWasVisted(1);
    cells.push_back(cell);
    int size = cells.size();
    if(size > 1){
        lines.push_back(sf::RectangleShape());
        lines.back() = createLine( cells[size-1]->getCenter(), cells[size-2]->getCenter(),cells[size-1]->getSize()/8  );
    }
}

void CurveLine::pop_back(){
	if(cells.size()>1){
		lines.pop_back();
    }
    cells.back()->setWasVisted( 0 );
    cells.pop_back();
}

inline void CurveLine::draw(sf::RenderWindow & window){
    for(std::vector<sf::RectangleShape>::iterator i = lines.begin(); i != lines.end(); ++i)
		window.draw(*i);
}

inline Cell* CurveLine::back(){
        return cells.back();
}

inline void CurveLine::clear(){
	for(std::vector<Cell*>::iterator i = cells.begin(); i!= cells.end(); ++i)
		(*i)->setWasVisted(0);
	lines.clear();
	cells.clear();
}

inline void CurveLine::drawLast(sf::RenderWindow & window){
	window.draw(lines.back());
}

inline int CurveLine::type(){ return cells[0]->getType(); }

inline void CurveLine::colect(){
	for(std::vector<Cell*>::iterator i = cells.begin(); i!= cells.end(); ++i)
		(*i)->setState(0);
}

inline int CurveLine::endConection( int minConection ){
    int tmp = 0;
    if( cells.size() >= minConection ){
        colect();
        tmp = cells.size();
    }
    clear();
    return tmp;
}
