#ifndef State_hh
#define State_hh

#include <string>
#include <fstream>

#include "Board.hh"
#include "Score.hh"


/*
 * Class responsible for the management of a game state
 */
class State{
private:
    Score score; // The current score of the game
    Board board; // The current board of the game
    
public:
    /*
     * Constructor
     *
     * Argument:
     * difficulty, the difficulty of the game: 'h' (hard); 'e' (easy)
     *
     * Throw:
     * invalid_argument exception if difficulty is neither equal to 'h' or 'e'
     */
    State(char difficulty);
    
    /*
     * Constructor
     *
     * Argument:
     * fin, file input stream of a saved state
     */
    State(std::ifstream& fin);
    
    /*
     * Compute the display of the state
     *
     * Return:
     * a string containing the display of the state
     */
    std::string getStateDisplay() const;
    
    /*
     * Play the given action from the current state
     *
     * Arguments:
     * action, the given action
     *
     * Return:
     * true if the action has changed the state, false otherwise
     */
    bool play(char action);
    
    /*
     * Check whether the current state is the final state,
     * either because the board is full and no more move can merge 2 tiles (Lost !)
     * or because a tile of value 2048 has been reached (Won !)
     *
     * Return:
     * 1, if the game is won
     * 0, if the game is not finished
     * -1, if the game is lost
     */
    int finalState() const;
    
    /*
     * Get current score value
     *
     * Return:
     * the current score value of the state
     */
    int getScoreValue() const;
    
};


#endif /* State_hh */
