//
// Created by milleraa on 10/29/2024.
//

#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Room.h"

class Room;
class RoomEntity;

class Map {
public:
    Map();
    void setToRoom(int x, int y, RoomEntity* entity);
    void moveToRoom(int x, int y, RoomEntity* entity);
    void removeFromRoom(int x, int y, RoomEntity* entity);
    Room* getRoom(int x, int y);
private:
    std::vector<std::vector<Room>> rooms;
};

#endif // MAP_H


