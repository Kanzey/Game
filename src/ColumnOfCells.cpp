#include "ColumnOfCells.hpp"

void ColumnOfCells::draw(sf::RenderWindow & window){
	for (ColumnOfCells::iterator i = begin(); i != end(); ++i){
		if( ! i->isOnPlace() ) i->move(0,i->getSize()/10);
		window.draw(*i);
	}
}

void ColumnOfCells::draw(int type, sf::RenderWindow & window){
	for(ColumnOfCells::iterator i = begin(); i != end(); ++i)
		if(i->getType() == type) window.draw(*i);
}

void ColumnOfCells::setPosition(sf::Vector2f start, int num, int size ){
	int k = 0;
	sf::Vector2f position;
	for (ColumnOfCells::iterator i = begin(); i != end(); ++i){
		position.x = start.x + num*size;
		position.y = start.y + k++*size;
		i->setPosition( position );
		i->setEndPosition( position );
		i->setSize(size);
	}
}

void ColumnOfCells::updateScale(){
 	for(ColumnOfCells::iterator i = begin(); i != end(); ++i)
		i->updateScale();
}

int ColumnOfCells::isFull(){
	 return _isFull;
}

void ColumnOfCells::setIsFull(int f){
	_isFull = f;
}

iter ColumnOfCells::updatePosition( std::vector<Cell*> & buff){
	int s = 1;
	std::vector<Cell*>::iterator it = buff.begin();
	iter ri = rbegin();
	sf::Vector2f end;
    while(it != buff.end() ){
    	end = ri->getEndPosition();
        *ri = *(*it);
        ri->setEndPosition( end );
        ri++; it++;
    }
	return ri;
}

void ColumnOfCells::createNewCells( iter ri, ObjectTextures & objectTextures){
	int s = 1;
	 while(ri != rend()){
    	ri->set(objectTextures.random());
     	ri->setState(1);
        ri->setWasVisted(0);
        sf::Vector2f pos = ri->getPosition();
        ri->setPosition(pos.x,-(s++)*ri->getSize());
        ++ri;
   	}
}

void ColumnOfCells::saveNonConected( std::vector<Cell*>  & buff ){
	  for(iter ri = rbegin(); ri != rend(); ++ri){
    	if( ri->getState() != 0 ) {
    		buff.push_back( &(*ri));
    		ri->setState(1);
   		}
    }
}

void ColumnOfCells::update( ObjectTextures & objectTextures ){
    std::vector<Cell*> buff;
	saveNonConected( buff );
	iter ri = updatePosition( buff );
	createNewCells(ri, objectTextures);
}

#undef iter

