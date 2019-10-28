#include "IObservable.h"
#include <algorithm>
#include "IObserver.h"

using namespace ::state;

void IObservable::addObserver(state::IObserver *observer) {
    this->observers.push_back(observer);
}

void IObservable::removeObserver(state::IObserver *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void IObservable::notify() {
    for (std::vector<IObserver *>::const_iterator iterator = observers.begin();
         iterator != observers.end(); ++iterator) {
        if (*iterator != 0) {
            (*iterator)->update(this);
        }
    }
}