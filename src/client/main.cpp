#include <iostream>
#include "client.h"
#include <string.h>

using namespace std;
using namespace client;

int main(int argc, char *argv[]) {
    TestRending test{};
    if (argc == 2) {
        if (strcmp(argv[1], "hello") == 0) {
            cout << "Bonjour à tous !" << endl;
        } else if (strcmp(argv[1], "render") == 0) {
            test.render();
        } else if (strcmp(argv[1], "engine") == 0) {
            test.engine();
        } else if (strcmp(argv[1], "random_ai") == 0) {
            test.ia();
        } else if (strcmp(argv[1], "heuristic_ai") == 0) {
            test.heuristic_ai();
        } else if (strcmp(argv[1], "thread") == 0) {
            test.thread();
        }
    } else {
        cout << "Je n'ai pas compris, entrez une de ces commandes :" << endl;
        cout << "hello, render, engine, random_ai, heuristic_ai & thread" << endl;
    }
    return 0;
}