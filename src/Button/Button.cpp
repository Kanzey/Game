#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Button.hpp"

void Button::setPosition(const sf::Vector2f & cords){
    sprite.setPosition( cords );
}

void Button::resize(const sf::Vector2f& scale){
    sprite.scale( scale );
}

void Button::draw(sf::RenderTarget &renderTarget){
    renderTarget.draw(sprite);
}

void Button::setTexture(const sf::Texture& texture){
    sprite.setTexture(texture, true);
}

sf::FloatRect Button::getGlobalBounds(){
    return sprite.getGlobalBounds();
}