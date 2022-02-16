#include "Tile.hh"

#include <random>

#define PROPABILITY_2 90
#define TILE_SIZE 4
#define MAX_VALUE 2048

using namespace std;


//
// Class member public functions
//

Tile::Tile(int _value){
    value = _value;
}

int Tile::getValue() const{
    return value;
}

void Tile::setRandomInitialValue(){
    if(rand() % 100 < PROPABILITY_2)
        value = 2;
    else
        value = 4;
}

bool Tile::isEmpty() const{
    return value == 0;
}

bool Tile::isMax() const{
    return value == MAX_VALUE;
}

bool Tile::operator==(const Tile& tile) const{
    return tile.value == value;
}

string Tile::getTileDisplay() const{
    string tileDisplay;
    if(!isEmpty()){
        string valstr = to_string(value);
        tileDisplay = string(TILE_SIZE - valstr.length(), ' ') + valstr;
    }else
        tileDisplay = string(TILE_SIZE, ' ');
    
    return tileDisplay;
}

void Tile::merge(Tile& tile1, Tile& tile2){
    tile1.value *= 2; // double value
    tile2.value = 0; // set empty
}
