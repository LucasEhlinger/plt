#include "Scene.h"
#include "state.h"
#include <iostream>
#include <string>

#define HEIGHT 13
using namespace render;

Scene::Scene(state::Board &board) {
    boardView = new BoardView{board};
    for (long unsigned int i = 0; i < tilesView.size(); ++i)
        if (this->boardView->board.tiles[i].exist) {
            tilesView[i] = new TileView(this->boardView->board.tiles[i]);
            boardView->board.tiles[i].addObserver(tilesView[i]);
        } else
            tilesView[i] = nullptr;

    for (long unsigned int i = 0; i < board.pawns.size(); ++i) {
        pawnsView.emplace_back(new PawnView(boardView->board.pawns[i]));
        board.pawns[i].addObserver(pawnsView[i]);
    }
}

std::array<int, 169> Scene::matrixTile() {
    std::array<int, 169> level;
    level.fill(9);
    for (int i = 0; i < HEIGHT; ++i)
        for (int j = 0; j < HEIGHT; ++j)
            if (tilesView[(i * HEIGHT) + j] != NULL)
                level[i * HEIGHT + j] = tilesView[(i * HEIGHT) + j]->tile.number_type;

    return level;
}

std::array<int, 169> Scene::matrixPawn() {
    std::array<int, 169> table;
    table.fill(9);

    //for all pawns displayed
    for (long unsigned int i = 0; i < pawnsView.size(); ++i)
        //set to the element of the coordinate of this pawn the value of his number_type
        table.at(pawnsView.at(i)->pawn.getCoordinate().getCoordInLine()) = pawnsView.at(i)->pawn.number_type;
    return table;
}

