#include "Cell.hpp"

int Cell::getState(){
	return _state; 
}

int Cell::wasVisited(){
	return _wasVisted;
}

int Cell::getType(){
	return _type;
}

int Cell::getSize(){
	return _size;
}

sf::Vector2f Cell::getEndPositon(){
	return _endPosition;
}

void Cell::setEndPosition(sf::Vector2f pos){
	_endPosition = pos;
}

void Cell::setSize(int s){
	_size = s;
}

void Cell::setState(int s){
	_state = s;
}

void Cell::setWasVisted(int v){
	_wasVisted = v;
}

void Cell::setType( int t ){ 
	_type = t;
}

void Cell::updateScale(){
	float scale = float(_size)/ float(getTexture()->getSize().x); 
	setScale( scale, scale );
}

void Cell::set( TwT para){
	setType(para.first); 
	setTexture(*para.second);
        updateScale();
}
sf::Vector2f Cell::getCenter(){
      return getPosition() + sf::Vector2f( getSize()/2, getSize()/2);
}
