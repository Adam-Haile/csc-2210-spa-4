//
// Created by milleraa on 10/29/2024.
//

#include "Player.h"

using namespace std;

Player::Player() {
    icon = " P ";
    message = "";
}

//TODO
vector<string> Player::getInventory() {
    return {
        "Homework: " + to_string(homework),
        "Masks: " + to_string(masks)
    };
}

vector<string> Player::search(Map* map) {
    vector<string> result = {};
    int playerX = x;
    int playerY = y;
    //for each adjacent room, get their messages
    for (int dx = -1; dx <= 1; dx ++) {
        int X = playerX + dx;
        for (int dy = -1; dy <= 1; dy ++) {
            int Y = playerY + dy;
            bool playerTile = dx == 0 && dy == 0;
            bool validTile = X >= 0 && X < 10 && Y >= 0 && Y < 8;
            if (!playerTile && validTile) {
                vector<string> messages = map->getRoom(X, Y)->getAllMessages();
                //add messages to result
                result.insert(result.end(), messages.begin(), messages.end());
            }
        }
    }
    return result;
}

string Player::interact(RoomEntity* entity) { return ""; }