//
// Created by milleraa on 10/29/2024.
//
#include <stdexcept>
#include <random>

#include "RoomEntity.h"

#include <map>

#include "Player.h"

using namespace std;

int getRandomInt(int min, int max) {
    // Initialize random number generator with a seed from the random_device
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

Blank::Blank() {
    icon = "   ";
    message = "";
}

Mask::Mask() {
    icon = " > ";
    message = "There's a box of disposable masks nearby.";
}

Homework::Homework() {
    icon = " H ";
    message = "You sense your homework nearby.";
}

ProfessorOffice::ProfessorOffice() {
    icon = " # ";
    message = "You feel an ominous presence.";
}

Portal::Portal() {
    icon = " ~ ";
    message = "This doorway leads somewhere weird.";
}
void Portal::setMap(Map *map) {
    this->map = map;
}
Camera::Camera() {
    icon = "<O>";
    message = "";
}

CameraZone::CameraZone() {
    icon = " ! ";
    message = "There's a camera in the corner.";
}

string Blank::interact(RoomEntity *entity) {
    return "";
}

string Mask::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {
        Player::getInstance()->masks++;
        return "You picked up a mask.";
    }

    return "";
}

string Homework::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {
        Player::getInstance()->homework++;
        return "You picked up a page of homework.";
    }

    return "";
}

string ProfessorOffice::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {
        Player::getInstance()->alive = false;
        return "You got caught! GAME OVER!";
    }
    if (entity == Homework::getInstance()) {
        Player::getInstance()->homework--;
        return "You slipped a page of homework under the door!";
    }

    return "";
}

string Portal::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {
        int i = getRandomInt(0, 10);
        int j = getRandomInt(0, 8);
        while(!map->getRoom(i,j)->canTeleport()) {
            i = getRandomInt(0, 10);
            j = getRandomInt(0, 8);
        }
        map->moveToRoom(i, j, entity);
    }

    return "";
}


string Camera::interact(RoomEntity *entity) {
    return "";
}

string CameraZone::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {
        Player *player = Player::getInstance();

        if(player->masks > 0 && player->inCamera == false) {
            player->inCamera = true;
            player->masks--;
            return "You equiped a mask and are anonymous on the cameras.";
        }

        if (player->inCamera == true) {
            return "You are sneaking through the cameras.";
        }

        if (player->masks == 0) {
            player->alive = false;
            return "You got caught by the cameras! GAME OVER!";
        }
    }

    return "";
}
