#include <iostream>
#include "game.hpp"

//Some private variables need to be made public in Game class to run this test. Exact variables below
//enemies_
//projectiles_

int main() {

    Game game("map1.txt");

    game.BuildTower(std::make_pair(1, 1), "basic");
    game.BuildTower(std::make_pair(4, 1), "freeze");
    game.BuildTower(std::make_pair(2, 1), "cannon");
    game.BuildTower(std::make_pair(3, 1), "pulse");

    for(auto it : game.GetTowers()) {
        std::cout << "Name: " << it.GetType() << ", Position: (" << it.GetPosition().first << "," << it.GetPosition().second << ")"<< std::endl;
    }

    std::cout << std::endl;

    game.RemoveTower(std::make_pair(1, 1));

    game.MoveTower(std::make_pair(4, 1), std::make_pair(5, 1));

    for(auto it : game.GetTowers()) {
        std::cout << "Name: " << it.GetType() << "Position: (" << it.GetPosition().first << "," << it.GetPosition().second << ")"<< std::endl;
    }

    std::cout << game.GetTowers().size() << std::endl;

    //Enemy(std::string type, std::pair<int, int> position, int speed, int radius, int health, int routeNumber, int value);



    game.enemies_.push_back(Tank("Tank4", std::make_pair(19, 19), 1, 10, 30, 1, 35));

    //Projectile::Projectile(std::pair<int, int> position, int radius, std::pair<int, int> speed, ProjectileType type, int damage, int range, int distanceTravelled)
    game.projectiles_.push_back(Projectile(std::make_pair(3, 3), 5, std::make_pair(3, 3), ((ProjectileType)0), 40, 10, 5));
    game.projectiles_.push_back(Projectile(std::make_pair(3, 3), 5, std::make_pair(3, 3), ((ProjectileType)0), 10, 10, 5));
    game.projectiles_.push_back(Projectile(std::make_pair(3, 3), 5, std::make_pair(3, 3), ((ProjectileType)0), 10, 10, 5));
    game.projectiles_.push_back(Projectile(std::make_pair(10, 10), 5, std::make_pair(3, 3), ((ProjectileType)0), 10, 10, 5));

    std::cout << "---" << std::endl;
    for(auto it : game.GetEnemies()) {
        std::cout << "Name: " << it.GetType() << "Health: " << it.GetHealth() << std::endl;
    }
    std::cout << "---" << std::endl;
    for(auto it : game.GetProjectiles()) {
        std::cout << "type: " << static_cast<std::underlying_type<ProjectileType>::type>(it.GetType()) << std::endl;
    }

    game.DetectCollision();
    std::cout << "---" << std::endl;
    for(auto it : game.GetEnemies()) {
        std::cout << "Name: " << it.GetType() << "Health: " << it.GetHealth() << std::endl;
    }

    std::cout << "---" << std::endl;
    for(auto it : game.GetProjectiles()) {
        std::cout << "type: " << static_cast<std::underlying_type<ProjectileType>::type>(it.GetType()) << std::endl;
    }


    return 0;
}