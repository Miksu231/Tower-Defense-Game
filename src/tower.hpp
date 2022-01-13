#ifndef TOWER
#define TOWER

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "math.h"

#include "projectile.hpp"

/*  Tower -class is base class for the towers. It has following subclasses: BasicTower, FreezeTower, CannonTower and
    pulseTower. Tower object represents a tower which can shoot enemies when enemies are wihtin its range.
    Tower -object are created in Game -instance. Shared pointer are used to store them in the vector inside of Game instance.   
    Tower -class has following variables:
    position
    projectileSpeed
    firerate
    range
    damage
    cost
    name
    level
    fire status*/
class Tower {
public:

/* Constructor for Tower -class */
Tower( std::pair<int, int> position, int projectileSpeed, int firerate, int range, int damage, int cost, const std::string& name, int level = 1 );

/* Default desctructor, copy assignment and copy constructors are be used. */

/* Returns upper left corner pixel position of the Tower. First parameter is x-axis, second is parameter is y-axis. */
std::pair<int, int> GetPosition() const;

/* Returns center pixel position of the Tower. First parameter is x-axis, second is parameter is y-axis */
std::pair<int, int> GetCenterPixel() const;

/*  Virtual Fire function takes as a parameter a pair which includes pair of integers (target's future position) 
    and integer (how many turns it takes for target and tower's projectile to move there). Fire method 
    will return vector of projectiles shared pointers.
      */
virtual std::vector< std::shared_ptr<Projectile> > Fire(std::pair<std::pair<int, int>, int>);

/*  Move method takes new position for tower as a parameter and change tower's current position
    to new position. */
void Move(std::pair<int, int>);

/*  Getter function which returns Tower specific projectile speed as a integer. */
int GetProjectileSpeed() const;

/* Multiplies towers damage by 1.3 factor and increases tower level by one */
void Upgrade();

/* Getter function which returns projectile range of tower. */
int GetRange() const;

/* Getter function which returns cost of tower as a integer. */
int GetCost() const;

/* Getter function which returns type of tower as a string. */
const std::string& GetType() const;

/* Getter function which returns level of tower as a integer. */
int GetLevel() const;

/* Getter function which returns firerate of tower as a integer */
int GetFirerate() const;

/* Getter function which returns FireStatus of tower as a boolean. If firestatus_
    variable is zero funciton returns true. Else function returns false and 
    firestatus_ variable is deducted by one. */
bool GetFireStatus();

/* Getter function which returns damage of tower as a integer. */
int GetDamage() const;

/* Print operator for testing purpose. */
friend std::ostream &operator<<(std::ostream &out, const Tower& a);

protected:
std::pair<int, int> position_; //Upper left corner position of the tower (x-axis,y-axis)
int projectileSpeed_; //Projectile speed of the tower
int firerate_; //Firerate of the tower
int range_; // Shooting range of the tover
int damage_; //Damage of the projectile shoot by the tower
int cost_; //Cost of the tower
std::string name_; //Type of the tower
int level_; //Level of the tower
int fire_status_; //Tower can shoot if status is 0
};


/*  BasicTower is subclass from Tower -class. BasicTower shoots standard projectiles with medium firerate, its projectiles cause medium damage,
    it has long range and it is cheap to build. */
class BasicTower : public Tower {
public: 
/* Constructor for BasicTower -class */
BasicTower(std::pair<int, int> position, int projectileSpeed = 19, int firerate = 40, int range = 150, int damage = 5, int cost = 150, const std::string& name = "basic");

/* Default desctructor, copy assignment and copy constructors are be used. */

/* BasicTower specific Fire -method, which projectile are specifed based on BasicTower's variables. */
virtual std::vector< std::shared_ptr<Projectile> > Fire(std::pair<std::pair<int, int>, int>);
};

/* FreezeTower is subclass from Tower -class. Freeze tower shoots projectiles which slows enemies movement. FreezeTower has slow firerate, 
    it has medium range and it is very cheap to build. */
class FreezeTower : public Tower {
public: 
/* Constructor for FreezeTower -class */
FreezeTower(std::pair<int, int> position,  int projectileSpeed = 10, int firerate = 50, int range = 120, int damage = 5, int cost = 100, const std::string& name = "freeze");

/* Default desctructor, copy assignment and copy constructors are be used. */

/* FreezeTower specific Fire -method, which projectile are specifed based on FreezeTower's variables. */
virtual std::vector< std::shared_ptr<Projectile> > Fire(std::pair<std::pair<int, int>, int>);
};

/* PulseTower is subclass from Tower -class. PulseTower shoots eight projectiles (on every 45 degree starting from 0 degree). PulseTower has slow firerate, 
    its projectiles cause medium damage, it has medium range and it is very expensive to build.   */
class PulseTower : public Tower {
public: 
/* Constructor for PulseTower -class shoots eight projectiles (on every 45 degree starting from 0 degree)*/
PulseTower(std::pair<int, int> position,  int projectileSpeed = 10, int firerate = 50, int range = 120, int damage = 5, int cost = 350, const std::string& name = "pulse");

/* Default desctructor, copy assignment and copy constructors are be used. */

/* PulseTower specific Fire -method, which shoots eight projectiles (on every 45 degree starting from 0 degree) which are specifed based on PulseTower's variables. */
virtual std::vector< std::shared_ptr<Projectile> > Fire(std::pair<std::pair<int, int>, int>);
};

/* CannonTower is subclass from Tower -class. CannonTower shoots big size projectiles. It has very slow firerate, 
    its projectiles cause extreme damage, it has long range and it is expensive to build.   */
class CannonTower : public Tower {
public: 
/* Constructor for CannonTower -class */
CannonTower(std::pair<int, int> position, int projectileSpeed = 19, int firerate = 120, int range = 150, int damage = 7, int cost = 250, const std::string& name = "cannon");

/* Default desctructor, copy assignment and copy constructors are be used. */

/* CannonTower specific Fire -method, which projectile are specifed based on CannonTower's variables. */
virtual std::vector< std::shared_ptr<Projectile> > Fire(std::pair<std::pair<int, int>, int>);
};

#endif