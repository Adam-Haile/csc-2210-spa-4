//
// Created by milleraa on 10/29/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "RoomEntity.h"

class Player : public Singleton<Player> {
    friend class Singleton<Player>;
public:
    Player();
    int x;
    int y;
    bool alive;
    std::vector<std::string> getInventory();
    std::vector<std::string> search();
    void interact(RoomEntity* entity) override;
    std::string getIcon() override {return icon; };
private:
    std::string icon;
    std::string message;
};

#endif // PLAYER_H
