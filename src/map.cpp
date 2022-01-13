#include "map.hpp"
#include "constants.hpp"
#include <iostream>

Map::Map(std::vector<std::vector<TileType>>& tile_types){
    width_ = tile_types[0].size();
    height_ = tile_types.size();

    //Populate tile vector based on the data read from the file
    int row = 0;
    for (auto r : tile_types){
        tiles_.push_back(std::vector<Tile>());
        int column = 0;
        for (auto type : r) {
            std::pair<int,int> position = std::make_pair(row,column);
            tiles_[row].push_back(Tile(position, type));
            column++;
        }
        row++;
    }

    //Find the Start tile
    Tile start;
    for (auto r : tiles_){
        for (auto c : r){
            if (c.GetType() == Start){
                start = c;
            }
        }
    }

    //Helper variables used in the route construction
    bool end = false;
    Tile next = start;
    int restricted;
    std::pair<int, int> center;

    //Route starts from the center pixel of the Start tile
    route_.push_back(start.GetCenterPixel());

    //This while loop constructs the enemy path on pixel level starting from the middle pixel of the
    //Start tile and ending to the middle pixel of the End tile.
    while (!end) {
        for (auto n : GetTileNeighbours(next)){
            if ((n.first.GetType() == Route || n.first.GetType() == End) && n.second != restricted) {
                if (n.first.GetType() == End) {
                    end = true;
                }
                next = n.first;

                switch (n.second)
                {
                //up
                case 1:
                    center = route_.back(); 
                    for (int i = 1; i <= TILE_SIZE; i++){
                        route_.push_back(std::make_pair(center.first-i, center.second));
                        restricted = 3;
                    }
                    break;
                //right
                case 2:
                    center = route_.back(); 
                    for (int i = 1; i <= TILE_SIZE; i++){
                        route_.push_back(std::make_pair(center.first, center.second+i));
                        restricted = 4;
                    }
                    break;
                //down
                case 3:
                    center = route_.back(); 
                    for (int i = 1; i <= TILE_SIZE; i++){
                        route_.push_back(std::make_pair(center.first+i, center.second));
                        restricted = 1;
                    }
                    break;
                //left
                case 4:
                    center = route_.back();  
                    for (int i = 1; i <= TILE_SIZE; i++){
                        route_.push_back(std::make_pair(center.first, center.second-i));
                        restricted = 2;
                    }
                    break;
                }
                break;
            }
        }
    }
}

const std::vector<std::vector<Tile>>& Map::GetTiles() const {
    return tiles_;
}

int Map::GetWidth() {
    return width_;
}

int Map::GetHeight() {
    return height_;
}

std::vector<std::pair<Tile, int>> Map::GetTileNeighbours(Tile& tile) {
    //Location of the tile whose neighbours we are searching
    std::pair<int,int> location = tile.GetPosition();

    //Vector for neighbours, int in the pair indicates in which direction the neighbour is located.
    //That information is used in map constructor when enemy path is created
    std::vector<std::pair<Tile, int>> neighbours;

    //column (y-axis)
    //up - 1
    if (location.first > 0) neighbours.push_back(std::make_pair(tiles_[location.first-1][location.second], 1));
    //down - 3
    if (location.first < height_-1) neighbours.push_back(std::make_pair(tiles_[location.first+1][location.second], 3));

    //row (x-axis)
    //left - 4
    if (location.second > 0) neighbours.push_back(std::make_pair(tiles_[location.first][location.second-1], 4));
    //right - 2
    if (location.second < width_-1) neighbours.push_back(std::make_pair(tiles_[location.first][location.second+1], 2));

    return neighbours;
}

Tile& Map::GetTile(std::pair<int, int> index) {
    return tiles_[index.first][index.second];
}

//This might be redundant duplicate
std::pair<int, int> Map::GetPixel(std::pair<int, int> index) {
    return std::make_pair(TILE_SIZE*index.second, TILE_SIZE*index.first);
}

std::vector<std::pair<int, int>> Map::GetRoute() const {
    return route_;
}
