#ifndef SCOREBOARD_HPP
#define	SCOREBOARD_HPP

class Scoreboard{
private:
    sf::Texture texture;
    sf::RenderWindow & window;
    sf::Texture backgroundTexture;
    std::vector<sf::Text> scores;
    sf::Font font;
public:
    Scoreboard(sf::RenderWindow & window): window(window){
        texture.loadFromFile("../Textures/grass.jpg"); 
        font.loadFromFile( "../arial.ttf" );
    }
    
    void start();
    void draw();
    sf::Vector2f getBounds();
    void setText( sf::Vector2f bounds);
    void drawText();
    void loadScores();
};

#endif	/* SCOREBOARD_HPP */

