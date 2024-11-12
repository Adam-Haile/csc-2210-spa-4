//
// Created by milleraa on 10/29/2024.
//

#include "Player.h"

using namespace std;

Player::Player() {
    icon = "\33[92m P \33[0m";
    message = "";
}

//TODO
vector<string> Player::getInventory() {
    return {
        "Homework: \33[3m\33[38:5:28m" + to_string(homework) + "\33[0m",
        "Masks: \33[3m\33[38:5:28m" + to_string(masks) + "\33[0m"
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
            if (!playerTile && map->validRoom(X,Y)) {
                vector<string> messages = map->getRoom(X, Y)->getAllMessages();
                //add messages to result
                result.insert(result.end(), messages.begin(), messages.end());
            }
        }
    }
    return result;
}

string Player::interact(RoomEntity* entity) { return ""; }