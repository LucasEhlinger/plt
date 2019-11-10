#include "Scene.h"
#include "state.h"
#include <iostream>
#include <string>

#define HEIGHT 13
using namespace render;

Scene::Scene() {
    state::Board board{};
    board.generate();
    boardView = new BoardView{board};
    for (long unsigned int i = 0; i < tilesView.size(); ++i) {
        if (board.tiles[i] != NULL) {
            tilesView[i] = new TileView(*board.tiles[i]);
            boardView->board.tiles[i]->addObserver(tilesView[i]);
        } else {
            tilesView[i] = nullptr;
        }
    }
    for (long unsigned int i = 0; i < board.pawns.size(); ++i) {
        pawnsView[i] = new PawnView(*board.pawns[i]);
        boardView->board.pawns[i]->addObserver(pawnsView[i]);
    }
}

void Scene::draw(unsigned int level[13 * 13]) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            if (tilesView[(i * HEIGHT) + j] != nullptr)
                level[i * HEIGHT + j] = tilesView[(i * HEIGHT) + j]->tile.number_type;
            else
                level[i * HEIGHT + j] = 9;
        }
    }
}