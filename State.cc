#include "State.hh"

#include <map>
#include <stdexcept>


using namespace std;

const map<char, int> SIZE = {{'e', 5}, {'h', 4}}; // The mapping between the difficulty of the game
                                                  // and the size of the game board

//
// Class member public functions
//

State::State(char difficulty){
    switch (difficulty) {
        case 'e':
        case 'h':
            board = Board(SIZE.at(difficulty));
            break;
        default:
            string errMsg = "Error in class State: Unexpected difficulty '";
            errMsg += difficulty;
            errMsg += "'";
            throw invalid_argument(errMsg);
            break;
    }
}

State::State(ifstream& fin){
    score = Score(fin);
    board = Board(fin);
}

string State::getStateDisplay() const{
    return score.getScoreDisplay() + "\n" + board.getBoardDisplay();
}

bool State::play(char action){
    bool hasChangedState = board.slide(action, &score);
    if(hasChangedState)
        board.initRandomTile();
    
    return hasChangedState;
}

int State::finalState() const{
    if(board.isWon())
        return 1;
    
    bool canMove = false;
    for(auto action : {'u', 'd', 'l', 'r'}){
        Board testBoard = board;
        if(testBoard.slide(action, nullptr, true)){
           canMove = true;
           break;
        }
    }
    
    return canMove - 1;
}

int State::getScoreValue() const{
    return score.getScore();
}
