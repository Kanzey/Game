#ifndef BACKGROUND_HPP
#define	BACKGROUND_HPP

class Background {
private:
    sf::RenderTexture renderTexture;
    sf::Texture texture1, texture2;
    int grindSize;
    
public:
    Background(std::string texPath1, std::string texPath2);
    Background(std::string texFilePath);
    
    void create( sf::Vector2i cords, sf::Vector2f start, int cellSize, int grindSize);    
    void draw( sf::RenderWindow & window );
};

#endif	/* BACKGROUND_HPP */

