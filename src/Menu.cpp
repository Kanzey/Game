#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cmath>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Button/FunctionButtons.cpp"

#include "Menu.hpp"
#include "Background.hpp"

Menu::Menu(std::string texPath1) {
    loadTextures(texPath1);
}

inline void Menu::loadTextures(std::string texPath1) {
    texture1.loadFromFile(texPath1);
    startTex.loadFromFile("../Textures/start.png");
    quitTex.loadFromFile("../Textures/quit.png");
    scoreTex.loadFromFile("../Textures/scores.png");
    startBut.setTexture(startTex);
    scoreBut.setTexture(scoreTex);
    quitBut.setTexture(quitTex);
}

inline void Menu::resize(int x, int y) {
    size = sf::Vector2f(x, y);
    create(x, y);
}

inline void Menu::resize(const sf::Vector2u & size){
    this->size = static_cast<sf::Vector2f>(size);
    create(size.x, size.y);
}

inline void Menu::create(const sf::Vector2u & size) {
    create(size.x, size.y);
}

void Menu::create(int x, int y) {
    sf::Sprite sprite(texture1);
    renderTexture.create(x, y);

    while (sprite.getPosition().x < x) {
        while (sprite.getPosition().y < y) {
            renderTexture.draw( sprite );
            sprite.move(0, texture1.getSize().y);
        }
        sprite.setPosition(sprite.getPosition().x + texture1.getSize().x, 0);
    }
    placeButtons(x, y);
    startBut.draw(renderTexture);
    scoreBut.draw(renderTexture);
    quitBut.draw(renderTexture);
    renderTexture.display();
}

void Menu::placeButtons(int x, int y) {
    sf::FloatRect rect = startBut.sprite.getGlobalBounds();

    float scale = std::min(4 * x / (8 * rect.width), 4 * y / (24 * rect.height));
    startBut.resize(sf::Vector2f(scale, scale));
    scoreBut.resize(sf::Vector2f(scale, scale));
    quitBut.resize(sf::Vector2f(scale, scale));
    rect = startBut.getGlobalBounds();
    sf::Vector2f start((x - rect.width) / 2, (y - 3 * rect.height) / 2);
    startBut.setPosition(start);
    start.y += rect.height + y / 10;
    scoreBut.setPosition(start);
    start.y += rect.height + y / 10;
    quitBut.setPosition(start);
}

inline void Menu::draw(sf::RenderWindow& window) {
    window.draw(sf::Sprite(renderTexture.getTexture()));
}

void Menu::start(sf::RenderWindow & window) {
    sf::Event event;
    sf::Vector2f cursor;
    create( window.getSize() );

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cursor = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (startBut.getGlobalBounds().contains( cursor ) ) startBut.onClick(window);
                    else if( scoreBut.getGlobalBounds().contains( cursor ) ) scoreBut.onClick(window);
                    else if( quitBut.getGlobalBounds().contains( cursor ) ) quitBut.onClick(window);
                }
            }
            if (event.type == sf::Event::Resized ){
                resize( event.size.width, event.size.height );
            }
        }
        window.clear();
        draw( window );
        window.display();
    }
}
