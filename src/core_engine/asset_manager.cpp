
#include "asset_manager.hpp"
#include "../util/get_dir.hpp"
#include "./load_exception.hpp"

namespace  {
    const auto res_dir = Util::get_resource_dir();
}

namespace Core {

void AssetManager::loadTexture(const std::string& name, const std::string& fileName ) {
    sf::Texture tex;
    if( tex.loadFromFile(res_dir + fileName) )
        texturesM[name] = tex;
    else
        throw LoadException{("Couldn't load " + res_dir + fileName).c_str()};
}

const sf::Texture& AssetManager::getTexture( const std::string& name ) const {
    return  texturesM.at(name);
}

void AssetManager::loadFont( const std::string& name, const std::string& fileName ) {
    sf::Font fon;
    if( fon.loadFromFile(res_dir + fileName) )
        fontsM[name] = fon;
}

const sf::Font& AssetManager::getFont( const std::string& name ) const {
    return  fontsM.at(name);
}

void AssetManager::loadBuffer( const std::string& name, const std::string& fileName ) {
    sf::SoundBuffer sound;
    if( sound.loadFromFile(res_dir + fileName) )
        bufferM[name] = sound;
}

const sf::SoundBuffer& AssetManager::getBuffer( const std::string& name ) const  {
    return  bufferM.at(name);
}

}//end of namespace Core
