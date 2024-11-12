//
// Created by milleraa on 10/29/2024.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <string>

#include "Player.h"
#include "Map.h"
#include "View.h"

class GameController {
public:
    explicit GameController(View* view); //needs the map keys
    ~GameController();
    void startGame();

private:
    Map* map;
    Player* player;
    View* view;
    std::string help_message = "helpity help";
    std::vector<std::string> interactions;
    enum state {QUIT, RUNNING, WON, LOST};

    char startTurn();
    vector<string> performAction(char action);
    void useItem(char direction, RoomEntity* item);
    std::vector<std::string> movePlayer(int difX, int difY);

    state getGameState(char action);
    void endRound(state gameState);
    void resetGame();
    void endGame(state gameState);
};

#endif // GAMECONTROLLER_H

