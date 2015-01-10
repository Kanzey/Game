#ifndef CURVELINE_HPP
#define CURVELINE_HPP

class CurveLine{
private:

    std::vector<Cell*> cells;
    std::vector<sf::RectangleShape> lines;
    
public:
	//return line type. Depends on type of first added Cell;
    inline int type();
	//return poiter to last Cell in conected line. U. 
    inline Cell* back();

    inline void clear();
    inline void colect();
    void pop_back();
    void addCell(Cell* cell);
    inline void draw(sf::RenderWindow & window);
    inline void drawLast(sf::RenderWindow & window);
    inline int endConection( int minConection );
    
};

#endif
