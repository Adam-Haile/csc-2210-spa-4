//
// Created by milleraa on 10/29/2024.
//

#include "RoomEntity.h"

Blank::Blank() {
    icon = " . ";
    message = "";
}

Mask::Mask() {
    icon = " < ";
    message = "";
}

std::string Mask::getColor() {
    return color;
}

Homework::Homework() {
    icon = " ?H ";
    message = "";
}

ProfessorOffice::ProfessorOffice() {
    icon = " # ";
    message = "";
}

Portal::Portal() {
    icon = " ~ ";
    message = "";
}

Camera::Camera() {
    icon = "<O>";
    message = "";
}

CameraZone::CameraZone(Camera cam) {
    icon = " ! ";
    message = "";
}

void Blank::interact(RoomEntity *entity) {
}

void Mask::interact(RoomEntity *entity) {
}

void Homework::interact(RoomEntity *entity) {
}

void ProfessorOffice::interact(RoomEntity *entity) {
}

void Portal::interact(RoomEntity *entity) {
}

void Camera::interact(RoomEntity *entity) {
}

void CameraZone::interact(RoomEntity *entity) {
}
