//
// Created by milleraa on 10/29/2024.
//

#ifndef ROOMENTITY_H
#define ROOMENTITY_H

using namespace std;

#include <string>
#include <vector>

#include "Map.h"

class Map;
class Room;
class Blank;
class Mask;
class Homework;
class ProfessorOffice;
class Portal;
class Camera;
class CameraZone;

class RoomEntity {
public:
    virtual string getIcon() = 0;
    virtual string interact(RoomEntity* entity) = 0;
    virtual ~RoomEntity() = default;
    virtual string getMessage() const {
        return message;
    }

protected:
    string message;
    RoomEntity() = default; // Protected constructor
};

template <typename T>
class Singleton : public RoomEntity {
public:
    static T* getInstance() {
        static T instance;
        return &instance;
    }
    Singleton(const Singleton&) = delete; //delete copy constructor
    Singleton& operator=(const Singleton&) = delete; //delete assignment operator
protected:
    Singleton() = default;
    ~Singleton() = default;
};

// Blank entity
class Blank : public RoomEntity {
public:
    Blank(Room *room);
    string getIcon() override;
    string interact(RoomEntity* entity) override;
private:
    string icon;
    string nonTraversableIcon;
    string message;
    Room *room;
};

// Mask Singleton
class Mask : public Singleton<Mask> {
    friend class Singleton<Mask>;
public:
    Mask();
    string getIcon() override {return icon; };
    string interact(RoomEntity* entity) override;
private:
    string icon;
    // string message;
};

// Homework Singleton
class Homework : public Singleton<Homework> {
    friend class Singleton<Homework>;
public:
    Homework();
    string getIcon() override {return icon; };
    string interact(RoomEntity* entity) override;
private:
    string icon;
    // string message;
};

// ProcessorOffice Singleton
class ProfessorOffice : public Singleton<ProfessorOffice> {
    friend class Singleton<ProfessorOffice>;
public:
    ProfessorOffice();
    string getIcon() override {return icon; };
    string interact(RoomEntity* entity) override;
private:
    string icon;
    // string message;
};

// Portal Singleton
class Portal : public Singleton<Portal> {
    friend class Singleton<Portal>;
public:
    Portal();
    string getIcon() override {return icon; };
    string interact(RoomEntity* entity) override;
    void setMap(Map* map);
private:
    string icon;
    // string message;
    Map* map;
};

// Camera Singleton
class Camera : public Singleton<Camera> {
    friend class Singleton<Camera>;
public:
    Camera();
    string getIcon() override {return icon; };
    string interact(RoomEntity* entity) override;
private:
    string icon;
    // string message;
};

// Camera Singleton
class CameraZone : public Singleton<CameraZone> {
    friend class Singleton<CameraZone>;
public:
    explicit CameraZone();
    string getIcon() override {return icon; };
    string interact(RoomEntity* entity) override;
    string getMessage() const override;
    string getLeftMessage() const;
private:
    string icon;
    // string message;
    string enter_message;
    string sneaking_message;
    string caught_message;
    string left_message;
    Camera cam;
};

#endif // ROOMENTITY_H