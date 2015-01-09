#ifndef COLUMNOFCELLS_HPP
#define COLUMNOFCELLS_HPP

#define iter ColumnOfCells::reverse_iterator

class ColumnOfCells: public std::vector<Cell>{
private:
	int _isFull;
public:

	ColumnOfCells(int n) : std::vector<Cell>(n) { }
	
	int isFull();
	void updateScale();
	void setIsFull(int f);
	void draw(sf::RenderWindow & window);
	iter updatePosition( std::vector<Cell*> & buff);
        void update( ObjectTextures & objectTextures);
        void draw(int type, sf::RenderWindow & window);
	void saveNonConected( std::vector<Cell*>  & buff );
	void setPosition(sf::Vector2f start, int num, int size );
	void createNewCells( iter ri, ObjectTextures & objectTextures);

};


#endif
