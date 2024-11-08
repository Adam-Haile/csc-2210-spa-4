//
// Created by milleraa on 10/29/2024.
//

#include <iostream>
#include "Map.h"

using namespace std;

Map::Map() : rooms(10, vector<Room>(8)) {
    // Terrible way to keep track, but will work for now
    vector<string> wall = {"01","02","05","21","22","23","24","26",
        "31","34","36","41","46","51","56","61","63","66",
        "71","73","74","75","76","92","95","96"};
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 8; j++) {
            string tile = to_string(i) + to_string(j);
            if (wall.front() == tile) {
                rooms[i][j].setTraversable(false);
                wall.erase(wall.begin());
            }
            cout << tile << " ";
        }
        cout << endl;
    }
    // Add cameras (currently NOT RANDOM)
    rooms[0][5].addEntity(Camera::getInstance());
}

Room* Map::getRoom(int x, int y) {
    return &rooms[x][y];
}

void Map::setToRoom(int x, int y, RoomEntity *entity) {
}

void Map::moveToRoom(int x, int y, RoomEntity *entity) {
}

void Map::removeFromRoom(int x, int y, RoomEntity *entity) {
}
