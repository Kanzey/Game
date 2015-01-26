#include <SFML/Graphics/RenderWindow.hpp>

#include "Button.cpp"
#include "FunctionButtons.hpp"
#include "../GameScreen.cpp"
#include "../Scoreboard.cpp"

void StartButton::onClick(sf::RenderWindow& renderWindow){
   start( renderWindow );
}

void StartButton::start(sf::RenderWindow & renderWindow){
    GameScreen gameScreen( renderWindow.getSize().x, renderWindow.getSize().y, 8, 4, renderWindow );
    gameScreen.start(maxMoves);
}

void ScoreButton::onClick(sf::RenderWindow& renderWindow){
    Scoreboard scoreboard(renderWindow);
    scoreboard.start();
}

void QuitButton::onClick(sf::RenderWindow& renderWindow){
    renderWindow.close();
}