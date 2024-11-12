//
// Created by milleraa on 10/29/2024.
//

#ifndef ROOM_H
#define ROOM_H

#include "RoomEntity.h"

class RoomEntity;

class Room {
public:
    Room();
    vector<string> interactAll(RoomEntity *entity);
    vector<string> getAllMessages();
    void setTraversable(bool traversable);
    void removeEntity(RoomEntity *entity);
    void addEntity(RoomEntity *entity);
    bool contains(RoomEntity *entity);
    bool isTraversable() const;
    bool canTeleport() const;
    std::string getString();
    std::vector<RoomEntity *> *getEntities();
private:
    bool traversable;
    std::vector<RoomEntity*> entities;
};

#endif // ROOM_H
