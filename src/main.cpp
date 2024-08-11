//
// Created by Voric on 11/08/2024.
//

#include "../include/Game.h"
#include "../include/MenuState.h"

int main() {
    Game game;
    game.pushState(std::make_shared<MenuState>());
    game.run();
    return 0;
}