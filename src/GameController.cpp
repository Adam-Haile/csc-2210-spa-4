//
// Created by milleraa on 10/29/2024.
//

#include "GameController.h"

using namespace std;

GameController::GameController(View* view) {
    this->view = view;
    map = new Map();
    player = Player::getInstance();
}

GameController::~GameController() {
    delete map;
}

void GameController::startGame() {
    state gameState = RUNNING;
    while (gameState == RUNNING) {
        char action = startTurn();
        performAction(action);
        gameState = getGameState(action);
    }
    endGame(gameState);
}

char GameController::startTurn() {
    vector<char> directions = map->getValidDirections(player);
    view->printState(directions, vector<string>{});
    char action = view->getInput(vector<char>{'N', 'E', 'S', 'W', 'H', 'M', 'Q'});
    return action;
}

void GameController::performAction(char action) {
    switch (action) {
        case 'H': view->printLine(help_message); break;
        case 'M': view->printMap(map); break;
        case 'Q': break;
        case 'N': movePlayer(-1,0); break;
        case 'E': movePlayer(0,1); break;
        case 'S': movePlayer(1,0);break;
        case 'W': movePlayer(0,-1);break;
        default: break;
    }
}

void GameController::movePlayer(int difX, int difY) {
    if (map->movePlayer(difX,difY)) {
        view->printMessages(player->search(map));
    }
}

GameController::state GameController::getGameState(char action) {
    state gamestate = RUNNING;
    if (action == 'Q') gamestate = QUIT;
    if (!player->alive) gamestate = LOST;
    if (player->won) gamestate = WON;
    return gamestate;
}

void GameController::endRound(int gameState) {
}

void GameController::endGame(int gameState) {
    if (gameState == 0) {
        view->printLine("Game Over");
    }
}

void GameController::resetGame() {
}
