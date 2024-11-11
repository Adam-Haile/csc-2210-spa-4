//
// Created by milleraa on 10/29/2024.
//

#include "GameController.h"

using namespace std;

GameController::GameController(View* view) {
    this->view = view;
    map = new Map();
    player = Player::getInstance();
    vector<string> interactions;
}

GameController::~GameController() {
    delete map;
}

void GameController::startGame() {
    bool repeat = true;
    state gameState = RUNNING;
    while (repeat) {
        while (gameState == RUNNING) {
            char action = startTurn();
            vector<string> messages = performAction(action);
            gameState = getGameState(action);
            if(gameState == RUNNING && !interactions.empty()) {
                view->printMessages(messages);
                view->printMessages(interactions);
            }
        }
        endRound(gameState);
    }
    endGame(gameState);
}

char GameController::startTurn() {
    vector<char> menuOptions = vector<char>{'H', 'M', 'Q', 'U'};
    vector<char> directions = map->getValidDirections(player);
    menuOptions.insert(menuOptions.begin(), directions.begin(), directions.end());
    vector<string> inventory = player->getInventory();

    view->printState(directions, inventory);
    char action = view->getInput(menuOptions);
    return action;
}

vector<string> GameController::performAction(char action) {
    interactions.clear();
    switch (action) {
        case 'H': view->printLine(help_message); break;
        case 'M': view->printMap(map); break;
        case 'Q': break;
        case 'U': {
            vector<char> valid_directions = map->getValidDirections(player);
            view->printLine("Use item in direction: ", false);
            view->printValidDirections(valid_directions);
            view->printLine("", true);
            char dir = view->getInput(valid_directions);
            useItem(dir, Homework::getInstance());
        }
        case 'N': interactions = movePlayer(0,1); break;
        case 'E': interactions = movePlayer(1,0); break;
        case 'S': interactions = movePlayer(0,-1); break;
        case 'W': interactions = movePlayer(-1,0); break;
        default: break;
    }
    return player->search(map);
}

vector<string> GameController::movePlayer(int difX, int difY) {
    int newX = player->x + difX;
    int newY = player->y + difY;
    map->moveToRoom(newX, newY, player);
    return map->getRoom(newX, newY)->interactAll(player);
}

void GameController::useItem(char direction, RoomEntity* item) {
    int x = player->x;
    int y = player->y;
    switch(direction){
        case 'N': map->getRoom(x, y+1)->interactAll(item); break;
        case 'E': map->getRoom(x+1, y)->interactAll(item); break;
        case 'S': map->getRoom(x, y-1)->interactAll(item); break;
        case 'W': map->getRoom(x-1, y)->interactAll(item); break;
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
