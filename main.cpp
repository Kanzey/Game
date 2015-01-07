#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
//#include <SFML/Thread.hpp>
#define PI 3.14159265


std::vector<sf::Texture> tex;


class ObjectTextures{
public:
	//load given number of textures. Textures are stored in global vector tex for easy maintance.
        //Texture files are defined in ./Textures/Textures.txt
	ObjectTextures(int n = 3){
            tex.clear();
		std::string tmp;
		std::fstream file("Textures/Textures.txt");
		for (int i = 0; i < n; ++i)
		{
			getline(file, tmp);
			tex.push_back(sf::Texture());
			tex.back().loadFromFile(tmp.c_str());	
		//std::cout << tmp<< std::endl;
		}
		srand(time(NULL));
	}
        //
	std::pair<int, sf::Texture* > random(){
		
		int _random = rand() % tex.size();
		return std::make_pair(_random, &tex[_random]);
	}

};

ObjectTextures objectTextures;

sf::RectangleShape createLine(sf::Vector2f A, sf::Vector2f B, int thicknes){
    double x = A.x-B.x;
    double y = A.y-B.y;
    double r = hypot(x,y);
    double rotate = atan2(x,y);
    sf::RectangleShape line(sf::Vector2f(r,thicknes));
    std::cout << x << " " << y << std::endl;
    line.rotate(270 - rotate*180/PI);
    line.setPosition(A);
    line.move(-thicknes*y/r/2, thicknes*x/r/2);
    return line;
}

int calcDist( sf::Vector2f A, sf::Vector2f B){
    return hypot(A.x-B.x, A.y-B.y);
}

void drawLine( std::vector<sf::Vector2f> & line, sf::RenderWindow & window, int thicknes){
    for(std::vector<sf::Vector2f>::iterator i = line.begin(); i!= line.end()-1; ++i) {
        window.draw( createLine( *i, *(i+1), thicknes ) );
    }
}


class Cell:public sf::Sprite{
	int _type;
	int _state;
	int _wasVisted;
	int _size;
        sf::Vector2f _endPosition;
public:

	Cell(): _state(1), _wasVisted(0) {};
	int getState(){ return _state; }
	int wasVisited(){ return _wasVisted;}
	int getType(){ return _type; }
        int getSize(){ return _size; }
        sf::Vector2f getEndPositon(){ return _endPosition; };
        void setEndPosition(sf::Vector2f pos){ _endPosition = pos; }
	void setSize(int s) { _size = s; }
	void setState(int s){ _state = s; }
	void setWasVisted(int v){ _wasVisted = v; }
	void setType( int t ){ _type = t; }
        void updateScale(){
            float scale = float(_size)/ float(getTexture()->getSize().x); 
            setScale( scale, scale );
        }
	void set( std::pair<int,sf::Texture*> par){
		setType(par.first); 
		//Texturere.loadFromFile( c.c_str() );
		setTexture(*par.second);
                updateScale();
	}
        sf::Vector2f getCenter(){
            return getPosition() + sf::Vector2f( getSize()/2, getSize()/2);
        }
};

class ColumnOfCells: public std::vector<Cell>{
	int _isFull;
public:
	ColumnOfCells(int n) : std::vector<Cell>(n) { }

	void draw(sf::RenderWindow & window){
            for (ColumnOfCells::iterator i = begin(); i != end(); ++i){
                if( abs(i->getPosition().y - i->getEndPositon().y ) > i->getSize()/10 ){
                    i->move(0,i->getSize()/10);
                }else{
                    i->setPosition( i->getEndPositon());
                }
			window.draw(*i);
            }
	}
        void draw(int type, sf::RenderWindow & window){
            for(ColumnOfCells::iterator i = begin(); i != end(); ++i)
                if(i->getType() == type) window.draw(*i);
        }
	void setPosition(sf::Vector2f start, int num, int size ){
		int k = 0;
		sf::Vector2f position;
		for (ColumnOfCells::iterator i = begin(); i != end(); ++i)
		{
			position.x = start.x + num*size;
			position.y = start.y + k++*size;
			//std::cout << position.x << " " << position.y << std::endl;
			i->setPosition( position );
                        i->setEndPosition( position );
			i->setSize(size);
		}
	}
        void updateScale(){
            for(ColumnOfCells::iterator i = begin(); i != end(); ++i)
                i->updateScale();
        }
	int isFull() { return _isFull == size(); }
	void setIsFull(int f){ _isFull = f;}
        void update(){
            std::vector<Cell*> buff;
            for(ColumnOfCells::reverse_iterator ri = rbegin(); ri != rend(); ++ri){
                if( ri->getState() != 0 ) {
                    buff.push_back( &(*ri));
                    ri->setState(1);
                }
            }
            std::vector<Cell*>::iterator it = buff.begin();
            int s = 1;
            ColumnOfCells::reverse_iterator ri = rbegin();
            sf::Vector2f end;
                        while(it != buff.end() ){
                        end = ri->getEndPositon();
                        *ri = *(*it);
                        ri->setEndPosition( end );
                        ri++; it++;
                    }
            while(ri != rend()){
                ri->set(objectTextures.random());
                ri->setState(1);
                ri->setWasVisted(0);
                sf::Vector2f pos = ri->getPosition();
                ri->setPosition(pos.x,-(s++)*ri->getSize());
                ++ri;
            }
        }
};

class GridOfCells: public std::vector<ColumnOfCells> {
public:
	GridOfCells(int n = 8) : std::vector<ColumnOfCells>(n, ColumnOfCells(n) ) { }

	void draw(sf::RenderWindow & window){  //draw all elements of the Grid;
		for (GridOfCells::iterator i = begin(); i != end(); ++i)
			i->draw(window);
	}
        
	void setPosition(sf::Vector2f start, int size){
		int k = 0;
		for (GridOfCells::iterator i = begin(); i != end(); ++i)
			i->setPosition(start, k++, size);
	}
        void draw(int type, sf::RenderWindow & window){
            for(GridOfCells::iterator i = begin(); i != end(); ++i)
                i->draw(type, window);
        }
        void updateScale(){
            for(GridOfCells::iterator i = begin(); i != end(); ++i)
                i->updateScale();
        }
        void update(){
            for(GridOfCells::iterator i = begin(); i != end(); ++i){
                i->update();
            }
        }
};



class Board{
public:
	sf::Vector2f start;
	int size, num, cellSize;
	sf::RenderWindow * window;
	GridOfCells gridOfCells;
        sf::Texture wood, grass;
	Board() { }
	Board(sf::RenderWindow* window, sf::Vector2f start, int cellSize, int num, int numOfPices  ):num(num), window(window), start(start), size(num*cellSize), cellSize(cellSize) {

		gridOfCells = GridOfCells( num );
		gridOfCells.setPosition(start,cellSize);
		int s = 0;
		for (GridOfCells::iterator i = gridOfCells.begin(); i != gridOfCells.end(); ++i)
		{
			for (ColumnOfCells::iterator k = i->begin(); k != i->end(); ++k)
			{
				//std::cout << ++s<<std::endl;
				k->set( objectTextures.random() );
			}
		}
            /*    wood.loadFromFile("Textures/wood.jpg");
                wood.setRepeated(1);
                grass.loadFromFile("Textures/grass.jpg");
                grass.setRepeated(1);
	*/
	}
        /*
        void createBackground(sf::Texture* texture){
            sf::RectangleShape bc1(sf::Vector2f(window->getSize().x, window->getSize().y));
            bc1.setTexture(&grass, true);
            sf::RectangleShape bc2(sf::Vector2f( size,size));
            bc2.move(sf::Vector2f(window->getSize().x/num, window->getSize().x/num));
            bc2.setTexture(&wood, true);
            while(1){
            window->clear();
            window->draw(bc1);
            window->draw(bc2);
            texture->update( *window );
            window->display();
            }
            window->clear();
            
            while(1){
                window->draw(sf::Sprite(*texture));
                window->display();
            }
        }
        */
        void resize(int x, int y){
            cellSize = std::min(x,y)/(num+2);
            size = cellSize * num;
            start = sf::Vector2f((x-size)/2,(y-size)/2);
            gridOfCells.setPosition(start, cellSize);
            sf::View view(sf::FloatRect(0,0,x,y));
            window->setView(view);
            gridOfCells.updateScale();
            
        }
        
	bool isIn(sf::Vector2f cursor){ // is cursor in game board
		return  cursor.x > start.x && cursor.y > start.y  && cursor.x < start.x + size &&  cursor.y < start.y + size ;
	}
        // are celss these same type
	bool isSameType(Cell* a, Cell* b){  
		return a->getType() == b->getType();
	}        
        // return cell center cordinates from Column and Row number;
	sf::Vector2f cellCenter(sf::Vector2i pos){ 
		sf::Vector2f center;
		center.x = start.x + pos.x*size + size/2;
		center.y = start.y + pos.y*size + size/2;
		return center;
	}
        //return Colum and Row number from cordinates;
	sf::Vector2i cellNum(sf::Vector2f cursor){	
		return sf::Vector2i(int(cursor.x-start.x)/cellSize, int(cursor.y-start.y)/cellSize);
	}
        //return cell center cordinates from cordinates
	sf::Vector2f cellCenter(sf::Vector2f cursor){ 
		return cellCenter(cellNum(cursor));
	}
        Cell* getCell(sf::Vector2i  num){
            return & gridOfCells[num.x][num.y];
        }
        Cell* getCell(sf::Vector2f cords){
            return getCell( cellNum(cords) );
        }
        
        //return poiter to cell over point given by cordinates
	Cell* cellFromPosition(sf::Vector2f cursor){ 
		sf::Vector2i pos = cellNum(cursor);
                std::cout << cursor.x <<" "<< cursor.y << std::endl;
                std::cout << pos.x << " " << pos.y << std::endl;
		return &gridOfCells[pos.x][pos.y];
	}
        //draw content of grid
	void draw(){
            gridOfCells.draw(*window);
	}
        //draw only cells of given type;
        void draw(int type){  
            gridOfCells.draw(type, *window);
        }
        void update(){
            gridOfCells.update();
        }
        
}; 

class CurveLine{
public:
    std::vector<Cell*> cells;
    std::vector<sf::RectangleShape> lines;
    
    void addCell(Cell* cell){
        cell->setWasVisted(1);
        cells.push_back(cell);
        int size = cells.size();
        if(size > 1){
            lines.push_back(sf::RectangleShape());
            lines.back() = createLine( cells[size-1]->getCenter(), cells[size-2]->getCenter(),cells[size-1]->getSize()/8  );
        }
    }
    void pop_back(){
        if(cells.size()>1){
            lines.pop_back();
        }
        cells.back()->setWasVisted( 0 );
        cells.pop_back();
    }
    void draw(sf::RenderWindow & window){
        for(std::vector<sf::RectangleShape>::iterator i = lines.begin(); i != lines.end(); ++i)
            window.draw(*i);
    }
    Cell* back(){
        return cells.back();
    }
    void clear(){
        for(std::vector<Cell*>::iterator i = cells.begin(); i!= cells.end(); ++i)
            (*i)->setWasVisted(0);
        lines.clear();
        cells.clear();
    }
    void drawLast(sf::RenderWindow & window){
        window.draw(lines.back());
    }
    int type(){ return cells[0]->getType(); }
    void colect(){
        for(std::vector<Cell*>::iterator i = cells.begin(); i!= cells.end(); ++i)
            (*i)->setState(0);
    }
    
};


class Game{
public:
	sf::RenderWindow window;
	sf::Texture windowTexture, backgroundTexture;
	sf::Sprite windowSprite;
        CurveLine line;
	Board board;
	Game( int x, int y, int cross, int numOfPices) {
		window.create(sf::VideoMode(x ,y), "Game" );
		int size =	std::min(x,y)/(cross+2);
                int sizex = (x-cross*size)/2;
                int sizey = (y-cross*size)/2; 
		board = Board(&window, sf::Vector2f(sizex,sizey), size, cross, numOfPices);
		windowTexture.create(x,y);
		windowSprite.setTexture(windowTexture);
	}
        //function handling game events and response to them;
	void start(){
            sf::Vector2f cursor;
		sf::Event event;
		int cflag = 0;
		while(window.isOpen() ){
			while(window.pollEvent(event)){
				if(event.type == sf::Event::Closed){
					window.close();
				}
				if(event.type == sf::Event::MouseButtonPressed){
                                    if( event.mouseButton.button  == sf::Mouse::Left ){
                                        cursor = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					if( board.isIn(cursor)){
                                            Cell * cell = board.cellFromPosition(cursor);
                                            highlight( cell->getType() );
                                            line.addCell(cell);
                                            cflag = 1;
                                        }
                                    }
				}
				if(event.type == sf::Event::MouseButtonReleased){
                                    if( event.mouseButton.button == sf::Mouse::Left ){
                                        line.colect();
                                        line.clear();
                                        cleanStaticTexture();
					cflag = 0;
                                        board.update();
                                    }
				}
                                if(event.type == sf::Event::Resized){
                                    unsigned int x = event.size.width, y = event.size.height;
                                        board.resize(x, y);
                                        windowTexture.create(x, y);
                                        windowSprite.setTextureRect(sf::IntRect(0, 0, x, y));
                                        //board.createBackground(&backgroundTexture);
                                }
                                if( cflag == 1)
                                   if(event.type == sf::Event::MouseMoved)
                                    {
                                        sf::Vector2f cursor(event.mouseMove.x, event.mouseMove.y);
                                        if(board.isIn(cursor)){
                                            Cell* cell = board.cellFromPosition(cursor);
                                            if( !cell->wasVisited() && line.type() == cell->getType() && calcDist(cursor,line.back()->getCenter()) < hypot(cell->getSize(),cell->getSize())+1 ){
                                                line.addCell(cell);
                                            }
                                        }
                                }
			}
			if( cflag ) staticDraw();
			else 		draw();
		}
	}
        //function higlight elements of given type and store that image in windowTexture; 
        void highlight(int type){
            window.clear(sf::Color(0,0,0,0));
            board.draw();
            windowTexture.update( window );
            windowSprite.setColor(sf::Color(90,90,90,255));
            window.clear();
            window.draw(windowSprite);
            board.draw(type);
            windowTexture.update( window );
            windowSprite.setColor(sf::Color(255,255,255,255));
       //     std::cout << tex.size() << std::endl;
        }
        void cleanStaticTexture(){
            window.clear();
            windowTexture.update(window);
        }
	void staticDraw(){
		window.clear();
		window.draw( windowSprite );
                line.draw(window);
		window.display();
	}
	void draw(){
            
		window.clear(sf::Color(0,0,0,0));
		board.draw();
		window.display();
	}

};


int main(){
	Game game(800,1200,8,3);
	game.start();
	return 0;
}