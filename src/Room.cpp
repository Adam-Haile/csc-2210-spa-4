//
// Created by milleraa on 10/29/2024.
//

#include "Room.h"
#include <algorithm>

Room::Room() : traversable(true) {
  entities = std::vector<RoomEntity*>();
  addEntity(new Blank(this));
}

vector<string> Room::interactAll(RoomEntity *entity) {
  vector<string> interactions;
  for (RoomEntity *i : entities) {
    string interaction = i->interact(entity);
    if (!interaction.empty()) {
      interactions.push_back(interaction);
    }
  }
  return interactions;
}

vector<string> Room::getAllMessages() {
  vector<string> messages;
  for (RoomEntity *i : entities) {
    if(!i->getMessage().empty()){
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
bool Room::contains(RoomEntity *entity) {
  const auto iterator = std::find(entities.begin(), entities.end(), entity);
  return iterator != entities.end();
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
}

std::vector<RoomEntity *> *Room::getEntities() {
  return &entities;
}
