#include "Menu.cpp"
#include <cstdlib>

int main(int argc, char** argv) {
    sf::RenderWindow renderWindow( sf::VideoMode(1200,800), "GAME" );
    Menu menu("../Textures/grass.jpg");
    menu.start( renderWindow );
    return 0;
}

