#ifndef GRIDOFCELLS_HPP
#define GRIDOFCELLS_HPP

class GridOfCells: public std::vector<ColumnOfCells> {
public:
	GridOfCells(int n = 8) : std::vector<ColumnOfCells>(n, ColumnOfCells(n) ) { }

	void updateScale();
	void draw(sf::RenderWindow & window);
        void update( ObjectTextures & objectTextures);
	void setPosition(sf::Vector2f start, int size);
        void draw(int type, sf::RenderWindow & window);
};

#endif
