#ifndef Score_hh
#define Score_hh

#include <fstream>
#include <string>


/*
 * Class responsible for the management of the score
 */
class Score{
private:
    int score = 0; // The current score value
    
public:
    /*
     * Default constructor
     */
    Score(){}
    
    /*
     * Constructor
     *
     * Argument:
     * fin, the file input stream containing the score representation
     *
     * Throw:
     * invalid_argument exception if fin does not contain the right format
     */
    Score(std::ifstream& fin);
    
    /*
     * Update the score by adding points
     *
     * Argument:
     * toAdd, the points to add to the score
     */
    void updateScore(int toAdd);
    
    /*
     * Accessor of the score
     *
     * Return:
     * the score
     */
    int getScore() const;
    
    /*
     * Compute the display of the score
     *
     * Return:
     * a string containing the display of the score
     */
    std::string getScoreDisplay() const;
};
#endif /* Score_hh */
