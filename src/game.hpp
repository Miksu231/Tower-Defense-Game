#ifndef GAME
#define GAME

#include <memory>
#include <algorithm>
#include <iostream>
#include <SFML/Audio.hpp>
#include "math.h"

#include "constants.hpp"
#include "map.hpp"
#include "tower.hpp"
#include "enemy.hpp"
#include "projectile.hpp"

class LoadingError : public std::exception {
    virtual const char* what() const noexcept {
        return "Could not load game assets";
    }
};

/* Class Game
 *
 * Instance of this class represents the Game object and is the core of the game. 
 * Game instance keeps track of the game situations by storing, creating, updating and removing
 * Tower, Enemy, Map and Projectile -objects. Game -class has public method which can be used 
 * to interact with game for example through the GUI interface.
 */
class Game {
public:
/* Constructor that takes the filename of the map to be loaded as parameter */
    Game(std::string map_filename);

/* Destructor */
    ~Game() {}

/* Copy assignment is not needed */
    Game& operator=(const Game&) = delete;

/* Returns reference to the map */
    Map& GetMap();

/* Returns reference to the vector containing shared pointers of towers */
    std::vector< std::shared_ptr<Tower> >& GetTowers();

/* Returns reference to the vector containing shared pointers of enemies */
    std::vector< std::shared_ptr<Enemy> >& GetEnemies();

/* Returns reference to the vector containing shared pointers of projectiles */
    std::vector< std::shared_ptr<Projectile> >& GetProjectiles();

/* Returns bool value that indicates whether the game has ended/finished */
    bool IsFinished() const;

/* Returns the current amout of the money */
    int GetMoney() const;

/* Returns the future location of the enemy in turns amount of game ticks */
    std::pair<int, int> GetEnemyPositionIn(Enemy& enemy, int turns) const ;

/*  Advances the game by one tick. Calls other method to perform actions.*/
    void Advance () ;
        //check if game has ended -> display score -> Quit game
        //Perform tower targeting -> fire at enemies
        //Advance enemies by one tick
        //Advance projectiles by one tick 
    

/* Starts the game */
    void Start();

/* Pauses the in-game clock */
    void Pause();

/* Quits the game */
    void End();

/* Resumes the the game if paused. */
    void Resume();

/* Restarts the current map */
    void Restart();

/*  BuildTower method takes a index position and a name as parameters. If it is possible to 
 *  build a tower to given position and tower name mathces to some Tower -subclasses shared 
 *    pointer of new tower will be added to towers_ vector. 
 */
    bool BuildTower(std::pair<int, int>, const std::string& name);

/*  MoveTower method takes two index positions (old position and new position) as parameters. 
 *  If there is a tower in old position and space to move tower to new position tower's internal
 *  position will be updated. 
 */
    bool MoveTower(std::pair<int, int>, std::pair<int, int>);

/*  RemoveTower takes a index position as a parameter. If tower with parameter's position
 *  existing in towers_ vector it will be removed. 
 */
    bool RemoveTower(std::pair<int, int>); 

/*  FindTarget takes a shared pointer to tower type object as a parameter. Function checks
 *  if there are enemies within range of the tower which was given as a paramater If target is found, function
 *  returns future position of the target and how many tick in future enemy will be there. If target is not found
 *  function returns std::make_pair(std::make_pair(-1, -1), -100). 
 */
    std::pair<std::pair<int, int>, int> FindTarget(std::shared_ptr<Tower> tower) const;

/*  Return Euclidian distance between to positions */
    int GetDistance(std::pair<int, int> a,std::pair<int, int> b) const;

/*  Checks if projectiles and enemies collide during the game tick. If so, updates status of enemies and projectile which collide */
    void DetectCollision();

/*  Updates counter_ variable by adding it to one or resetting it to zero if upper limit 44999 is reached. */
    void UpdateCount();

/*  Compares index positions of enemies and returns boolean */
    static bool ComparePosition(std::shared_ptr<Enemy>& a, std::shared_ptr<Enemy>& b);

/*  Checks the status of each projectile which has shared pointer in a projectiles_ vector.
 *  Depening on the projectile's status either calls projectile's Move() function or removes
 *  projectile's share pointer from the projectiles_ vector. 
 */
    void AdvanceProjectiles();

/*  Check the stauts of each tower which has shared pointer in a towers_ vector. Depending on the
 *  tower's status uses method of tower for trying to shoot enemies or does nothing. 
 */
    void AdvanceTowers();
    
/*  Updates position of the enemies stored in the enemies_ vector. Enemies positions are tied to predefined route and enemy's speed. 
 *  If some enemy is getting to the end of route also finishing conditionin will be updated.  
 */
    void AdvanceEnemies();

/*  This spawns new enemies to the map if current enemy wave is not empty */
    void SpawnEnemies();

/*  Returns current enemy wave number. */  
    int GetWaveNumber() const;

/*  Removes enemies which healt is zero or less from the enemies_ vector. */
    void RemoveDeadEnemies();

/*  Return boolean status of endPaused_ variable. */
    bool GetEndPausedStatus();

/*  Return boolean status of paused_ variable. */
    bool GetPausedStatus();

/*  Updates endPaused_ variable to the boolean given as a parameter. */
    void SetEndPaused(bool status);

/*  Updates paused_ variable to the boolean given as a parameter. */
    void SetPaused(bool status);

/*  Clears projectiles_ vector. */
    void ClearProjectiles();

/*  Takes a index position as a parameter and checks if there is a tower in given position.
 *  If player has enough money and tower was found in the given position it will be upgraded and 
 *  costs will be deducted from player 
 */
    bool UpgradeTower(std::pair<int, int> index);

/*  Returns status of winning condition*/
    bool GetWinningCondition();

/*  Returns total number of waves for the current map. */
    int GetNumberOfWaves() const;

private:
    Map map_; // Map is saved here.
    std::vector<std::pair<int,int>> route_; // Map specific route is saved here
    std::vector< std::shared_ptr<Tower> > towers_; //Collection of shared pointers to the tower objects which are currently involved in the game.
    std::vector< std::shared_ptr<Enemy> > enemies_; //Collection of shared pointers to the enemy objects which are currently involved in the game.
    std::vector<std::shared_ptr<Enemy>> wave_; //Collection of shared pointers to the enemy objects which are deployed to the enemies_ vector.
    std::vector<std::vector<std::shared_ptr<Enemy>>> waves_; //Collection of waves.
    std::vector< std::shared_ptr<Projectile> > projectiles_; //Collection of shared pointers to the projectile objects which are currently involved in the game.
    bool is_finished_; //
    int money_; //money available for the player
    int wave_number_; // current wave number
    int number_of_waves; // total waves per map.
    std::string map_name_; // name of the map file
    int count_; //internal counter
    bool paused_ = true;    //status of pause
    bool endPaused_ = true; // 
    bool winningCondition_ = false; //status of winning condition
    sf::SoundBuffer pop; //sound buffer
    sf::Sound popSound; // individual sound
};

#endif