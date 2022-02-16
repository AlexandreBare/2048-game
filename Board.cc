#include "Board.hh"

#include <stdexcept>
#include <algorithm>
#define BOARD_FORMAT "#"

using namespace std;


//
// Functions
//

/*
 * Function that computes whether the array limit
 * (the beginning or end) has been reached
 *
 * Argument:
 * n, the current position in the array
 * size, the size of the array
 *
 * Return:
 * true, if the array has reached a limit, false otherwise
 */
static bool isLimit(int n, int size){
    return n < size && n >= 0;
}



//
// Class member private functions
//

bool Board::slideTile(int position[], int direction[], vector<array<int, 2>>* alreadyMerged, Score* score, bool isSlidingTest){
    bool hasJustMerged = false;
    bool hasMoved = false;
    bool hasBumpedIntoAnotherTile = false;
    int nextPos[] = {position[0] + direction[0], position[1] + direction[1]};
    while(!hasBumpedIntoAnotherTile && isLimit(nextPos[0], (int)size) && isLimit(nextPos[1], (int)size)){
        if(!board[nextPos[0]][nextPos[1]].isEmpty()){
            hasBumpedIntoAnotherTile = true;
            if(board[nextPos[0]][nextPos[1]] == board[position[0]][position[1]]){
                
                if(isSlidingTest)
                    return true;
                
                else{
                    
                    if(alreadyMerged != nullptr){
                       auto predicate = [nextPos](auto position) {
                           return nextPos[0] == position[0] && nextPos[1] == position[1];
                       };
                       if(find_if(alreadyMerged->cbegin(),
                                  alreadyMerged->cend(),
                                  predicate) == alreadyMerged->cend()){
                           Tile::merge(board[nextPos[0]][nextPos[1]], board[position[0]][position[1]]);
                           alreadyMerged->push_back(array<int, 2>{nextPos[0], nextPos[1]});
                           // Save the position of the tiles already merged this round
                           hasMoved = true;
                           hasJustMerged = true;
                       }
                        
                    }else{
                        Tile::merge(board[nextPos[0]][nextPos[1]], board[position[0]][position[1]]);
                        hasMoved = true;
                        hasJustMerged = true;
                    }
                    
                    if(hasJustMerged){
                        hasJustMerged = false;
                    
                        if(score != nullptr){
                            score->updateScore(board[nextPos[0]][nextPos[1]].getValue());
                        }
                        
                        if(board[nextPos[0]][nextPos[1]].isMax())
                            isWinningBoard = true;
                    }
                    
                }
            }
        }else if (!board[position[0]][position[1]].isEmpty()){
            if(isSlidingTest)
                return true;
            else{
                Board::swapTiles(nextPos, position);
                hasMoved = true;
            }
        }
        
        position[0] = nextPos[0];
        position[1] = nextPos[1];
        nextPos[0] += direction[0];
        nextPos[1] += direction[1];
    }
    
    return hasMoved;
}

void Board::swapTiles(int* pos1, int* pos2){
    Tile buffer = board[pos1[0]][pos1[1]];
    board[pos1[0]][pos1[1]] = board[pos2[0]][pos2[1]];
    board[pos2[0]][pos2[1]] = buffer;
}



//
// Class member public functions
//

Board::Board(size_t _size){
    size = _size;
    board.resize(_size);
    for(size_t i = 0; i < _size; i++){
        board[i].resize(_size);
    }
    initRandomTile();
}

Board::Board(ifstream& fin){
    string readLine;
    
    // rfind(BOARD_FORMAT, 0) returns the position of the first character of the last match,
    // knowing the match should start at maximum position 0 in BOARD_STRING
    if(getline(fin, readLine) && readLine.rfind(BOARD_FORMAT, 0) == 0){
        size = (readLine.length() - 1) / 5;
        board.resize(size);
        size_t i = 0;
        while(i < size && getline(fin, readLine) && readLine.rfind(BOARD_FORMAT, 0) == 0){
            bool firstCol = true;
            string readNumber = "";
            for(char c : readLine){
                if(isdigit(c) || isspace(c))
                    readNumber += c;
                else if(readNumber != ""){
                    if(firstCol){
                        board[i].reserve(size);
                        firstCol = false;
                    }
                    try{
                        board[i].push_back(Tile(stoi(readNumber)));
                    }catch(invalid_argument& e){
                        board[i].push_back(Tile());
                    }
                    readNumber = "";
                }
            }
            i++;
        }
        
        getline(fin, readLine); // remove last line of the board representation ("###...###")
    }else
        throw invalid_argument("Exception in class Board: Wrong format in the input file stream for the game board");
}

bool Board::slide(char direction, Score* score, bool isSlidingTest){
    int startRow = 0;
    int startCol = 0;
    int rowUpdate = 1;
    int colUpdate = 1;
    int rowDirection = 0;
    int colDirection = 0;
    
    switch(direction){
        case 'u':
            startRow = 1;
            rowDirection = -1;
            break;
        case 'd':
            startRow = (int) (size - 2);
            rowUpdate = -1;
            rowDirection = 1;
            break;
        case 'l':
            startCol = 1;
            colDirection = -1;
            break;
        case 'r':
            startCol = (int) (size - 2);
            colUpdate = -1;
            colDirection = 1;
            break;
        default: throw invalid_argument("Exception in class Board: invalid direction of slide '" + to_string(direction) + "'\nValid direction:\n"
                                        "'u' move Up;\n"
                                        "'d' move Down;\n"
                                        "'l' move Left;\n"
                                        "'r' move Right\n");
            break;
    }
    
    bool hasATileMoved = false;
    vector<array<int, 2>> alreadyMerged;
    for(int row = startRow; isLimit(row, (int)size); row += rowUpdate){
        for(int col = startCol; isLimit(col, (int)size); col += colUpdate){
            int position[] = {row, col};
            int direction[] = {rowDirection, colDirection};
            if(slideTile(position, direction, &alreadyMerged, score, isSlidingTest)){
                if(isSlidingTest)
                    return true;
                else
                    hasATileMoved = true;
            }
        }
    }
    
    return hasATileMoved;
}

void Board::initRandomTile(){
    size_t i, j;
    
    do{
        i = rand() % size;
        j = rand() % size;
    }while(!board[i][j].isEmpty());
    
    board[i][j].setRandomInitialValue();
}


bool Board::isWon() const{
    return isWinningBoard;
}

string Board::getBoardDisplay() const{
    size_t boardRepLength = 1 + 2 * size;
    size_t wallSize = 1 + 5 * size;
    
    string hWall;
    for (size_t i = 0; i < wallSize; i++){
        hWall += "#";
    }
    
    string boardDisplay = hWall + "\n";
    int col = 0;
    for (size_t row = 0; row < size; row++){
        for(size_t j = 0; j < boardRepLength; j++){
            if(j == 0 || j == boardRepLength - 1)
                boardDisplay += "#";
            else if(j % 2){
                boardDisplay += board[row][col].getTileDisplay();
                col++;
            }else
                boardDisplay += "|";
        }
        col = 0;
        boardDisplay += "\n";
    }
    boardDisplay += hWall;
    
    return boardDisplay;
}

