//
// Created by milleraa on 10/29/2024.
//

#ifndef ROOM_H
#define ROOM_H

#include "RoomEntity.h"

class Room {
public:
    bool isTraversable;
    void removeEntity(RoomEntity * entity);
    void addEntity(RoomEntity* entity);
private:
    std::vector<RoomEntity*> entities;
};

#endif // ROOM_H
