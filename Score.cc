#include "Score.hh"

#include <stdexcept>

#define SCORE_FORMAT "Score: "

using namespace std;

//
// Class member public functions
//

Score::Score(ifstream& fin){
    string read;
    getline(fin, read);
    
    // rfind returns the position of the first character of the last match,
    // knowing the match should start at maximum position 0 in SCORE_STRING
    if(read.rfind(SCORE_FORMAT, 0) == 0){
        int length = sizeof(SCORE_FORMAT) / sizeof(char) - 1;
        score = stoi(read.substr(length));
    }else
        throw invalid_argument("Exception in class Score: Wrong format in the input file stream to obtain the score");
}

void Score::updateScore(int toAdd){
    score += toAdd;
}

int Score::getScore() const{
    return score;
}

string Score::getScoreDisplay() const{
    return SCORE_FORMAT + to_string(score);
}
