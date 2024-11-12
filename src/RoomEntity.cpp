//
// Created by milleraa on 10/29/2024.
//
#include <stdexcept>
#include "RoomEntity.h"
#include <map>
#include "Player.h"

using namespace std;

Blank::Blank(Room *room){
    icon = "   ";
    nonTraversableIcon = "XXX";
    message = "";
    this->room = room;
}

string Blank::getIcon() {
    return room->isTraversable() ? icon : nonTraversableIcon;
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
    message = "There's a camera in the corner.";
}

CameraZone::CameraZone() {
    icon = " ! ";
    message = "The camera can almost see you"; // Other msg was misleading, this was kinda sucks
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
        // Player::getInstance()->homework--; //TODO either add this to Blank or a Player Action
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
        Room * room = map->getRandomRoom(true, x, y);
        while(!room->canTeleport()) {
            room = map->getRandomRoom(true, x, y);
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

        if(player->masks > 0 && this->watching == false) {
            this->watching = true;
            player->masks--;
            return "You equipped a mask and are anonymous on the cameras.";
        }

        if (this->watching == true) {
            return "You are sneaking through the cameras.";
        }

        if (player->masks == 0) {
            player->alive = false;
            return "You got caught by the cameras!";
        }

        //TODO
        // if (something) {
        //     this->watching = false;
        //     return "You've left the sight of the cameras. They'll remember you next time...";
        // }
    }

    return "";
}

string CameraZone::getMessage() const {
    return this->watching ? "" : this->message;
}
