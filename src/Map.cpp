//
// Created by milleraa on 10/29/2024.
//

#include <iostream>
#include "Map.h"

using namespace std;

Map::Map() {
    vector<vector<std::string>> test(10, vector<std::string>(8,""));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 8; j++) {
            test[i][j] = to_string(i) + "," + to_string(j);
        }
    }
    for (int i = 0; i < test.size(); i++) {
        for (int j = 0; j < test[i].size(); j++) {
            cout << test[i][j] << " | ";
        }
        cout << endl;
    }
}

void Map::setToRoom(int x, int y, RoomEntity *entity) {
}

void Map::moveToRoom(int x, int y, RoomEntity *entity) {
}

// void Map::removeFromRoom(int x, int y, RoomEntity *entity) {
// }
