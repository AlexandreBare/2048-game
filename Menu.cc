#include "Menu.hh"

#include <iostream>
#include <string>

#define SAVED_GAME_FILENAME "power11.saved"

using namespace std;

//
// Functions
//

int main(){
    try{
        Menu::loadMenu();
    }catch(const invalid_argument& e){
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}

/*
 * Display the welcome menu on the terminal
 * ('e' start a new Easy (5-by-5) game;
 *  'h' start a new Hard (4-by-4) game;
 *  'r' Resume the last saved game;
 *  'q' Quit the game)
 */
static void displayMenu(){
    cout << "\n\nWelcome !\n\nPress\n"
            "- 'e' for a new Easy (5-by-5) game\n"
            "- 'h' for a new Hard (4-by-4) game\n"
            "- 'r' to Resume the last saved game\n"
            "- 'q' to Quit the game\n" << endl;
}


/*
 * Read the menu option chosen and process it
 * ('e' start a new Easy (5-by-5) game;
 *  'h' start a new Hard (4-by-4) game;
 *  'r' Resume the last saved game;
 *  'q' Quit the game)
 */
static void readOption(){
    char read;
    cin >> read;
    
    switch(read){
        case 'e':
        case 'h':{
            Gameplay gameplay(SAVED_GAME_FILENAME, read);
            gameplay.play();
        }break;
        case 'r':{
            try{
                Gameplay gameplay(SAVED_GAME_FILENAME);
                gameplay.play();
            }catch(EmptyFileException){
                cout << "\nNo game saved" << endl;
                Menu::loadMenu();
            }
        }break;
        case 'q': // Nothing to be done
            break;
        default: Menu::loadMenu();
            break;
    }
}


//
// Class member static function
//

void Menu::loadMenu(){
    displayMenu();
    readOption();
}
