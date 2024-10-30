//
// Created by milleraa on 10/29/2024.
//

#ifndef MAP_H
#define MAP_H

#include "Room.h"
#include <vector>

class Map {
public:
    Map();
    void setToRoom(int x, int y, RoomEntity* entity);
    void moveToRoom(int x, int y, RoomEntity* entity);
private:
    std::vector<std::vector<Room>> rooms;
};

#endif // MAP_H

