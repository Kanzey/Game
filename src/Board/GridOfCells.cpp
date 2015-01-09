#include "GridOfCells.hpp"

void GridOfCells::draw(sf::RenderWindow & window){
	for (GridOfCells::iterator i = begin(); i != end(); ++i)
			i->draw(window);
}
        
void GridOfCells::setPosition(sf::Vector2f start, int size){
	int k = 0;
	for (GridOfCells::iterator i = begin(); i != end(); ++i)
		i->setPosition(start, k++, size);
}

void GridOfCells::draw(int type, sf::RenderWindow & window){
	for(GridOfCells::iterator i = begin(); i != end(); ++i)
     	i->draw(type, window);
}

void GridOfCells::updateScale(){
	for(GridOfCells::iterator i = begin(); i != end(); ++i)
		i->updateScale();
}

void GridOfCells::update( ObjectTextures & objectTextures){
	for(GridOfCells::iterator i = begin(); i != end(); ++i)
		i->update( objectTextures );
}


