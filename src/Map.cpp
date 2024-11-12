//
// Created by milleraa on 10/29/2024.
//

#include <random>
#include <iostream>

#include "Map.h"
#include "Player.h"

using namespace std;

const static int GLOBAL_SEED = 12345;

std::mt19937 gen(GLOBAL_SEED);

Map::Map() : Map(-1, -1) {}

Map::Map(int playerX, int playerY) {
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

    int x, y;
    if (playerX < 0 && playerY < 0) {
        getRandomRoom(true, true, x, y)->addEntity(Player::getInstance());
        Player::getInstance()->x = x;
        Player::getInstance()->y = y;
    } else if (validRoom(playerX, playerY)) {
        getRoom(playerX, playerY)->addEntity(Player::getInstance());
        Player::getInstance()->x = playerX;
        Player::getInstance()->y = playerY;
    } else {
        cerr << "Player spawn is an invalid room";
    }

    spawnRandomCamera();
    spawnRandomCamera();

    Portal::getInstance()->setMap(this);
    getRandomRoom(true)->addEntity(Mask::getInstance());
    getRandomRoom(true)->addEntity(Mask::getInstance());
    getRandomRoom(true)->addEntity(Homework::getInstance());
    getRandomRoom(true)->addEntity(Homework::getInstance());
    getRandomRoom(true)->addEntity(Homework::getInstance());
    getRandomRoom(true)->addEntity(ProfessorOffice::getInstance());
    getRandomRoom(false, true, x, y)->addEntity(Portal::getInstance());
    getRoom(x, y)->setTraversable(true);
}

bool Map::cameraContainsEntity(RoomEntity * entity, int x, int y) {
    bool contains = false;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            contains = contains ||
                validRoom(x + dx, y + dy) && getRoom(x + dx, y + dy)->contains(entity);
        }
    }
    return contains;
}


void Map::spawnRandomCamera() {
    int x, y;
    this->getRandomRoom(false, true, x, y);
    while(this->cameraContainsEntity(Player::getInstance(), x, y) ||
            this->cameraContainsEntity(ProfessorOffice::getInstance(), x, y) ||
            this->cameraContainsEntity(Mask::getInstance(), x, y)) {
        this->getRandomRoom(false, true, x, y);
    }

    addCamera(x, y);
}

Room* Map::getRandomRoom(bool isTraverseable) {
    int x, y;
    return getRandomRoom(isTraverseable, false, x, y);
}


Room* Map::getRandomRoom(bool isTraverseable, bool isEmpty) {
    int x, y;
    return getRandomRoom(isTraverseable, isEmpty, x, y);
}

Room* Map::getRandomRoom(bool isTraverseable, bool isEmpty, int &x, int &y) {
    // Use the global random number generator
    std::uniform_int_distribution<int> distX(0, 7);
    std::uniform_int_distribution<int> distY(0, 9);

    while (true) {
        x = distX(gen);
        y = distY(gen);

        if (validRoom(x, y) && getRoom(x, y)->isEmpty() && getRoom(x, y)->isTraversable() == isTraverseable) {
            return getRoom(x, y);
        }
    }
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