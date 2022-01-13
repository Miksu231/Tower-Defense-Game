#ifndef MAP
#define MAP

#include <vector>
#include <string>
#include <algorithm>

#include "tile.hpp"

/* Class Map
 *
 * Instance of this class represents a map. Map is collection of tiles, that form the grass areas of
 * the map and enemy path/route. 
 */
class Map {
public:
    //Default constructor needed in the second constructor
    Map() = default;
    //Constructor used to initialize map instance: populates tile vector and constructs enemy path/route
    Map(std::vector<std::vector<TileType>>& tile_types);

    //Returns tiles of the map 
    const std::vector<std::vector<Tile>>& GetTiles() const;

    //Returns map width (number of horizontal tiles)
    int GetWidth();

    //Returns map height (number of vertical tiles)
    int GetHeight();

    //Returns all neighbours of Tile 
    std::vector<std::pair<Tile, int>> GetTileNeighbours(Tile& tile);

    //Returns Tile in the given index (row, column)
    Tile& GetTile(std::pair<int, int> index);

    std::pair<int, int> GetPixel(std::pair<int, int> index);
    
    //Returns the enemy path/route in the map (x,y)
    std::vector<std::pair<int, int>> GetRoute() const;

private:
    std::vector<std::vector<Tile>> tiles_;
    std::vector<std::pair<int,int>> route_;
    int width_;
    int height_;

};

#endif
