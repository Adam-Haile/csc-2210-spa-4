//
// Created by milleraa on 10/29/2024.
//

#include "GameController.h"

using namespace std;

GameController::GameController(View* view) {
    this->view = view;
    map = new Map();
    // player = Player::getInstance();
}

GameController::~GameController() {
    delete map;
}

void GameController::startGame() {
    int gameState = 1;
    while (gameState == 1) {
        char action = startTurn();
        performAction(action);
        gameState = getGameState(action);
    }
    endGame(gameState);
}

char GameController::startTurn() {
    vector<char> directions = {'N', 'E', 'S', 'W'};
    view->printState(directions, vector<string>{});
    char action = view->getInput(vector<char>{'N', 'E', 'S', 'W', 'H', 'M', 'Q'});
    return action;
}

void GameController::performAction(char action) {
    switch (action) {
        case 'H': view->printLine(help_message); break;
        case 'M': view->printMap(map); break;
        case 'Q': break;
        default: break;
    }
}

int GameController::getGameState(char action) {
    return action != 'Q' && action != 'q';
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
