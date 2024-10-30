//
// Created by milleraa on 10/29/2024.
//

#ifndef ROOMENTITY_H
#define ROOMENTITY_H

#include <string>
#include <vector>

class Blank;
class Mask;
class Homework;
class ProfessorOffice;
class Portal;
class Camera;
class CameraZone;

class RoomEntity {
public:
    virtual std::string getIcon() = 0;
    virtual void interact(RoomEntity* entity) = 0;
    virtual ~RoomEntity() = default;
    virtual std::string getMessage() const { return message; }

protected:
    std::string message;
    RoomEntity() = default; // Protected constructor
};

template <typename T>
class Singleton : public RoomEntity {
public:
    static T* getInstance() {
        static T instance;
        return instance;
    }
    Singleton(const Singleton&) = delete; //delete copy constructor
    Singleton& operator=(const Singleton&) = delete; //delete assignment operator
protected:
    Singleton() = default;
    ~Singleton() = default;
};

// Blank Singleton
class Blank : public Singleton<Blank> {
    friend class Singleton<Blank>; // Allows access to protected constructor
public:
    Blank();
    std::string getIcon() override {return icon; };
    void interact(RoomEntity* entity) override;
private:
    std::string icon;
    std::string message;
};

// Mask Singleton
class Mask : public Singleton<Mask> {
    friend class Singleton<Mask>;
public:
    Mask();
    std::string getColor();
    std::string getIcon() override {return icon; };
    void interact(RoomEntity* entity) override;
private:
    std::string icon;
    std::string message;
    std::string color;
};

// Homework Singleton
class Homework : public Singleton<Homework> {
    friend class Singleton<Homework>;
public:
    Homework();
    std::string getIcon() override {return icon; };
    void interact(RoomEntity* entity) override;
private:
    std::string icon;
    std::string message;
};

// ProcessorOffice Singleton
class ProfessorOffice : public Singleton<ProfessorOffice> {
    friend class Singleton<ProfessorOffice>;
public:
    ProfessorOffice();
    std::string getIcon() override {return icon; };
    void interact(RoomEntity* entity) override;
private:
    std::string icon;
    std::string message;
};

// Portal Singleton
class Portal : public Singleton<Portal> {
    friend class Singleton<Portal>;
public:
    Portal();
    std::string getIcon() override {return icon; };
    void interact(RoomEntity* entity) override;
private:
    std::string icon;
    std::string message;
};

// Camera Singleton
class Camera : public Singleton<Camera> {
    friend class Singleton<Camera>;
public:
    Camera();
    std::string getIcon() override {return icon; };
    void interact(RoomEntity* entity) override;
private:
    std::string icon;
    std::string message;
    std::vector<CameraZone*> zones;
};

// Camera Singleton
class CameraZone : public Singleton<CameraZone> {
    friend class Singleton<CameraZone>;
public:
    explicit CameraZone(Camera cam);
    std::string getIcon() override {return icon; };
    void interact(RoomEntity* entity) override;
private:
    std::string icon;
    std::string message;
    Camera cam;
};

#endif // ROOMENTITY_H