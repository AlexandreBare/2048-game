#ifndef Board_hh
#define Board_hh

#include <fstream>
#include <string>
#include <vector>
#include <array>
#include "Tile.hh"
#include "Score.hh"


/*
 * Class responsible for the management of a game state
 */
class Board{
private:
    std::vector<std::vector<Tile>> board; // The current board of tiles
    size_t size; // The size of the board
    bool isWinningBoard = false; // Whether the current board is in a winning state
    
    /*
     * if isSlidingTest is false:
     *      Slide a tile in the given direction until
     *      it reaches a wall or encounters another tile and merges
     *      (if a merged tile reaches the maximum value,
     *      the flag isWinningBoard is set to true)
     *
     * else:
     *      Test if a slide is possible
     *
     * Argument:
     * position, the position of the sliding tile
     * direction, the direction of sliding
     * alreadyMerged, the list of positions of tiles that have
     *                already merged and should not merge anymore
     * score, the score tracker object
     * isSlidingTest, whether the function is just called to test
     *                that sliding is possible
     *                or it should actually slide the tile
     *
     * Return:
     * if isSlidingTest is false:
     *      true if the tile has changed position or merged, false otherwise
     * else:
     *      true if the tile can change position or merge, false otherwise
     */
    bool slideTile(int position[], int direction[], std::vector<std::array<int, 2>>* alreadyMerged = nullptr,
                   Score* score = nullptr, bool isSlidingTest = false);
    
    /*
     * Swap 2 tiles
     *
     * Argument:
     * pos1, the position of the first tile
     * pos2, the position of the second tile
     */
    void swapTiles(int* pos1, int* pos2);
    
public:
    /*
     * Constructor
     */
    Board(){}
    
    /*
     * Constructor
     *
     * Argument:
     * _size, the size of the square board
     */
    Board(size_t _size);
    
    /*
     * Constructor
     *
     * Argument:
     * fin, the file input stream containing the board representation
     */
    Board(std::ifstream& fin);
    
    /*
     * if isSlidingTest is false:
     *      Slide the tiles of the board in the direction specified
     *
     * else:
     *      Test if at least one tile can slide
     *
     * Argument:
     * direction, the direction of sliding
     *            ('u' move Up; 'd' move Down; 'l' move Left; 'r' move Right)
     * score, the score tracker object
     * isSlidingTest, whether the function is just called to test
     *                that sliding is possible
     *                or it should actually slide the tiles
     *
     * Return:
     * if isSlidingTest is false:
     *      true if at least one tile has changed position or merged, false otherwise
     * else:
     *      true if at least one tile can change position or merge, false otherwise
     *
     * Throw:
     * invalid_argument exception if the direction is not valid,
     * ie: not part of {'u' (move Up); 'd' (move Down); 'l' (move Left); 'r' (move Right)}
     */
    bool slide(char direction, Score* score = nullptr, bool isSlidingTest = false);
    
    /*
     * Set an empty tile to its initial value
     * at a random position on the board
     */
    void initRandomTile();
    
    /*
     * Check whether the player has won the game
     * because a tile of maximum value has been reached
     *
     * Return:
     * true, if the game is won
     * false, otherwise
     */
    bool isWon() const;
    
    /*
     * Compute the display of the game board
     *
     * Return:
     * a string containing the display of the game board
     */
    std::string getBoardDisplay() const;
};

#endif /* Board_hh */
