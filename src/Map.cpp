//
// Created by milleraa on 10/29/2024.
//

#include <iostream>
#include "Map.h"

#include <set>

#include "Player.h"

using namespace std;

//TODO
//Make random generation
//Make portal be in a normally non-traversable room
Map::Map() : rooms(10, vector<Room>(8)) {
    vector<string> wall = {"01","02","05","21","22","23","24","26",
        "31","34","36","41","46","51","56","61","63","66",
        "71","73","74","75","76","92","95","96"};
    for (string s : wall) {
        int i = s[0] - '0';
        int j = s[1] - '0';
        rooms[i][j].setTraversable(false);
    }
    // NOTHING RANDOM RN
    Portal::getInstance()->setMap(this);
    setToRoom(5,7,Mask::getInstance());
    setToRoom(3,2,Mask::getInstance());
    setToRoom(3,0,Homework::getInstance());
    setToRoom(4,4,Homework::getInstance());
    setToRoom(6,0,Homework::getInstance());
    setToRoom(1,1,ProfessorOffice::getInstance());
    setToRoom(8,6,Player::getInstance());
    Player::getInstance()->x = 8;
    Player::getInstance()->y = 6;

    addCamera(0,5);
    addCamera(7,3);
    setToRoom(0,7,Portal::getInstance());
}

void Map::addCamera(int x, int y) {
    setToRoom(x,y,Camera::getInstance());
    for (int dx = -1; dx <= 1; dx ++) {
        for (int dy = -1; dy <= 1; dy ++) {
            if (dx == 0 && dy == 0) continue;
            setToRoom(x + dx, y + dy,CameraZone::getInstance());
        }
    }
}

Room* Map::getRoom(int x, int y) {
    return &rooms[x][y];
}

void Map::setToRoom(int x, int y, RoomEntity *entity) {
    if (x >= 0 && x < 10 && y >= 0 && y < 8) {
        rooms[x][y].addEntity(entity);
    }
}

//TODO fix this or rename, only works for player
void Map::moveToRoom(int x, int y, RoomEntity *entity) {
    bool validRoom = x >= 0 && x < 10 && y >= 0 && y < 8;
    if (validRoom) {
        if (entity == Player::getInstance()) {
            if (rooms[x][y].isTraversable()) {
                removeFromRoom(Player::getInstance()->x, Player::getInstance()->y, entity);
                Player::getInstance()->x = x;
                Player::getInstance()->y = y;
                rooms[x][y].addEntity(entity);
            }
        }
    }
}

void Map::removeFromRoom(int x, int y, RoomEntity *entity) {
    if (x >= 0 && x < 10 && y >= 0 && y < 8) {
        rooms[x][y].removeEntity(entity);
    }
}

vector<char> Map::getValidDirections(Player *player) const {
    vector<char> validDirections;
    int x = player->x;
    int y = player->y;
    if (rooms[x-1][y].isTraversable()) validDirections.push_back('N');
    if (rooms[x+1][y].isTraversable()) validDirections.push_back('S');
    if (rooms[x][y-1].isTraversable()) validDirections.push_back('E');
    if (rooms[x][y+1].isTraversable()) validDirections.push_back('W');
    return validDirections;
}