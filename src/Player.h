//
// Created by milleraa on 10/29/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "RoomEntity.h"

using namespace std;

class Player : public Singleton<Player> {
    friend class Singleton<Player>;
public:
    Player();
    int x;
    int y;
    int homework = 3;
    int masks = 0;
    bool alive = true;
    bool won = false;
    vector<std::string> getInventory();
    vector<std::string> search(Map* map) const;
    string interact(RoomEntity* entity) override;
    // int getHomework();
    // int getMasks();
    // void setHomework(int homework);
    // void setMask(int masks);
    string getIcon() override {return icon; };
private:
    string icon;
    string message;
};

#endif // PLAYER_H
