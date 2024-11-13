//
// Created by milleraa on 10/29/2024.
//
#include <stdexcept>
#include "RoomEntity.h"
#include <map>
#include "Player.h"

using namespace std;

Blank::Blank(Room *room){
    icon = "\33[0m   \33[0m";
    nonTraversableIcon = "\33[0mXXX\33[0m";
    message = "";
    this->room = room;
}

string Blank::getIcon() {
    return room->isTraversable() ? icon : nonTraversableIcon;
}

Mask::Mask() {
    icon = "\33[96m > \33[0m";
    message = "There's a box of disposable masks nearby.";
}

Homework::Homework() {
    icon = "\33[38:5:178m H \33[0m";
    message = "You sense your homework nearby.";
}

ProfessorOffice::ProfessorOffice() {
    icon = "\33[38:5:166m # \33[0m";
    message = "You feel an ominous presence.";
}

Portal::Portal() {
    icon = "\33[38:5:13m ~ \33[0m";
    message = "This doorway leads somewhere weird.";
}

void Portal::setMap(Map *map) {
    this->map = map;
}

Camera::Camera() {
    icon = "\33[38:5:9m<O>\33[0m";
    message = "There's a camera in the corner.";
}

CameraZone::CameraZone() {
    icon = "\33[38:5:124m\33[5m ! \33[0m";
    message = "The camera can almost see you"; // Other msg was misleading, this was kinda sucks
    enter_message = "You equipped a mask and are anonymous on the cameras.";
    sneaking_message = "You are sneaking through the cameras.";
    caught_message = "You got caught by the cameras!";
    left_message = "You've left the sight of the cameras. They'll remember you next time...";
}

string Blank::interact(RoomEntity *entity) {
    if(entity == Mask::getInstance()) {
        room->removeEntity(entity);
    }
    if(entity == Homework::getInstance()) {
        room->removeEntity(entity);
        Player::getInstance()->homework--;
    }
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

//TODO ensure this is correct
string ProfessorOffice::interact(RoomEntity *entity) {
    // Just for testing
    if(entity == Player::getInstance()) {
        // if (Player::getInstance()->homework > 0) {
        //     Player::getInstance()->homework--;
        //     return "You slipped a page of homework under the door!";
        // } else {
        Player::getInstance()->alive = false;
        return "You got caught!";
        // }
    }
    if (entity == Homework::getInstance()) {
        Player::getInstance()->won = true;
        return "You slipped a page of homework under the door!";
    }
    return "";
}

//TODO avoid magic numbers
string Portal::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {
        int x;
        int y;
        Room * room = map->getRandomRoom(true, true, x, y);
        while(!room->canTeleport()) {
            room = map->getRandomRoom(true, true, x, y);
        }
        map->moveToRoom(x, y, Player::getInstance());
    }

    return "You have encountered weird architecture.";
}

string Camera::interact(RoomEntity *entity) {
    return "";
}

string CameraZone::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {
        Player *player = Player::getInstance();

        if(player->masks > 0 && !player->watched) {
            player->watched = true;
            player->masks--;
            return enter_message;
        }

        if (player->watched) {
            return sneaking_message;
        }

        if (player->masks == 0) {
            player->alive = false;
            return caught_message;
        }
    }

    return "";
}

string CameraZone::getMessage() const {
    return Player::getInstance()->watched ? "" : this->message;
}

string CameraZone::getLeftMessage() const {
    return this->left_message;
}