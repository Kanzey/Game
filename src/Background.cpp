#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Background.hpp"

Background::Background(std::string texPath1, std::string texPath2){
    texture1.loadFromFile(texPath1.c_str());
    texture2.loadFromFile(texPath2.c_str());
}
Background::Background(std::string texFilePath){
    std::fstream file(texFilePath.c_str());
    std::string texPath;
    getline(file, texPath);
    texture1.loadFromFile(texPath);
    getline(file,texPath);
    texture2.loadFromFile(texPath);
}

void Background::create( sf::Vector2i cords, sf::Vector2f start, int cellSize, int grindSize){
        
    sf::Sprite sprite(texture1);
    renderTexture.create(cords.x, cords.y);
    float x = texture1.getSize().x, y = texture1.getSize().y;

    while( sprite.getPosition().x < cords.x ){
        while( sprite.getPosition().y < cords.y){
            renderTexture.draw( sprite );
            sprite.move(0,y);
        }
        sprite.setPosition( sprite.getPosition().x + x, 0);
    }
    sprite = sf::Sprite(texture2);
    x = texture2.getSize().x; y = texture2.getSize().y;
    sprite.setScale(cellSize/x, cellSize/y);
    sprite.setPosition(start);
    for(int i=0; i<=grindSize; ++i){
        for(int k=0; k<grindSize; ++k){
            renderTexture.draw( sprite );
            sprite.move( 0, cellSize );
        }
        sprite.setPosition(start.x + i*cellSize, start.y);
    }
    
    renderTexture.display();
}
    
void Background::draw( sf::RenderWindow & window ){
    window.draw( sf::Sprite(renderTexture.getTexture()));
}
