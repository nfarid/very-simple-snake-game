
#ifndef ASSET_MANAGER_HPP_56
#define ASSET_MANAGER_HPP_56

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>


namespace Core {

class AssetManager {
public:
    //                //name of texture           //file
    void loadTexture(const std::string& name, const std::string& fileName );
    const sf::Texture& getTexture( const std::string& name ) const;

    void loadFont( const std::string& name, const std::string& fileName );
    const sf::Font& getFont( const std::string& name ) const;

    void loadBuffer( const std::string& name, const std::string& fileName );
    const sf::SoundBuffer& getBuffer( const std::string& name ) const;
private:
    //name, resource pairs
    std::unordered_map<std::string,sf::Texture> texturesM;
    std::unordered_map<std::string,sf::Font> fontsM;
    std::unordered_map<std::string,sf::SoundBuffer> bufferM;
};

} //end of namespace Core

#endif // ASSET_MANAGER_HPP_56
