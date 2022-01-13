#include "tile.hpp"
#include "constants.hpp"

Tile::Tile(std::pair<int, int>& position, int type, bool canPlace) :
    position_(position), type_(type), canPlace_(canPlace) { 
        if (type == Grass) canPlace_ = true;
    }
    

const std::pair<int, int>& Tile::GetPosition() const {
        return position_;
}

std::pair<int, int> Tile::GetCenterPixel() const {
    return std::make_pair(position_.first*TILE_SIZE+((TILE_SIZE-1)/2)+1, position_.second*TILE_SIZE+((TILE_SIZE-1)/2)+1);
}

std::pair<int, int> Tile::GetCornerPixel() const {
    return std::make_pair(position_.first*TILE_SIZE, position_.second*TILE_SIZE);
}

int Tile::GetType() const {
    return type_;
}

bool Tile::GetCanPlace() const {
    return canPlace_;
}

void Tile::Place() {
    canPlace_ = false;
}

void Tile::UnassignTower() {
    canPlace_ = true;
}