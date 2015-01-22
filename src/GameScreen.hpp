
#ifndef GAMESCREEN_HPP
#define	GAMESCREEN_HPP

class GameScreen {
private:
    Background background;
    sf::RenderWindow & window;
    sf::Texture windowTexture, backgroundTexture;
    sf::Sprite windowSprite;
    CurveLine line;
    Board board;
public:
    GameScreen(int x, int y, int cross, int numOfPices, sf::RenderWindow & window);

    void start();
    void cleanStaticTexture();
    void highlight(int type);
    void staticDraw();
    void draw();

};



#endif	/* GAMESCREEN_HPP */

