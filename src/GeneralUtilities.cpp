#ifndef GENERALUTILITIES_CPP
#define GENERALUTILITIES_CPP
#define PI (2*acos(0))

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

class Score{
public:
    Score( std::string name, long long score) : name(name), _score(score) {}
    
    std::string name;
    long long _score;
    bool operator<( const Score & other) const{
        return _score> other._score;
    }
};

void saveScore(const Score & score){
    std::fstream file("ut.bin");
    std::vector<Score> scores;
    scores.push_back(score);
    std::string name; long long val;
    while( file >>name >> name >> val ){
        scores.push_back( Score(name, val) );
    }
    std::sort(scores.begin(), scores.end());
    file.close();
    file.open("ut.bin", std::fstream::out | std::fstream::trunc );
    for(int i=1; i<11 && i<= scores.size(); ++i){
        file << i <<". " << scores[i-1].name << " " << scores[i-1]._score << std::endl;
    }
    file.close();
}

#endif
