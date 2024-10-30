//
// Created by milleraa on 10/29/2024.
//

#include "GameController.h"
#include "View.h"

int main() {
    View* view = new View();
    GameController* gc = new GameController(view);
    gc->startGame();
}
