#include "ObjectTextures.hpp"

ObjectTextures::ObjectTextures() { }

ObjectTextures::ObjectTextures(int texNum , std::string PATH){
	std::string tmp;
	std::fstream file( PATH.c_str() );
	sf::Texture texture;
	for(int i=0; i<texNum; ++i){
		getline(file,tmp);
		texture.loadFromFile( tmp.c_str() );
		Textures.push_back( std::make_shared<sf::Texture>( texture ) );
	}
	srand(time(NULL));
}

ObjectTextures::ObjectTextures( std::string PATH ){
	std::string tmp;
	std::fstream file( PATH.c_str() );
	sf::Texture texture;
	while( getline(file,tmp) ){
		texture.loadFromFile( tmp.c_str() );
                texture.setSmooth(true);
		Textures.push_back( std::make_shared<sf::Texture>( texture ) );
	}
	srand(time(NULL));
}

TwT ObjectTextures::random(){
	int _random = rand() % Textures.size();
	return std::make_pair(_random, Textures[_random].get() );
}

size_t ObjectTextures::size(){
	return Textures.size();
}

sf::Texture* ObjectTextures::operator[](unsigned int num ){
	return Textures[num].get();
}
