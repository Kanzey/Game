#include <SFML/Graphics/RenderWindow.hpp>

#include "Button.cpp"
#include "FunctionButtons.hpp"
#include "../GameScreen.cpp"

void StartButton::onClick(sf::RenderWindow& renderWindow){
   start( renderWindow );
}

void StartButton::start(sf::RenderWindow & renderWindow){
    GameScreen gameScreen( renderWindow.getSize().x, renderWindow.getSize().y, 8, 4, renderWindow );
    gameScreen.start();
}

void ScoreButton::onClick(sf::RenderWindow& renderWindow){
    std::cout<< "Not implemented jet\n" << std::endl;
}

void QuitButton::onClick(sf::RenderWindow& renderWindow){
    renderWindow.close();
}