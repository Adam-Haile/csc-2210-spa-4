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
    int getGameState(char action);
    void endRound(int gameState);
    void endGame(int gameState);
    void resetGame();
    void movePlayer(int difX, int difY);

private:
    Map* map;
    // Player* player;
    View* view;
    std::string help_message = "helpity help";
};

#endif // GAMECONTROLLER_H

