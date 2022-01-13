#ifndef TILE
#define TILE

#include <utility>
#include <string>

// Enumeration types for the different type of tiles
enum TileType {
    Grass,
    Route,
    Start,
    End,
    Wall
};

/* Class Tile
 *
 * Instance of this class represents a tile in the map. Type of a tile can be either wall,
 * road or grass. Enemy path goes along the road blocks. Towers are placed on the grass
 * blocks.
 */
class Tile {
public:
    //Default constructor
    Tile() {}
    
    Tile(std::pair<int, int>& position, int type, bool canPlace = false);

    //Tile's index position on the map, (row, column)
    const std::pair<int, int>& GetPosition() const;

    //Tile's center position on the GUI (y, x)
    std::pair<int, int> GetCenterPixel() const;

    //Tile's corner position on the GUI (y, x)
    std::pair<int, int> GetCornerPixel() const;

    //Returns Tile's TileType enum
    int GetType() const;

    bool GetCanPlace() const;

    void Place(); 

    void UnassignTower();

private:
    //Index position on map (row, column)
    std::pair<int, int> position_;
    int type_;
    bool canPlace_;
};

#endif