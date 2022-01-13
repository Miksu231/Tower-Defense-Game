#include <iostream>
#include "enemy.hpp"
#include "enemy.cpp"
#include <vector>

int main() {

Infantry InfantryEnemy = Infantry("Infantry", std::make_pair(50, 50), 2, 5, 10, 0, 15);

Tank TankEnemy = Tank("Tank", std::make_pair(0, 0), 1, 10, 30, 1, 35);

Scout ScoutEnemy = Scout("Scout", std::make_pair(0, 50), 4, 5, 5, 2, 25);

Container ContainerEnemy = Container("Container", std::make_pair(50, 0), 2, 15, 15, 3, 30);

std::cout << InfantryEnemy;
std::cout <<TankEnemy;
std::cout <<ScoutEnemy;
std::cout << ContainerEnemy;

InfantryEnemy.~Infantry();
TankEnemy.~Tank();
ScoutEnemy.~Scout();
ContainerEnemy.~Container();
}
