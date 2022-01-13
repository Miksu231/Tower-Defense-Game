#ifndef PROJECTILE
#define PROJECTILE

#include <iostream>
#include <utility>
#include "math.h"

/* Enumerator for defining projectile types. */
enum class ProjectileType {
    basic,
    cannon,
    freeze
};

/*  Projectile -class represents projectiles which are shooted towards the enemies by towers during the game play.
    Tower -class has Fire function which creates projectiles and projectiles are stored inside of Game class instance in as a 
    shared pointer in a vector. */
class Projectile {
public:
/* Default constructor for Projectile */
    Projectile() = default; 

/* Projectile constructor which has seven arguments. */   
    Projectile(std::pair<int, int> position, int radius, std::pair<int, int> speed, ProjectileType type, int damage, int range, int distanceTravelled = 0); 

/* Getter function which returns projectile type as a Enumration declaration */
    ProjectileType GetType() const;

/* Getter function which returns damage of projectile as an integer. */
    int GetDamage() const;

/* Getter function which returns upper left corner pixel position of the Projectile. First parameter is x-axis, second is parameter is y-axis. */
    std::pair<int, int> GetPosition() const;

/* Getter function which returns center pixel position of the Projectil. First parameter is x-axis, second is parameter is y-axis */
    std::pair<int, int> GetCenterPixel() const;

/* Getter function which returns the radius of the projectile as an integer. */
    int GetRadius() const;

/*  Move function takes a pair of integer which represents a new position as a paramater and update this to be
    Projectiles current position_.  Move function also updates Projectiles distanceTravelled_ variable by adding to it 
    a distance travelled in a one tick based on Projectiles speed. */
    void Move();

/* Function can alter to_be_deleted_ variable's status to be true. */
    void MarkToBeDeleted();

/* Getter function which returns distance travelled by Projectile as an integer. */
    int GetDistance() const;

/* Getter function which returns range of Projectile can move. */
    int GetRange() const;

/* Getter function which returns Projectile's to_be_deleted_ variable.  */
    bool GetStatus() const;
private:
    std::pair<int, int> position_; //Upper left corner position of the Projectile (x-axis, y-axis)
    int radius_; //Radius of the projectile
    std::pair<int, int> speed_; //Speed of the projectile   
    ProjectileType type_; //Type of the projectile
    int damage_; //Damage of the projectile
    int range_; //Range of the projectile
    bool to_be_deleted_; //Status if projectile need to be deleted.
    int distanceTravelled_; //Distance of how many pixels projectile has moved.

    
//Function for testing purpose
friend std::ostream& operator<<(std::ostream&os, const Projectile& projectile);
};

#endif