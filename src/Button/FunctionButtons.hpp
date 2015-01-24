/* 
 * File:   FunctionButtons.hpp
 * Author: kamil
 *
 * Created on 15 styczeń 2015, 19:49
 */

#ifndef FUNCTIONBUTTONS_HPP
#define	FUNCTIONBUTTONS_HPP

class StartButton : public Button{
private:
    void start(sf::RenderWindow & renderWindow);
public:
    StartButton() : Button() {}
    StartButton(sf::Texture & texture) : Button(texture) { }
    void onClick( sf::RenderWindow & renderWindow);
    
    int maxMoves;
};

class ScoreButton : public Button{
public:
    ScoreButton() : Button() {}
    ScoreButton( sf::Texture & texture) : Button(texture) { }
    void onClick( sf::RenderWindow & renderWindow);
};

class QuitButton : public Button{
public:
    QuitButton() : Button() {}
    QuitButton( sf::Texture & texture) : Button(texture) { }
    void onClick( sf::RenderWindow & renderWindow);
};


#endif	/* FUNCTIONBUTTONS_HPP */

