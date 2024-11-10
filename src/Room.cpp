//
// Created by milleraa on 10/29/2024.
//

#include "Room.h"
#include <algorithm>

Room::Room() {
  entities = std::vector<RoomEntity*>();
  addEntity(new Blank(this));
}

void Room::interactAll(RoomEntity *entity) {
  for (RoomEntity *i : entities) {
    i->interact(entity);
  }
}

vector<string> Room::getAllMessages() {
  vector<string> messages;
  for (RoomEntity *i : entities) {
    if(i->getMessage() != ""){
      messages.push_back(i->getMessage());
    }
  }
  return messages;
}

void Room::removeEntity(RoomEntity *entity) {
  // Took me forever to figure out
  // It'll iterate through the vector until it finds entity, or it reaches the end
  const auto iterator = std::find(entities.begin(), entities.end(), entity);
  if (iterator != entities.end()) { // If it found it, we erase it
    entities.erase(iterator);
  }
}

void Room::addEntity(RoomEntity *entity) {
  //add entity to front
  entities.insert(entities.begin(), entity);
}

void Room::setTraversable(const bool traversable) {
  this->traversable = traversable;
}

bool Room::isTraversable() const {
  return traversable;
}

bool Room::canTeleport() const {
  return traversable && entities.size() == 1;
}

std::string Room::getString() {
  RoomEntity *entity = entities.front();
  return entity->getIcon();
  // int level = 0;
  // std::string toReturn = "   ";
  // if (!traversable) {
  //   level = 2;
  //   toReturn = "XXX";
  // }
  // for (RoomEntity * i : entities) {
  //   switch (i -> getIcon().at(1)) {
  //     case '!':
  //       if (level < 1) {
  //         level = 1;
  //         toReturn = " ! ";
  //       }
  //     break;
  //     case 'O':
  //       if (level < 3) {
  //         level = 3;
  //         toReturn = "<O>";
  //       }
  //       break;
  //     case '>':
  //       if (level < 4) {
  //         level = 4;
  //         toReturn = " > ";
  //       }
  //       break;
  //     case 'H':
  //       if (level < 5) {
  //         level = 5;
  //         toReturn = " H ";
  //       }
  //       break;
  //     case '#':
  //       if (level < 6) {
  //         level = 6;
  //         toReturn = " # ";
  //       }
  //       break;
  //     case '~':
  //       if (level < 7) {
  //         level = 7;
  //         toReturn = " ~ ";
  //       }
  //       break;
  //     case 'P':
  //       if (level < 8) {
  //         level = 8;
  //         toReturn = " P ";
  //       }
  //       break;
  //   }
  // }
  // return toReturn;
  // idk if there's a better way
  //  !  Camera Zone - 1
  // XXX Not Traversable - 2
  // <0> Camera - 3
  //  >  Mask - 4
  //  H  Homework - 5
  //  #  Office - 6
  //  ~  Portal - 7
  //  P  Player - 8
}

std::vector<RoomEntity *> * Room::getEntities() {
  return &entities;
}
