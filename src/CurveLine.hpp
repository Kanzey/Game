#ifndef CURVELINE_HPP
#define CURVELINE_HPP

class CurveLine{
private:

    std::vector<Cell*> cells;
    std::vector<sf::RectangleShape> lines;
    
public:
	//return line type. Depends on type of first added Cell;
    int type();
	//return poiter to last Cell in conected line. U. 
    Cell* back();

	void clear();
	void colect();
	void pop_back();
    void addCell(Cell* cell);
    void draw(sf::RenderWindow & window);
    void drawLast(sf::RenderWindow & window);

};

#endif
