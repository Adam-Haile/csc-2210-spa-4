//
// Created by milleraa on 10/29/2024.
//
#include <stdexcept>

#include "RoomEntity.h"

#include <Player.h>

using namespace std;

Blank::Blank() {
    icon = " . ";
    message = "";
}

Mask::Mask() {
    icon = " < ";
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

Camera::Camera() {
    icon = "<O>";
    message = "";
}

CameraZone::CameraZone(Camera cam) {
    icon = " ! ";
    message = "There's a camera in the corner.";
}

string Blank::interact(RoomEntity *entity) {
    return "";
}

string Mask::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {
        int masks = Player::getInstance()->getMasks();
        Player::getInstance()->setMask(masks + 1);
        return "You picked up a mask.";
    }

    return "";
}

string Homework::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {

    }

    return "";
}

string ProfessorOffice::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {

    } else if (entity == Homework::getInstance()) {

    }

    return "";
}

string Portal::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {

    }

    return "";
}

string Camera::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {

    }

    return "";
}

string CameraZone::interact(RoomEntity *entity) {
    if(entity == Player::getInstance()) {

    }

    return "";
}
