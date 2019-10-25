#include <iostream>
#include <array>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML
#include "state.h"

using namespace std;

int main(int argc,char* argv[])
{
    int nb_row = 13;
    int nb_col = 13;

    const char* castle_path = "./../res/hexagon-pack/PNG/castle.png";
    const char* colony_path = "./../res/hexagon-pack/PNG/colony.png";
    const char* field_path = "./../res/hexagon-pack/PNG/field.png";
    const char* forest_path = "./../res/hexagon-pack/PNG/forest.png";
    const char* mountain_path = "./../res/hexagon-pack/PNG/mountain.png";
    const char* ruin_path = "./../res/hexagon-pack/PNG/ruin.png";
    const char* start_path = "./../res/hexagon-pack/PNG/start.png";
    const char* stoneage_path = "./../res/hexagon-pack/PNG/stoneage.png";
    const char* swamp_path = "./../res/hexagon-pack/PNG/swamp.png";

    sf::Texture texCastle;
    if(!texCastle.loadFromFile(castle_path))
        return 0;
    sf::Texture texColony;
    if(!texColony.loadFromFile(colony_path))
        return 0;
    sf::Texture texField;
    if(!texField.loadFromFile(field_path))
        return 0;
    sf::Texture texForest;
    if(!texForest.loadFromFile(forest_path))
        return 0;
    sf::Texture texMountain;
    if(!texMountain.loadFromFile(mountain_path))
        return 0;
    sf::Texture texRuin;
    if(!texRuin.loadFromFile(ruin_path))
        return 0;
    sf::Texture texStart;
    if(!texStart.loadFromFile(start_path))
        return 0;
    sf::Texture texStoneage;
    if(!texStoneage.loadFromFile(stoneage_path))
        return 0;
    sf::Texture texSwamp;
    if(!texSwamp.loadFromFile(swamp_path))
        return 0;

    // create the window
    sf::VideoMode vm(1280, 720);
    sf::RenderWindow window(vm , "Such_plt_WOW", sf::Style::Close); //sf::Style::Fullscreen or Default

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...

        // create an array of 8 vertices that define a tile primitive
        sf::VertexArray tile(sf::TriangleFan, 8);

        // define texture area of tile
        tile[0].texCoords = sf::Vector2f(36, 42);
        tile[1].texCoords = sf::Vector2f(36, 0);
        tile[2].texCoords = sf::Vector2f(0, 21);
        tile[3].texCoords = sf::Vector2f(0, 63);
        tile[4].texCoords = sf::Vector2f(36, 84);
        tile[5].texCoords = sf::Vector2f(72, 63);
        tile[6].texCoords = sf::Vector2f(72, 21);
        tile[7].texCoords = sf::Vector2f(36, 0);

        for(int i =  0; i<nb_row; ++i){
            for(int j = 0; j<nb_col; ++j){
                if(i%2 == 0){
                    // define the position of the tile's points
                    tile[0].position = sf::Vector2f(172+36+72*j, 0+42+63*i);
                    tile[1].position = sf::Vector2f(172+36+72*j, 0+0+63*i);
                    tile[2].position = sf::Vector2f(172+0+72*j, 0+21+63*i);
                    tile[3].position = sf::Vector2f(172+0+72*j, 0+63+63*i);
                    tile[4].position = sf::Vector2f(172+36+72*j, 0+84+63*i);
                    tile[5].position = sf::Vector2f(172+72+72*j, 0+63+63*i);
                    tile[6].position = sf::Vector2f(172+72+72*j, 0+21+63*i);
                    tile[7].position = sf::Vector2f(172+36+72*j, 0+0+63*i);

                    // draw
                    window.draw(tile, &texCastle);
                }
                else{
                    // define the position of the tile's points
                    tile[0].position = sf::Vector2f(172+36+36+72*j, 0+63+42+63*(i-1));
                    tile[1].position = sf::Vector2f(172+36+36+72*j, 0+63+0+63*(i-1));
                    tile[2].position = sf::Vector2f(172+36+0+72*j, 0+63+21+63*(i-1));
                    tile[3].position = sf::Vector2f(172+36+0+72*j, 0+63+63+63*(i-1));
                    tile[4].position = sf::Vector2f(172+36+36+72*j, 0+63+84+63*(i-1));
                    tile[5].position = sf::Vector2f(172+36+72+72*j, 0+63+63+63*(i-1));
                    tile[6].position = sf::Vector2f(172+36+72+72*j, 0+63+21+63*(i-1));
                    tile[7].position = sf::Vector2f(172+36+36+72*j, 0+63+0+63*(i-1));

                    // draw
                    window.draw(tile, &texMountain);
                }
            }
        }

        // end the current frame
        window.display();
    }
    return 0;
}
