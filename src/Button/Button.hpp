#ifndef BUTTON_HPP
#define	BUTTON_HPP

#include "Drawable.cpp"
#include "Clickable.cpp"

class Button : public Clickable, public Drawable {
public:
    sf::Sprite sprite;
    Button(): sprite() { }
    Button(const sf::Texture & texture): sprite(texture) { }
    
    bool isOn(const sf::Vector2f & cords);
    void setPosition(const sf::Vector2f & cords);
    void resize( const sf::Vector2f & scale );
    void draw( sf::RenderTarget &renderTarget );
    void setTexture(const sf::Texture & texture);    
    sf::FloatRect getGlobalBounds();
};

#endif	/* BUTTON_HPP */

