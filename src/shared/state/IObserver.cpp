#include "IObserver.h"
#include "Tile.h"
#include "../../client/render/TileVue.h"

using namespace state;

void IObserver::update(state::IObservable &obj, int iMyEntityType) {
    state::Tile *tile = (state::Tile *) &obj;

    switch (iMyEntityType) {
        case 1:
            state::Tile tile = static_cast<Tile &>(obj);
            this = static_cast<render::TileVue*>(this);
            this->update(obj);
            break;


    }


    if (reinterpret_cast<state::Tile>(obj) != NULL) {

    }

    printf("pourquoi ??");
};