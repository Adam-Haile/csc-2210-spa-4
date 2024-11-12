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
Map::Map() {
    rooms.resize(10); // Create 10 rows
    for (int i = 0; i < 10; ++i) {
        rooms[i].resize(8); // Create 8 columns for each row
    }

    vector<string> wall = {"01","02","05","21","22","23","24","26",
                           "31","34","36","41","46","51","56","61","63","66",
                           "71","73","74","75","76","92","95","96"};
    for (string s : wall) {
        int i = s[0] - '0';
        int j = s[1] - '0';
        rooms[i][j].setTraversable(false);
    }

    Portal::getInstance()->setMap(this);
    setToRoom(7, 5, Mask::getInstance());
    setToRoom(2, 3, Mask::getInstance());
    setToRoom(0, 3, Homework::getInstance());
    setToRoom(4, 4, Homework::getInstance());
    setToRoom(0, 6, Homework::getInstance());
    setToRoom(1, 1, ProfessorOffice::getInstance());
    setToRoom(6, 8, Player::getInstance());
    Player::getInstance()->x = 6;
    Player::getInstance()->y = 8;

    addCamera(5, 0);
    addCamera(3, 7);
    setToRoom(7, 0, Portal::getInstance());
}


void Map::addCamera(int x, int y) {
    setToRoom(x,y,Camera::getInstance());
    for (int dx = -1; dx <= 1; dx ++) {
        for (int dy = -1; dy <= 1; dy ++) {
            if (dx == 0 && dy == 0) continue;
            Room *room = validRoom(x + dx, y + dy) ? getRoom(x + dx, y + dy) : nullptr;
            if (room && room->isTraversable()) {
                room->addEntity(CameraZone::getInstance());
            }
        }
    }
}

Room* Map::getRoom(int x, int y) {
    return &rooms[y][x];
}

void Map::setToRoom(int x, int y, RoomEntity *entity) {
    if (validRoom(x, y)) {
        getRoom(x,y)->addEntity(entity);
    }
}

void Map::moveToRoom(int x, int y, RoomEntity *entity) {
    if (validRoom(x, y)) {
        if (entity == Player::getInstance()) {
            if (getRoom(x,y)->isTraversable()) {
                removeFromRoom(Player::getInstance()->x, Player::getInstance()->y, entity);
                Player::getInstance()->x = x;
                Player::getInstance()->y = y;
                getRoom(x,y)->addEntity(entity);
            }
        }
    }
}

void Map::removeFromRoom(int x, int y, RoomEntity *entity) {
    if (validRoom(x, y)) {
        getRoom(x,y)->removeEntity(entity);
    }
}

bool Map::validRoom(int x, int y) {
    return y >= 0 && y < 10 && x >= 0 && x < 8;
}

vector<char> Map::getValidDirections(Player *player) {
    vector<char> validDirections;
    int x = player->x;
    int y = player->y;
    if (validRoom(x,y-1) && getRoom(x, y-1)->isTraversable()) validDirections.push_back('N');
    if (validRoom(x,y+1) && getRoom(x, y+1)->isTraversable()) validDirections.push_back('S');
    if (validRoom(x+1,y) && getRoom(x+1, y)->isTraversable()) validDirections.push_back('E');
    if (validRoom(x-1,y) && getRoom(x-1, y)->isTraversable()) validDirections.push_back('W');
    return validDirections;
}