// #include <iostream>
// #include "tower.hpp"
// #include <vector>


// int main() {

//     Projectile* projectileptr = new Projectile(std::make_pair(3, 3), 5, std::make_pair(3, 3), ((ProjectileType)0), 1, 0, 5);

//     Projectile projectile(std::make_pair(3, 3), 5, std::make_pair(3, 3), ((ProjectileType)0), 1, 0, 5);

//     BasicTower basic(std::make_pair(0, 0), 5, 5, 5, 5, 5);
//     basic.Upgrade();
//     FreezeTower freeze(std::make_pair(1, 1), 5, 6, 6, 6, 6);

//     CannonTower cannon(std::make_pair(2, 2), 5, 7, 7, 7, 7);

//     PulseTower pulse(std::make_pair(3, 3), 5, 8, 8, 8, 8);

//     PulseTower* pulseptr = new PulseTower (std::make_pair(3, 3), 5, 8, 8, 8, 8);

//     std::vector<Projectile> projectileVec; 

//     std::vector<Tower*> towerVec; 

//     // projectileVec.push_back(basic.Fire(std::make_pair(std::make_pair(3, 3),5)));
//     // projectileVec.push_back(projectileptr);

//     towerVec.push_back(pulseptr);

//     std::cout << projectile << std::endl;
//     std::cout << basic << std::endl;
//     std::cout << freeze << std::endl;
//     std::cout << cannon << std::endl;
//     std::cout << pulse << std::endl;
//     std::cout << pulseptr << std::endl;
//     // std::cout << projectileptr << std::endl;
//     std::cout << "Cost method: " << basic.GetCost() << std::endl;
//     std::cout << "Cost method: " << basic.GetCost() << std::endl;

//     // for(auto it : projectileVec) {
//     //     std::cout << "Deleting projectile which radius is " << it->GetRadius() << std::endl;
//     //     delete it;
//     // }

//     for(auto it : towerVec) {
//         std::cout << "Deleting " << it->GetType() << " tower and its' cost is " <<it->GetCost() << " money unit."<< std::endl;
//         delete it;
//     }

//     return 0;
// }