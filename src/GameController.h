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
    enum State {QUIT, RUNNING, WON, LOST};
    enum Mode {DEFAULT, DEBUG, MINIMAP};
    bool color;
    Mode mode;
    std::vector<std::string> interactions;
    Map* map;
    Player* player;
    View* view;
    std::string help_message = R"(Welcome to the MSOE Science Building! Your goal is to navigate this maze-like building, avoiding hazards, gather helpful items, and sneak your late homework into your professor’s office with them catching you! Be cautious – hazards like camera’s, the professor, and mysterious doors stand in your way.
Actions
-	Move around to the North (N), East (E), South (S), and West (W) so long as there isn’t a wall!
-	Pass (P) your homework under your professor’s door from any side of the room with any direction!
-	See your map (M) of where everything is located at!
-	Quit (q) and take an F on your assignment
Hazards
-	Cameras: Watch for surveillance, cameras have a range on them being identified in its range will mean game over. Remember, camera’s must be on walls!
-	Professor’s Office: Sneak your homework into their office! But watch out, if you enter it, you’ll be caught and get an F. Sneak it under their door to avoid getting caught.
-	Portals: This building is full of twists and doors that will take you to random areas around the building; proceed with caution.
Items
-	COVID Masks: Protect your identity and sneak past a camera! Keep in mind, they won’t fall for the same mask again, so you’ll have to find a new one once you get past.
-	Late Homework: Your papers got scattered all over the building! Collect them all and get them to the professor to win!
)";

    char startTurn();
    vector<string> performAction(char action);
    void useItem(char direction, RoomEntity* item);
    std::vector<std::string> movePlayer(int difX, int difY);

    State getGameState(char action);

    Mode setMode();

    void setSettings();

    void endRound(State gameState);
    void resetGame();
    void endGame(State gameState);
};

#endif // GAMECONTROLLER_H

