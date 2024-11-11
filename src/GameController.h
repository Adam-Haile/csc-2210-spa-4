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
    char startTurn();
    void performAction(char action);
    void useItem(char direction, RoomEntity* item);

    void endRound(int gameState);
    void endGame(int gameState);
    void resetGame();
    std::vector<std::string> movePlayer(int difX, int difY);

private:
    Map* map;
    Player* player;
    View* view;
    std::string help_message = "helpity help";
    enum state {QUIT, RUNNING, WON, LOST};
    state getGameState(char action);
    std::vector<std::string> messages;
};

#endif // GAMECONTROLLER_H

