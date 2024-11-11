//
// Created by milleraa on 10/29/2024.
//

#ifndef MAP_H
#define MAP_H

#include <vector>

// #include "Player.h"
#include "Room.h"

class Room;
class RoomEntity;
class Player;

class Map {
public:
    Map();
    void setToRoom(int x, int y, RoomEntity* entity);
    void moveToRoom(int x, int y, RoomEntity* entity);
    void removeFromRoom(int x, int y, RoomEntity* entity);
    // bool movePlayer(int difX, int difY);
    Room* getRoom(int x, int y);
    bool validRoom(int x, int y);
    vector<char> getValidDirections(Player *player) const;

private:
    std::vector<std::vector<Room>> rooms;
    void addCamera(int x, int y);
};

#endif // MAP_H


