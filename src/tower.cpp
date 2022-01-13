#include "tower.hpp"
#include "constants.hpp"

Tower::Tower(std::pair<int, int> position, int projectileSpeed, int firerate, int range, int damage, int cost, const std::string& name, int level) 
: position_(position), projectileSpeed_(projectileSpeed), firerate_(firerate), range_(range), damage_(damage), cost_(cost), name_(name), level_(level) {
    fire_status_ =0; //fire_status_ is set as zero when new Tower object is created.
}

std::pair<int, int> Tower::GetPosition() const {
    return position_;
}

std::pair<int, int> Tower::GetCenterPixel() const {
    return std::make_pair(position_.first+round((TILE_SIZE-1)/2)+1, position_.second+round((TILE_SIZE-1)/2)+1);
}

std::vector< std::shared_ptr<Projectile> > Tower::Fire(std::pair<std::pair<int, int>, int> target) {
    std::vector< std::shared_ptr<Projectile> > result = { 
        std::make_shared<Projectile>(GetCenterPixel(), //Projectiles initial position
        5, //radius of projectile
        std::make_pair(round((target.first.first - GetCenterPixel().first) / target.second), //speed of projectile
        round((target.first.second - GetCenterPixel().second) / target.second)), 
        ((ProjectileType)0), //type of projectile
        5, //damage of projectile
        GetRange() //Distance how long projectile can travel.
        )};
    return result;
}

int Tower::GetProjectileSpeed() const {
    return projectileSpeed_;
}

void Tower::Move(std::pair<int, int> newPos) {
    position_ = newPos;
}

int Tower::GetRange() const {
    return range_;
}

void Tower::Upgrade() {
    damage_+= round(damage_*0.3);
    level_++;
}

int Tower::GetCost() const {
    return cost_;
}

const std::string& Tower::GetType() const {
     return name_; 
}
int Tower::GetLevel() const {
   return level_; 
}

int Tower::GetFirerate() const {
    return firerate_;
}

bool Tower::GetFireStatus() {
    if (fire_status_>0){ 
        fire_status_--;
        return false;
    } else {
        return true;
    }
}

int Tower::GetDamage() const {
    return damage_;
}


//for testing
std::ostream &operator<<(std::ostream &os, const Tower& tower) {
    os << "Tower:\n";
    os << "type: " << tower.name_ << std::endl;
    os << "position: " << tower.position_.first << ", " << tower.position_.second << std::endl;
    os << "projectile speed: " << tower.projectileSpeed_ << std::endl;
    os << "firerate: " << tower.firerate_ << std::endl;
    os << "range: " << tower.range_ << std::endl;
    os << "damage:" << tower.damage_ << std::endl;
    os << "cost: " << tower.cost_ << std::endl;
    os << "level: " << tower.level_ << std::endl;
    return os;
}

BasicTower::BasicTower(std::pair<int, int> position,  int projectileSpeed, int firerate, int range, int damage, int cost, const std::string& name)
: Tower( position, projectileSpeed, firerate, range, damage, cost, name) {

}
std::vector< std::shared_ptr<Projectile> > BasicTower::Fire(std::pair<std::pair<int, int>, int> target) {
    fire_status_ = firerate_;
    std::vector< std::shared_ptr<Projectile> > result = { 
        std::make_shared<Projectile>(GetCenterPixel(),
        5, 
        std::make_pair(round((target.first.first - GetCenterPixel().first) / target.second), 
        round((target.first.second - GetCenterPixel().second) / target.second)), 
        ((ProjectileType)0), 
        GetDamage(), 
        GetRange() 
        )};
    return result;
}

FreezeTower::FreezeTower(std::pair<int, int> position, int projectileSpeed, int firerate, int range, int damage, int cost, const std::string& name)
: Tower( position, projectileSpeed, firerate, range, damage, cost, name) {
   
}

std::vector< std::shared_ptr<Projectile> > FreezeTower::Fire(std::pair<std::pair<int, int>, int> target) {
    fire_status_ = firerate_;
    std::vector< std::shared_ptr<Projectile> > result = { 
        std::make_shared<Projectile>(GetCenterPixel(), 
        5, 
        std::make_pair(round((target.first.first - GetCenterPixel().first) / target.second),
        round((target.first.second - GetCenterPixel().second) / target.second)),
        ((ProjectileType)2), 
        GetLevel(), 
        GetRange() 
        )};   
    return result;
}



CannonTower::CannonTower(std::pair<int, int> position, int projectileSpeed, int firerate, int range, int damage, int cost, const std::string& name)
: Tower( position, projectileSpeed, firerate, range, damage, cost, name) {
    
}

std::vector< std::shared_ptr<Projectile> > CannonTower::Fire(std::pair<std::pair<int, int>, int> target) {
    fire_status_ = firerate_;
    std::vector< std::shared_ptr<Projectile> > result = { 
        std::make_shared<Projectile>(GetCenterPixel(),
        15,
        std::make_pair(round((target.first.first - GetCenterPixel().first) / target.second),
        round((target.first.second - GetCenterPixel().second) / target.second)),
        ((ProjectileType)1),
        GetDamage(),
        GetRange()
        )};
    return result;
}

PulseTower::PulseTower(std::pair<int, int> position,  int projectileSpeed, int firerate, int range, int damage, int cost, const std::string& name)
: Tower( position, projectileSpeed, firerate, range, damage, cost, name) {
    
}

std::vector< std::shared_ptr<Projectile> > PulseTower::Fire(std::pair<std::pair<int, int>, int> target) {
    fire_status_ = firerate_;
    std::vector< std::shared_ptr<Projectile> > result = { 
        std::make_shared<Projectile>(GetCenterPixel(), 5 * target.second/target.second, std::make_pair(0, -GetProjectileSpeed()), ((ProjectileType)0), GetDamage(), GetRange() ), // target.second/target.second added just to get rid of warning.
        std::make_shared<Projectile>(GetCenterPixel(), 5, std::make_pair(GetProjectileSpeed(), 0), ((ProjectileType)0), GetDamage(), GetRange() ),
        std::make_shared<Projectile>(GetCenterPixel(), 5, std::make_pair(0, GetProjectileSpeed()), ((ProjectileType)0), GetDamage(), GetRange() ),
        std::make_shared<Projectile>(GetCenterPixel(), 5, std::make_pair(-GetProjectileSpeed(), 0), ((ProjectileType)0), GetDamage(), GetRange() ),
        std::make_shared<Projectile>(GetCenterPixel(), 5, std::make_pair(round((GetProjectileSpeed()*3)/4), round((GetProjectileSpeed()*3)/4)), ((ProjectileType)0), GetDamage(), GetRange() ),
        std::make_shared<Projectile>(GetCenterPixel(), 5, std::make_pair(round(-(GetProjectileSpeed()*3)/4), -round((GetProjectileSpeed()*3)/4)), ((ProjectileType)0), GetDamage(), GetRange() ),
        std::make_shared<Projectile>(GetCenterPixel(), 5, std::make_pair(round(-(GetProjectileSpeed()*3)/4), round((GetProjectileSpeed()*3)/4)), ((ProjectileType)0), GetDamage(), GetRange() ),
        std::make_shared<Projectile>(GetCenterPixel(), 5, std::make_pair(round((GetProjectileSpeed()*3)/4), -round((GetProjectileSpeed()*3)/4)), ((ProjectileType)0), GetDamage(), GetRange() ),
        };
    return result;
}