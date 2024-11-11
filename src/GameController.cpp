//
// Created by milleraa on 10/29/2024.
//

#include "GameController.h"

using namespace std;

GameController::GameController(View* view) {
    this->view = view;
    map = new Map();
    player = Player::getInstance();
    vector<string> messages;
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
        if(gameState == RUNNING && !messages.empty()) {
            view->printMessages(messages);
        }
    }
    endRound(gameState);
    // endGame(gameState);
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

void GameController::performAction(char action) {
    messages.clear();
    switch (action) {
        case 'H': view->printLine(help_message); break;
        case 'M': view->printMap(map); break;
        case 'Q': break;
        case 'U': {
            vector<char> valid_directions = map->getValidDirections(player);
            view->printLine("Use item in direction: ");
            view->printValidDirections(valid_directions);
            view->printLine("", true);
            char dir = view->getInput(valid_directions);
            useItem(dir, Homework::getInstance());
        }
        //TODO verify directions
        case 'N': messages = movePlayer(-1,0); break;
        case 'E': messages = movePlayer(0,1); break;
        case 'S': messages = movePlayer(1,0); break;
        case 'W': messages = movePlayer(0,-1); break;
        default: break;
    }
}

//TODO cleanup
vector<string> GameController::movePlayer(int difX, int difY) {
    int newX = player->x + difX;
    int newY = player->y + difY;
    bool inBounds = newX >= 0 && newX < 10 && newY >= 0 && newY < 8;
    map->moveToRoom(newX, newY, player);
    return map->getRoom(newX, newY)->interactAll(player);
}

void GameController::useItem(char direction, RoomEntity* item) {
    int x = player->x;
    int y = player->y;
    //TODO verify directions
    switch(direction){
        case 'N': map->getRoom(x-1, y)->interactAll(item); break;
        case 'E': map->getRoom(x, y+1)->interactAll(item); break;
        case 'S': map->getRoom(x+1, y)->interactAll(item); break;
        case 'W': map->getRoom(x, y-1)->interactAll(item); break;
    }
}

// //TODO remove this entirely??
// bool Map::movePlayer(int difX, int difY) {

//     if (inBounds && rooms[newX][newY].isTraversable()) {
        
//         TODO move to controller
//         for (RoomEntity *entity : *rooms[newX][newY].getEntities()) {
//             std::string result = entity->interact(Player::getInstance());
//             if (!result.empty()) {
//                 std::cout << result << std::endl;
//             }
//             if (entity == Mask::getInstance() || entity == Homework::getInstance()) {
//                 removeFromRoom(Player::getInstance()->x, Player::getInstance()->y, entity);
//             }
//         }
//         return true;
//     }
//     return false;
// }

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
