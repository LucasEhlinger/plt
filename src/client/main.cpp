#include <iostream>
#include <array>
#include <string.h>
#include "render.h"

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML
#include "state.h"

using namespace std;

// From sfml doc, turning verteces into entities, here a map
class TileMap : public sf::Drawable, public sf::Transformable {
public:

    bool load(const std::string &tileset, sf::Vector2u tileSize, const int *tiles, unsigned int nb_col,
              unsigned int nb_row) {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(nb_col * nb_row * 3 * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < nb_col; ++i) {
            unsigned int odd_offset = 0;
            for (unsigned int j = 0; j < nb_row; ++j) {
                if (tiles[i * nb_row + j] == 9)
                    continue;
                else {
                    // get the current tile type
                    int tileNumber = tiles[i * nb_row + j];

                    // get a pointer to the current tile's quad
                    sf::Vertex *hex = &m_vertices[(i + j * nb_col) * 3 * 4];

                    if (i % 2 == 1)
                        odd_offset = tileSize.x / 2;

                    hex[0].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                                   tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                    hex[1].position = sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                                                   0 + tileSize.y * 3 / 4 * i);
                    hex[2].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                                   tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                    hex[3].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                                   tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                    hex[4].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                                   tileSize.y * 3 / 4 + tileSize.y * 3 / 4 * i);
                    hex[5].position = sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                                                   tileSize.y + tileSize.y * 3 / 4 * i);
                    hex[6].position = sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                                                   tileSize.y + tileSize.y * 3 / 4 * i);
                    hex[7].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                                   tileSize.y * 3 / 4 + tileSize.y * 3 / 4 * i);
                    hex[8].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                                   tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                    hex[9].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                                   tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                    hex[10].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                                    tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                    hex[11].position = sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                                                    tileSize.y + tileSize.y * 3 / 4 * i);

                    hex[0].texCoords = sf::Vector2f(tileSize.x + tileSize.x * tileNumber,
                                                    tileSize.y / 4);
                    hex[1].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x * tileNumber,
                                                    0);
                    hex[2].texCoords = sf::Vector2f(0 + tileSize.x * tileNumber,
                                                    tileSize.y / 4);
                    hex[3].texCoords = sf::Vector2f(0 + tileSize.x * tileNumber,
                                                    tileSize.y / 4);
                    hex[4].texCoords = sf::Vector2f(0 + tileSize.x * tileNumber,
                                                    tileSize.y * 3 / 4);
                    hex[5].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x * tileNumber,
                                                    tileSize.y);
                    hex[6].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x * tileNumber,
                                                    tileSize.y);
                    hex[7].texCoords = sf::Vector2f(tileSize.x + tileSize.x * tileNumber,
                                                    tileSize.y * 3 / 4);
                    hex[8].texCoords = sf::Vector2f(tileSize.x + tileSize.x * tileNumber,
                                                    tileSize.y / 4);
                    hex[9].texCoords = sf::Vector2f(tileSize.x + tileSize.x * tileNumber,
                                                    tileSize.y / 4);
                    hex[10].texCoords = sf::Vector2f(0 + tileSize.x * tileNumber,
                                                     tileSize.y / 4);
                    hex[11].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x * tileNumber,
                                                     tileSize.y);
                }
            }
        }
        return true;
    }

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

int testRender();

int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "hello") == 0) {
            cout << "Bonjour à tous !" << endl;
        } else if (strcmp(argv[1], "render") == 0) {
            render::Scene scene;
            scene.draw();
            //testRender();
        } else if (strcmp(argv[1], "engine") == 0) {

        }
    } else {
        cout << "Je n'ai pas compris, entrez une de ces commandes :" << endl;
        cout << "hello, render, engine" << endl;
    }
    return 0;
}

int testRender() {

    // create the window
    sf::RenderWindow window(sf::VideoMode(1536, 860), "Tilemap");

    render::Scene scene;
    scene.draw();

    // define the level with an array of tile indices
    const int level[] =
            {
                    0, 0, 0, 0,
                    1, 1, 1, 1,
                    2, 2, 2, 2,
                    3, 3, 3, 3
            };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("./../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(72, 84), level, 4, 4))
        return -1;

    // run the main loop
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
