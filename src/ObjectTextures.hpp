#ifndef F_OBJECTTEXTURES
#define F_OBJECTTEXTURES

#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#define TwT std::pair<int,sf::Texture*>

//
// Class used to manage textures of objects.
//
//
class ObjectTextures{
private:
	// its wiser to store pointers to Textures in vector than Textures.
	std::vector<sf::Texture*> Textures;
public:	
	ObjectTextures();

	//store [texNum] textures precised in PATH file
	ObjectTextures(int texNum , std::string PATH );

	//store all textrue precised in PATH file;
	ObjectTextures(std::string PATH);

	ObjectTextures( const ObjectTextures& other );

	ObjectTextures  operator=( const ObjectTextures& other);

	~ObjectTextures();

	//return random Type and Texture*
	TwT random();

	size_t size();

	sf::Texture* operator[]( unsigned int num );

	
};

#endif
