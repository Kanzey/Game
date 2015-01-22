#ifndef MENU_HPP
#define	MENU_HPP

class Menu {
private:
    sf::Texture texture1, startTex, scoreTex, quitTex;
    StartButton startBut;
    ScoreButton scoreBut;
    QuitButton quitBut;
    sf::RenderTexture renderTexture;
    ObjectTextures objectTextures;
    
public:
    Menu(std::string texPath1);

    inline void loadTextures(std::string texPath1);
    void create(int x, int y);
    inline void resize(int x, int y);
    inline void create(const sf::Vector2i & size);
    inline void draw(sf::RenderWindow & window);
    void placeButtons(int x, int y);
    void start(sf::RenderWindow & window);
};

#endif	/* MENU_HPP */

