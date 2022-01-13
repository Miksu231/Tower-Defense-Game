#include "enemy.hpp"
#include <iostream>


Enemy::Enemy(int routeNumber, std::string type, int speed, int radius, int health, int value, int freeze):
type_(type), speed_(speed), radius_(radius), health_(health), routeNumber_(routeNumber), value_(value), freezed_(freeze) {}

Enemy::~Enemy() {}

void Enemy::ResetRouteNumber() {
    routeNumber_ = 0;
}

int Enemy::Move() {
    if (freezed_ > 0){
        freezed_--;
        routeNumber_ += 1;
    }else {
        routeNumber_ += speed_;
    }
    return routeNumber_;
}
int Enemy::GetHealth() const {
    return health_;
}
int Enemy::GetValue() const {
    return value_;
}
int Enemy::GetRadius() const {
    return radius_;
}
int Enemy::GetRouteIndex() const {
    return routeNumber_;
}
std::string Enemy::GetType() const {
    return type_;
}

int Enemy::GetSpeed() const {
    return speed_;    
}

void Enemy::ReduceHealth(int damage) {
    health_ -= damage;
}

bool Enemy::Freezed() const {
    return freezed_ > 0;
}

void Enemy::Freeze(int level) {
    freezed_ = 30*level;
}

std::ostream &operator<<(std::ostream &os, const Enemy& enemy) {
    os << "Enemy:\n" << std::endl;
    os << "Enemy Type:" << enemy.GetType();
    os << "Speed:" << enemy.speed_ << std::endl;
    os << "Radius:" << enemy.GetRadius() << std::endl;
    os << "Health" << enemy.GetHealth() << std::endl;
    os << "Route index:" << enemy.GetRouteIndex() << std::endl;
    return os;
}

Infantry::Infantry(int routeNumber, std::string type,  int speed, int radius, int health,  int value): 
Enemy(routeNumber, type, speed, radius, health, value) {}

Infantry::~Infantry() {}

Tank::Tank(int routeNumber, std::string type,  int speed, int radius, int health, int value): 
Enemy(routeNumber, type, speed, radius, health, value) {}

Tank::~Tank() {}

Scout::Scout(int routeNumber, std::string type,  int speed, int radius, int health, int value): 
Enemy(routeNumber, type, speed, radius, health, value) {}

Scout::~Scout() {}

Container::Container(int routeNumber, std::string type,  int speed, int radius, int health, int value): 
Enemy(routeNumber, type, speed, radius, health, value) {}

Container::~Container() {}
