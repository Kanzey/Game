#include "ObjectTextures.hpp"

ObjectTextures::ObjectTextures() { }

ObjectTextures::ObjectTextures(int texNum , std::string PATH){
	std::string tmp;
	std::fstream file( PATH.c_str() );
	for(int i=0; i<texNum; ++i){
		getline(file,tmp);
		Textures.push_back( new sf::Texture );
		Textures.back()->loadFromFile( tmp.c_str() );
	}
	srand(time(NULL));
}

ObjectTextures::ObjectTextures( std::string PATH ){
	std::string tmp;
	std::fstream file( PATH.c_str() );
	while( getline(file,tmp) ){
		Textures.push_back( new sf::Texture );
		Textures.back()->loadFromFile( tmp.c_str() );
	}
	srand(time(NULL));
}

ObjectTextures::ObjectTextures( const ObjectTextures& other ){
	for(std::vector<sf::Texture*>::const_iterator it = other.Textures.begin(); it != other.Textures.end(); ++it){
		Textures.push_back( new sf::Texture );
		*( Textures.back() ) = *(*it);
	}
}

ObjectTextures ObjectTextures::operator=( const ObjectTextures & other){
		Textures.clear();
	for(std::vector<sf::Texture*>::const_iterator it = other.Textures.begin(); it != other.Textures.end(); ++it){
		Textures.push_back( new sf::Texture );
		*(Textures.back() )= *(*it);
	}
	return *this;
}

ObjectTextures::~ObjectTextures(){
	for(std::vector<sf::Texture*>::iterator it = Textures.begin(); it != Textures.end(); ++it){
		delete  *it;
	}
}

TwT ObjectTextures::random(){
	int _random = rand() % Textures.size();
	return std::make_pair(_random, Textures[_random] );
}

size_t ObjectTextures::size(){
	return Textures.size();
}

sf::Texture* ObjectTextures::operator[](unsigned int num ){
	return Textures[num];
}
