#include "Scene.h"
#include "state.h"

using namespace render;

Scene::Scene(sf::RenderWindow &window, sf::View &view) : window(window), view(view) {
    state::Board board{};
    board.generate();
    boardView = new BoardView{board};
    for (int i = 0; i < tilesView.size(); ++i) {
        tilesView[i] = new TileView(*boardView->board.tiles[i]);
        boardView->board.tiles[i]->addObserver(tilesView[i]);
    }
    for (int i = 0; i < board.pawns.size(); ++i) {
        pawnsView[i] = new PawnView(*boardView->board.pawns[i]);
        boardView->board.pawns[i]->addObserver(pawnsView[i]);
    }
}
void Scene::draw() {

}