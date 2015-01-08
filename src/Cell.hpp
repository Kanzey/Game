#ifndef CELL_HPP
#define CELL_HPP

#ifndef TwT
#define TwT std::pair<int,sf::Texture*>
#endif

class Cell:public sf::Sprite{
private:
	int _type;
	// state of Cell 0
	// 0 - Cell is moving.
	// 1 - Cell is on place.
	int _state;
	int _wasVisted;
	int _size;

	//Contais curentCell destination point used in dropdown animation
        sf::Vector2f _endPosition;
public:

	Cell(): _state(1), _wasVisted(0) {};
	int getState();
	int wasVisited();
	int getType();
        int getSize();
        sf::Vector2f getEndPositon();
        void setEndPosition(sf::Vector2f pos);
	void setSize(int s);
	void setState(int s);
	void setWasVisted(int visitState);
	void setType( int type );
        void updateScale();
	void set( TwT para );
        sf::Vector2f getCenter();
};

#endif
