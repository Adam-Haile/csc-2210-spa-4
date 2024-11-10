//
// Created by milleraa on 10/29/2024.
//

#include "Player.h"

using namespace std;

Player::Player() {
    icon = " P ";
    message = "";
}

vector<string> Player::getInventory() {
    return {};
}

vector<string> Player::search(Map* map) const {
    vector<std::string> result = {};
    for (int dx = -1; dx <= 1; dx ++) {
        int otherX = x + dx;
        for (int dy = -1; dy <= 1; dy ++) {
            if (dx == 0 && dy == 0) continue;
            int otherY = y + dy;
            if (otherX >= 0 && otherX < 10 && otherY >= 0 && otherY < 8) {
                std::vector<RoomEntity *> * entities = map->getRoom(otherX, otherY)->getEntities();
                if (!entities->empty()) {
                    for (RoomEntity *entity : *entities) {
                        std::string message = entity->getMessage();
                        if (!message.empty()) {
                            result.push_back(message);
                        }
                    }
                }
            }
        }
    }
    return result;
}

string Player::interact(RoomEntity* entity) { return ""; }