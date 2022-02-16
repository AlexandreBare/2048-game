#ifndef Gameplay_hh
#define Gameplay_hh

#include <vector>
#include "Menu.hh"
#include "State.hh"
#include "EmptyFileException.hh"


/*
 * Class responsible for the interactions with the player during the game
 */
class Gameplay{
private:
    std::vector<State> states;  // All the accumulated states of the game
    std::string savedGameFilename; // The name of the file to save a game
    
    /*
     * Compute the display of the whole game
     *
     * Return:
     * a string containing the display of the whole game
     */
    std::string getGameDisplay() const;
    
    /*
     * Save the game to the appropriate file
     */
    void save() const;
    
    /*
     * Remove the last state of the game
     */
    void undo();
    
    /*
     * Quit the game and go back to the welcome menu
     */
    static void quit();

    
public:
    /*
     * Constructor
     * Build a gameplay object based on the content of a file or
     * based on the difficulty of the game
     *
     * Arguments:
     * _savedGameFilename, the name of the file to save/load the game
     * difficulty, the difficulty of the game: 'h' (hard); 'e' (easy)
     *             (not to be given if the game is loaded from file)
     *
     * Throw:
     * EmptyFileException if the game is build from a file and the file is empty
     */
    Gameplay(std::string _savedGameFilename, char difficulty = '\0');
    
    /*
     * Respond to the input with the correct playing action
     * ('u' move Up;
     *  'd' move Down;
     *  'l' move Left;
     *  'r' move Right;
     *  'b' Back: undo last move;
     *  's' Save current game state to power11.saved;
     *  'q' Quit current game. This option must bring the user back to the welcome menu)
     */
    void play();
    
};


#endif /* Gameplay_hh */
