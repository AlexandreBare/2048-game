#include "Gameplay.hh"

#include <iostream>
#include <fstream>

using namespace std;

//
// Class member private functions
//

string Gameplay::getGameDisplay() const{
    string gameDisplay;
    
    for(auto i = states.cbegin(); i != states.cend() - 1; i++){
        gameDisplay += i->getStateDisplay() + "\n";
    }
    gameDisplay += states.back().getStateDisplay();
    
    return gameDisplay;
}

void Gameplay::save() const{
    ofstream fout;
    fout.open(savedGameFilename); // Open the file for writing and discard previous content
    if(fout){
        fout << getGameDisplay();
        fout.close();
    }else
        cerr << "\nSaving to file '" << savedGameFilename << "' has failed; Can't open file" << endl;
}

void Gameplay::undo(){
    if(states.size() > 1)
        states.pop_back(); // Remove last element of states
}

void Gameplay::quit(){
    Menu::loadMenu();
}



//
// Class member public functions
//

Gameplay::Gameplay(string _savedGameFilename, char difficulty){
    savedGameFilename = _savedGameFilename;
    if(difficulty == 'e' || difficulty == 'h'){
        states.push_back(State(difficulty));
    }else{
        ifstream fin;
        fin.open(_savedGameFilename);
        if(fin.good()){
            do{
                states.push_back(State(fin));
            }while(!fin.eof());
            fin.close();
        }else{
            throw EmptyFileException();
        }
    }
}

void Gameplay::play(){
    cout << "\n" << states.back().getStateDisplay() << endl;
    char playerIn;
    cin >> playerIn;
    switch(playerIn){
        case 'u':
        case 'd':
        case 'l':
        case 'r':{
            State newState(states.back());
            if(newState.play(playerIn)){
                states.push_back(newState);
                int finalState = newState.finalState();
                if(finalState == 0)
                    play();
                else{
                    cout << "\n" << newState.getStateDisplay() << endl;
                    if (finalState == -1)
                        cout << "\nYOU LOST!" << endl;
                    else
                        cout << "\nYOU WON WITH A SCORE OF "
                             << to_string(newState.getScoreValue())
                             << endl;
                    
                    cin >> playerIn; // Any player input brings back to the menu
                    quit();
                }
            }else
                play();
                
        }break;
        case 'b':
            undo();
            play();
            break;
        case 's':
            save();
            play();
            break;
        case 'q': quit();
            break;
        default:
            cout << "\nInvalid player input '" << to_string(playerIn - '0') // playerIn - '0': char to int conversion
                  << "'\n"
                  << "'u' move Up;\n"
                     "'d' move Down;\n"
                     "'l' move Left;\n"
                     "'r' move Right;\n"
                     "'b' Back: undo last move;\n"
                     "'s' Save current game state to power11.saved;\n"
                     "'q' Quit current game. This option must bring the user back to the welcome menu\n"
                     "Try again\n" << endl;
            play();
            break;
    }
}

