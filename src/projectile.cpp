#include "projectile.hpp"

Projectile::Projectile(std::pair<int, int> position, int radius, std::pair<int, int> speed, ProjectileType type, int damage, int range, int distanceTravelled) :
        position_(position), radius_(radius), speed_(speed), type_(type), damage_(damage), range_(range), distanceTravelled_(distanceTravelled) {
            to_be_deleted_ = false; // as a default to_be_deleted is false.
        }

ProjectileType Projectile::GetType() const{
    return type_;
}

std::pair<int, int> Projectile::GetPosition() const {
    return position_;
}

std::pair<int, int> Projectile::GetCenterPixel() const {
    return std::make_pair(round(position_.first + radius_/2), round(position_.second+radius_/2));
}

int Projectile::GetRadius() const{
    return radius_;
}

void Projectile::Move(){
    position_ = std::make_pair(position_.first + speed_.first, position_.second + speed_.second);
    distanceTravelled_ += round(sqrt(speed_.first*speed_.first + speed_.second*speed_.second));
}

void Projectile::MarkToBeDeleted() {
    to_be_deleted_ = true;
}

int Projectile::GetDamage() const {
    return damage_;
}

int Projectile::GetDistance() const {
    return distanceTravelled_;
}

int Projectile::GetRange() const {
    return range_;
}

bool Projectile::GetStatus() const {
    return to_be_deleted_;
}

std::ostream& operator<<(std::ostream& os, const Projectile& projectile){
    os << "PROJECTILE:\n";
    os << "position: " << projectile.position_.first << ", " << projectile.position_.second << "\n";
    os << "speed: " << projectile.speed_.first << ", " << projectile.speed_.second << "\n";
    os << "type: " << static_cast<std::underlying_type<ProjectileType>::type>(projectile.type_) << std::endl;
    return os;

}
