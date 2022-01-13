#ifndef ENEMY
#define ENEMY

#include <iostream>
#include "math.h"

/* The Enemy-class represents all the enemies moving across the game map. An enemy has a route number index, type, speed, radius, health, value and freeze duration. 
There are 4 types of enemies: Infantry, which is a basic enemy type; Tank which is slower, but has more health; 
Scout which has the same amount of health as infantry, but it is faster; And container, which splits into several infantry enemies upon its defeat */

class Enemy {
public:
    //Constructor for the Enemy-class
    Enemy(int routeNumber, std::string type, int speed, int radius, int health, int value, int freeze = 0);

    //Destructor for the Enemy-class
    ~Enemy();

    void ResetRouteNumber();

    //Moves the enemy forward one tick along the route
    //Returns route_number
    int Move();

    //Returns the health of the enemy as an int 
    int GetHealth() const;

    //Returns the value of the enemy (the amount of points gained from destroying it) as an int
    int GetValue() const;

    //Returns the radius of the enemy (assuming the enemy is circular) as an int
    int GetRadius() const;

    //Returns the index along the route that this enemy is on
    int GetRouteIndex() const;

    bool Freezed() const;

    void Freeze(int level);

    //Returns the type of the enemy as a string
    std::string GetType() const;

    //Returns the enemy's speed as an int
    int GetSpeed() const;

    //Reduces the enemy's health by a certain amount
    void ReduceHealth(int damage);

    //Print function for testing
    friend std::ostream &operator<<(std::ostream &os, const Enemy& enemy);

private:
    std::string type_; // The enemy's type, i.e. container, infantry, scout, tank
    int speed_; //the enemy's speed, i.e. how many points along the route it will move per game turn
    int radius_; //the radius of the enemy, assuming it is spherical
    int health_; // the health of the enemy
    int routeNumber_; //the index of the location that the enemy is currently on along the route
    int value_;  // the value of the enemy that is to be added to the player's score once defeated
    int freezed_; // The duration of a freeze (the result of being hit by a freeze tower) in game ticks 
};
class Infantry: public Enemy {
public:
    //Constructor for the Infantry-class
    Infantry(int routeNumber = 0, std::string type = "Infantry", int speed = 3, int radius = 20, int health = 30, int value = 35);

    //Destructor for the Infantry-class
    ~Infantry();
};
class Tank : public Enemy {
public:
    //Constructor for the Tank-class
    Tank(int routeNumber = 0, std::string type = "Tank", int speed = 2, int radius = 25, int health = 45, int value = 35);
    //Destructor for the Tank-class
    ~Tank();
};

class Scout : public Enemy {
public:
    //Constructor for the Scout-class
    Scout(int routeNumber = 0, std::string type = "Scout", int speed = 4, int radius = 20, int health = 30, int value = 35);
        //Destructor for the Scout-class
    ~Scout();
};
class Container: public Enemy {
public:
    //Constructor for the Container-class
    Container(int routeNumber = 0, std::string type = "Container", int speed = 2, int radius = 25, int health = 30, int value = 35);

    //Destructor for the Container-class
    ~Container();

};
#endif