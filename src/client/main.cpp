#include <iostream>

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
    const char* forest_path = "/root/Documents/plt_true/res/hexagon-pack/PNG/forest.png";
//    char castle_path = "/root/Documents/plt_true/res/hexagon-pack/PNG/castle.png";
//    char swamp_path = "/root/Documents/plt_true/res/hexagon-pack/PNG/swamp.png";
//    char ruin_path = "/root/Documents/plt_true/res/hexagon-pack/PNG/ruin.png";
//    char stoneage_path = "/root/Documents/plt_true/res/hexagon-pack/PNG/stoneage.png";

    // create the window
    sf::VideoMode vm(1024, 768);
    sf::RenderWindow window(vm , "My window", sf::Style::Fullscreen); //sf::Style::Fullscreen or Default

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
//        sf::IntRect ut_rec(-120,-140, 120, 140);
//        sf::Texture texture;
//        if(!texture.loadFromFile(, ut_rec))
//            return 0;
//        sf::Sprite sprite;
//        sprite.setTexture(texture);
//        window.draw(sprite);
        // create an array of 3 vertices that define a hexa primitive
        sf::VertexArray hexa(sf::TriangleFan, 8);

        // define the position of the hexa's points
        hexa[0].position = sf::Vector2f(60, 70);
        hexa[1].position = sf::Vector2f(60, 0);
        hexa[2].position = sf::Vector2f(0, 35);
        hexa[3].position = sf::Vector2f(0, 105);
        hexa[4].position = sf::Vector2f(60, 140);
        hexa[5].position = sf::Vector2f(120, 105);
        hexa[6].position = sf::Vector2f(120, 35);
        hexa[7].position = sf::Vector2f(60, 0);

        // define texture area of hexa
        hexa[0].texCoords = sf::Vector2f(60, 70);
        hexa[1].texCoords = sf::Vector2f(60, 0);
        hexa[2].texCoords = sf::Vector2f(0, 35);
        hexa[3].texCoords = sf::Vector2f(0, 105);
        hexa[4].texCoords = sf::Vector2f(60, 140);
        hexa[5].texCoords = sf::Vector2f(120, 105);
        hexa[6].texCoords = sf::Vector2f(120, 35);
        hexa[7].texCoords = sf::Vector2f(60, 0);

        sf::Texture texture;
        if(!texture.loadFromFile(forest_path))
            return 0;

        // draw
        window.draw(hexa, &texture);

        // end the current frame
        window.display();
    }
    return 0;
}
