#ifndef GENERALUTILITIES_CPP
#define GENERALUTILITIES_CPP
#define PI 3.14159265

sf::RectangleShape createLine(sf::Vector2f A, sf::Vector2f B, int thicknes){
    double x = A.x-B.x;
    double y = A.y-B.y;
    double r = hypot(x,y);
    double rotate = atan2(x,y);
    sf::RectangleShape line(sf::Vector2f(r,thicknes));
#ifdef DBG
    std::cout << x << " " << y << std::endl;
#endif
    line.rotate(270 - rotate*180/PI);
    line.setPosition(A);
    line.move(-thicknes*y/r/2, thicknes*x/r/2);
    return line;
}

int calcDist( sf::Vector2f A, sf::Vector2f B){
    return hypot(A.x-B.x, A.y-B.y);
}

#endif
