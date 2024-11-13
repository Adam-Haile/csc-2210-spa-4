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
    State gameState = RUNNING;
    while (repeat) {
        while (gameState == RUNNING) {
            char action = startTurn();
            vector<string> messages = performAction(action);
            gameState = getGameState(action);
            if(gameState == RUNNING && !interactions.empty()) {
                view->printMessages(interactions);
                interactions.clear();
            }
            if(gameState == RUNNING && !messages.empty()) {
                view->printMessages(messages);
            }
        }
        endRound(gameState);
        view->printLine("Do you want to try again for an even better grade? [Y/n]: ");
        repeat = view->getInput(vector<char>{"Y","N"}) == 'Y';
        if(repeat) resetGame();
    }
    endGame(gameState);
}

char GameController::startTurn() {
    vector<char> menuOptions = vector<char>{'H', 'M', 'Q', 'U', '*'};
    vector<char> directions = map->getValidDirections(player);
    menuOptions.insert(menuOptions.begin(), directions.begin(), directions.end());
    vector<string> inventory = player->getInventory();
    if(mode == DEFAULT) {
        view->printState(directions,inventory);
    } else {
        vector<string> localMap = view->generateLocalMap(
            map, player->x, player->y, mode==DEBUG);
        view->printState(directions, inventory, localMap);
        // view->printMessages(localMap);
    }
    char action = view->getInput(menuOptions);
    return action;
}

vector<string> GameController::performAction(char action) {
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
        } break;
        case '*': setSettings(); break;
        case 'N': interactions = movePlayer(0,-1); break;
        case 'E': interactions = movePlayer(1,0); break;
        case 'S': interactions = movePlayer(0,1); break;
        case 'W': interactions = movePlayer(-1,0); break;
        default: break;
    }
    return player->search(map);
}

vector<string> GameController::movePlayer(int difX, int difY) {
    int newX = player->x + difX;
    int newY = player->y + difY;
    map->moveToRoom(newX, newY, player);
    Room *room = map->getRoom(newX, newY);
    vector<string> messages = room->interactAll(player);
    if (player->watched && !room->contains(CameraZone::getInstance())) {
        player->watched = false;
        messages.push_back(CameraZone::getInstance()->getLeftMessage());
    }
    if (room->contains(Mask::getInstance())) {
        room->removeEntity(Mask::getInstance());
    }
    if (room->contains(Homework::getInstance())) {
        room->removeEntity(Homework::getInstance());
    }
    return messages;
}

void GameController::useItem(char direction, RoomEntity* item) {
    int x = player->x;
    int y = player->y;
    switch(direction){
        case 'N': map->getRoom(x, y-1)->interactAll(item); break;
        case 'E': map->getRoom(x+1, y)->interactAll(item); break;
        case 'S': map->getRoom(x, y+1)->interactAll(item); break;
        case 'W': map->getRoom(x-1, y)->interactAll(item); break;
    }
}

GameController::State GameController::getGameState(char action) {
    State gamestate = RUNNING;
    if (action == 'Q') gamestate = QUIT;
    if (!player->alive) gamestate = LOST;
    if (player->won) gamestate = WON;
    return gamestate;
}

void GameController::setSettings() {
    //in color
    // view->printLine("Color: Current[" + string(color ? "On" : "Off") + "] ", false);
    // view->printLine("Do you want color [Y/n]: ", true);
    // color = view->getInput(vector<char>{'Y','N'}) == 'Y';
    //default, minimap, or debug
    view->printLine("Minimap: Current[", false);
    switch(mode) {
        case MINIMAP: view->printLine("On", false); break;
        case DEBUG: view->printLine("DEBUG", false); break;
        default: view->printLine("Off", false); break;
    }
    view->printLine("] Do you want a minimap [Y/n]: ", true);
    char choice = view->getInput(vector<char>{'Y','N','D'});
    switch(choice) {
        case 'Y': mode = MINIMAP; break;
        case 'D': mode = DEBUG; break;
        default: mode = DEFAULT; break;
    }
}

void GameController::endRound(State gameState) {
    switch (gameState) {
        case QUIT: view->printLine("You have given up, good luck next time!"); break;
        case LOST: view->printLine("You have failed your course"); break;
        case WON: view->printLine("You have succeeded at your heist"); break;
    }
}

void GameController::endGame(State gameState) {
    view->printLine("Do your homework next time!");
}

void GameController::resetGame() {
    delete map;
    map = new Map(player->x, player->y);
    interactions.clear();
}
