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
    const int screen_width = 1536;
    const int screen_height = 860;
    const int nb_row = 13;
    const int nb_col = nb_row;
    const int middle_row = (nb_row+nb_row%2)/2;
    const int off_mar_X = 172;
    const int off_mar_Y = 10;
    const int tile_w = 72;
    const int tile_h = 84;
    const int shift_X = tile_w/2;
    const int shift_Y = tile_h*3/4;
    const int ite_row = tile_w;
    const int ite_col = tile_h*3/4;

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
    sf::VideoMode vm(screen_width, screen_height);
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
        /* A bit tricky, before defining the shape of the vertex, we set what will be the 'texturabale' area,
        without knowing if it will fit in the vertex. We assume that we know what we are doing and that at worst
        this area can be wider, the texture won't leak. */
        tile[0].texCoords = sf::Vector2f(tile_w/2, tile_h/2);
        tile[1].texCoords = sf::Vector2f(tile_w/2, 0);
        tile[2].texCoords = sf::Vector2f(0, tile_h/4);
        tile[3].texCoords = sf::Vector2f(0, tile_h*3/4);
        tile[4].texCoords = sf::Vector2f(tile_w/2, tile_h);
        tile[5].texCoords = sf::Vector2f(tile_w, tile_h*3/4);
        tile[6].texCoords = sf::Vector2f(tile_w, tile_h/4);
        tile[7].texCoords = sf::Vector2f(tile_w/2, 0);

        int nb_tiles;
        for(int i =  0; i<nb_row; ++i){
            int odd_offset = 0;
            nb_tiles = nb_col-abs(middle_row-1-i);
            if(nb_tiles%2 == 1) {
                // define the position of the tile's points
                // If odd number of tiles, we have to put a tile in the middle of the line
                tile[0].position = sf::Vector2f(screen_width / 2, off_mar_Y + tile_h / 2 + ite_col * i);
                tile[1].position = sf::Vector2f(screen_width / 2, off_mar_Y + 0 + ite_col * i);
                tile[2].position = sf::Vector2f(screen_width / 2 - tile_w / 2,
                        off_mar_Y + tile_h / 4 + ite_col * i);
                tile[3].position = sf::Vector2f(screen_width / 2 - tile_w / 2,
                        off_mar_Y + tile_h * 3 / 4 + ite_col * i);
                tile[4].position = sf::Vector2f(screen_width / 2, off_mar_Y + tile_h + ite_col * i);
                tile[5].position = sf::Vector2f(screen_width / 2 + tile_w / 2,
                        off_mar_Y + tile_h * 3 / 4 + ite_col * i);
                tile[6].position = sf::Vector2f(screen_width / 2 + tile_w / 2,
                        off_mar_Y + tile_h / 4 + ite_col * i);
                tile[7].position = sf::Vector2f(screen_width / 2, off_mar_Y + 0 + ite_col * i);
                // draw
                window.draw(tile, &texCastle);

                odd_offset = tile_w / 2;
                --nb_tiles;
            }
            for(int j = 0; j<nb_tiles/2; ++j) {
                tile[0].position = sf::Vector2f(screen_width / 2 + odd_offset + tile_w / 2 + ite_row * j,
                                                off_mar_Y + tile_h / 2 + ite_col * i);
                tile[1].position = sf::Vector2f(screen_width / 2 + odd_offset + tile_w / 2 + ite_row * j,
                                                off_mar_Y + 0 + ite_col * i);
                tile[2].position = sf::Vector2f(screen_width / 2 + odd_offset + 0 + ite_row * j,
                                                off_mar_Y + tile_h / 4 + ite_col * i);
                tile[3].position = sf::Vector2f(screen_width / 2 + odd_offset + 0 + ite_row * j,
                                                off_mar_Y + tile_h * 3 / 4 + ite_col * i);
                tile[4].position = sf::Vector2f(screen_width / 2 + odd_offset + tile_w / 2 + ite_row * j,
                                                off_mar_Y + tile_h + ite_col * i);
                tile[5].position = sf::Vector2f(screen_width / 2 + odd_offset + tile_w + ite_row * j,
                                                off_mar_Y + tile_h * 3 / 4 + ite_col * i);
                tile[6].position = sf::Vector2f(screen_width / 2 + odd_offset + tile_w + ite_row * j,
                                                off_mar_Y + tile_h / 4 + ite_col * i);
                tile[7].position = sf::Vector2f(screen_width / 2 + odd_offset + tile_w / 2 + ite_row * j,
                                                off_mar_Y + 0 + ite_col * i);
                // draw
                window.draw(tile, &texField);
            }
            for(int j = 0; j<nb_tiles/2; ++j) {
                tile[0].position = sf::Vector2f(screen_width / 2 - odd_offset + tile_w / 2 - ite_row * (j+1),
                                                off_mar_Y + tile_h / 2 + ite_col * i);
                tile[1].position = sf::Vector2f(screen_width / 2 - odd_offset + tile_w / 2 - ite_row * (j+1),
                                                off_mar_Y + 0 + ite_col * i);
                tile[2].position = sf::Vector2f(screen_width / 2 - odd_offset + 0 - ite_row * (j+1),
                                                off_mar_Y + tile_h / 4 + ite_col * i);
                tile[3].position = sf::Vector2f(screen_width / 2 - odd_offset + 0 - ite_row * (j+1),
                                                off_mar_Y + tile_h * 3 / 4 + ite_col * i);
                tile[4].position = sf::Vector2f(screen_width / 2 - odd_offset + tile_w / 2 - ite_row * (j+1),
                                                off_mar_Y + tile_h + ite_col * i);
                tile[5].position = sf::Vector2f(screen_width / 2 - odd_offset + tile_w - ite_row * (j+1),
                                                off_mar_Y + tile_h * 3 / 4 + ite_col * i);
                tile[6].position = sf::Vector2f(screen_width / 2 - odd_offset + tile_w - ite_row * (j+1),
                                                off_mar_Y + tile_h / 4 + ite_col * i);
                tile[7].position = sf::Vector2f(screen_width / 2 - odd_offset + tile_w / 2 - ite_row * (j+1),
                                                off_mar_Y + 0 + ite_col * i);
                // draw
                window.draw(tile, &texSwamp);
            }
        }

        // end the current frame
        window.display();
    }
    return 0;
}
