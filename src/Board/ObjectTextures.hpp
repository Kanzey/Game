#ifndef F_OBJECTTEXTURES
#define F_OBJECTTEXTURES

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <SFML/Graphics.hpp>

#define TwT std::pair<int,sf::Texture*>

//
// Class used to manage textures of objects.
//
class ObjectTextures{
private:
	// changed to shared pointers :P
	std::vector<std::shared_ptr<sf::Texture>> Textures;
public:	
	ObjectTextures();

	//store [texNum] textures precised in PATH file
	ObjectTextures(int texNum , std::string PATH );

	//store all textrue precised in PATH file;
	ObjectTextures(std::string PATH);
/*
	ObjectTextures( const ObjectTextures& other );

	ObjectTextures  operator=( const ObjectTextures& other);

	~ObjectTextures();
*/
	//return random Type and Texture*
	TwT random();

	size_t size();

	sf::Texture* operator[]( unsigned int num );

	
};

#endif
