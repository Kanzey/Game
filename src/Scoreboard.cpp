#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <SFML/Graphics/Text.hpp>

#include "Scoreboard.hpp"

void Scoreboard::start(){
    sf::Event event;
    int flag = 0;
    window.clear();
    draw();
    window.display();
    while (window.isOpen() && flag == 0) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    flag = 1;
                }
            }
            if ( event.type == sf::Event::Resized ){
                int x = event.size.width, y = event.size.height;
                window.clear();
                draw();
                window.display();
                window.setView(sf::View(sf::FloatRect(0,0,x,y)));
            }
        }
    }
}

void Scoreboard::draw(){
    int x = window.getSize().x , y = window.getSize().y;
    sf::Sprite sprite(texture);
   
    while (sprite.getPosition().x < x) {
          while (sprite.getPosition().y < y) {
            window.draw( sprite );
            sprite.move(0, texture.getSize().y);
        }
        sprite.setPosition(sprite.getPosition().x + texture.getSize().x, 0);
    }    
    loadScores();
    
    if( scores.size() != 0){
        sf::Vector2f bounds = getBounds();
        setText(bounds);
        drawText();
    }
}

void Scoreboard::setText( sf::Vector2f bounds){
    int x = window.getSize().x, y = window.getSize().y;
    //if( x*8/10 < bounds.x || y*8/10 < bounds.y ){
        float scale = std::min( x*8/10/bounds.x, y*8/10/bounds.y );
        for(std::vector<sf::Text>::iterator it = scores.begin(); it != scores.end(); ++it){
            it->scale( scale, scale );
        }
        bounds.x *= scale;
        bounds.y *= scale;
    //}
    x = (x-bounds.x)/2;
    y = (y-bounds.y)/2;
    int i = 0;
    int height = scores[0].getGlobalBounds().height;
    for(std::vector<sf::Text>::iterator it = scores.begin(); it != scores.end(); ++it){
            it->setPosition(x, y/2 + i++*(height + y/10) );
    }
}

void Scoreboard::drawText(){
    for(std::vector<sf::Text>::iterator it = scores.begin(); it != scores.end(); ++it){
        window.draw(*it);
    }
}

void Scoreboard::loadScores(){
    if(scores.size() == 0){
        std::ifstream file("ut.bin");
        std::string in;
        
        while( getline( file, in ) ){
            scores.push_back(sf::Text(in,font, 60));
        }
    }
}

sf::Vector2f Scoreboard::getBounds(){
    float maxWidth = 0;
    float maxHeight =0;
    for(std::vector<sf::Text>::iterator it = scores.begin(); it != scores.end(); ++it ){
        maxWidth = std::max( maxWidth, it->getGlobalBounds().width );
    }
    maxHeight = scores.back().getGlobalBounds().height * scores.size();
    return sf::Vector2f( maxWidth, maxHeight );
}
