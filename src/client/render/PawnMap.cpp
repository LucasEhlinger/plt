#include <iostream>
#include "PawnMap.h"

using namespace render;

bool PawnMap::load(const std::string &pawnset, sf::Vector2u tileSize, unsigned int *level, const unsigned int nb_row, const unsigned int nb_col) {
    // load the pawnset texture
    if (!m_pawnset.loadFromFile(pawnset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(nb_col * nb_row * 3 * 4);

    // populate the vertex array, with one pawnagon per tile
    for (unsigned int i = 0; i < nb_row; ++i) {
        unsigned int odd_offset = 0;

        if (i % 2 == 0)
            odd_offset = tileSize.x / 2;

        for (unsigned int j = 0; j < nb_col; ++j) {

            if (level[i * nb_row + j] == 9)
                continue;

            else {
                // get the current tile type
                int pawnNumber = level[i * nb_row + j];

                // get a pointer to the current tile's pawnagone
                sf::Vertex *pawn = &m_vertices[(i + j * nb_col) * 3 * 4];

                // set pawn position
                pawn[0].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                               tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                pawn[1].position = sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                                               0 + tileSize.y * 3 / 4 * i);
                pawn[2].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                               tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                pawn[3].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                               tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                pawn[4].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                               tileSize.y * 3 / 4 + tileSize.y * 3 / 4 * i);
                pawn[5].position = sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                                               tileSize.y + tileSize.y * 3 / 4 * i);
                pawn[6].position = sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                                               tileSize.y + tileSize.y * 3 / 4 * i);
                pawn[7].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                               tileSize.y * 3 / 4 + tileSize.y * 3 / 4 * i);
                pawn[8].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                               tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                pawn[9].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                               tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                pawn[10].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                                tileSize.y / 4 + tileSize.y * 3 / 4 * i);
                pawn[11].position = sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                                                tileSize.y + tileSize.y * 3 / 4 * i);

                // texture coord
                pawn[0].texCoords = sf::Vector2f(tileSize.x + tileSize.x * pawnNumber,
                                                tileSize.y / 4);
                pawn[1].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x * pawnNumber,
                                                0);
                pawn[2].texCoords = sf::Vector2f(0 + tileSize.x * pawnNumber,
                                                tileSize.y / 4);
                pawn[3].texCoords = sf::Vector2f(0 + tileSize.x * pawnNumber,
                                                tileSize.y / 4);
                pawn[4].texCoords = sf::Vector2f(0 + tileSize.x * pawnNumber,
                                                tileSize.y * 3 / 4);
                pawn[5].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x * pawnNumber,
                                                tileSize.y);
                pawn[6].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x * pawnNumber,
                                                tileSize.y);
                pawn[7].texCoords = sf::Vector2f(tileSize.x + tileSize.x * pawnNumber,
                                                tileSize.y * 3 / 4);
                pawn[8].texCoords = sf::Vector2f(tileSize.x + tileSize.x * pawnNumber,
                                                tileSize.y / 4);
                pawn[9].texCoords = sf::Vector2f(tileSize.x + tileSize.x * pawnNumber,
                                                tileSize.y / 4);
                pawn[10].texCoords = sf::Vector2f(0 + tileSize.x * pawnNumber,
                                                 tileSize.y / 4);
                pawn[11].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x * pawnNumber,
                                                 tileSize.y);
            }
        }
    }

    return true;
}

void PawnMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the pawnset texture
    states.texture = &m_pawnset;

    // draw the vertex array
    target.draw(m_vertices, states);
}
