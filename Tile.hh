#ifndef Tile_hh
#define Tile_hh

#include <string>


/*
 * Class responsible for the individual managament of the tiles of a board
 */
class Tile{
private:
    int value = 0; // The current value of the tile
    // 0 = default value for empty tile
    
public:
    /*
     * Default Constructor
     */
    Tile(){}
    
    /*
     * Constructor
     *
     * Argument:
     * _value, the tile value
     */
    Tile(int _value);
    
    /*
     * Accessor for the value
     *
     * Return:
     * the value
     */
    int getValue() const;
    
    /*
     * Set the tile value with value 2 (90% of the time) or 4 (10% of the time)
     */
    void setRandomInitialValue();
    
    /*
     * Check whether the tile is empty (of value 0) or not
     *
     * Return:
     * true if the tile is empty (of value 0), false otherwise
     */
    bool isEmpty() const;
    
    /*
     * Check whether the tile has reached the maximum value (2048)
     *
     * Return:
     * true if the tile has reached the maximum value (2048), false otherwise
     */
    bool isMax() const;
    
    /*
     * Overloaded == operator
     *
     * Argument:
     * tile1, the first tile to compare
     *
     * Return:
     * true, if both tiles have the same value, false otherwise
     */
    bool operator==(const Tile& tile) const;
    
    /*
     * Compute the display of the tile (empty tiles are left blank)
     *
     * Return:
     * a string containing the tile display
     */
    std::string getTileDisplay() const;
    
    /*
     * Check whether the tile has merged
     * (flag to be unset externally)
     *
     * Return:
     * true if the tile has merged, false otherwise
     */
    /*bool isAMergedTile(){
        return hasMerged;
    }*/
    
    /*
     * Merge 2 tiles: the first one has its value doubled, the second one is set to an empty tile
     *
     * Arguments:
     * tile1, the first tile
     * tile2, the second tile
     */
    static void merge(Tile& tile1, Tile& tile2);
    
};
#endif /* Tile_hh */
