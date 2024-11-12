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
    Map(int playerX, int playerY);
    void spawnRandomCamera();
    bool cameraContainsEntity(RoomEntity * entity, int x, int y);
    Room* getRandomRoom(bool isTraverseable);
    Room* getRandomRoom(bool isTraverseable, bool isEmpty);
    Room* getRandomRoom(bool isTraverseable, bool isEmpty, int& x, int& y);
    void setToRoom(int x, int y, RoomEntity* entity);
    void moveToRoom(int x, int y, RoomEntity* entity);
    void removeFromRoom(int x, int y, RoomEntity* entity);
    // bool movePlayer(int difX, int difY);
    Room* getRoom(int x, int y);
    bool validRoom(int x, int y);
    vector<char> getValidDirections(Player *player);

private:
    std::vector<std::vector<Room>> rooms;
    void addCamera(int x, int y);
};

#endif // MAP_H


