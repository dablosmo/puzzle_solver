#include <QtGui/QApplication>
#include "mainwindow.h"

using namespace std;

/** @mainpage CSCI102 PA #4 

    @section purpose Purpose / Overview 
    
    This program adds on to the previous Programming assignment by changing the view of it. Instead of using prompts for user input and 
    command line arguments, the user will use GUI-based controls. For example, they can enter their preferred game options into text boxes
    and click buttons to activate various functions within the program.
    
    @section requirements Requirements 
    
    Requirements include, 
    - Making text boxes where the user can input game options. (Size of board, degree of scramble, seed) 
    - Buttons that allow the user to start game, quit game, and use cheat (A*) 
    - Radio Buttons that allows user to choose which heuristic to use when cheating 
    - Message box that displays errors when the user does something invalid, like try to move a tile that isnt next to a blank
      or try to start the game with unsufficient inputs into the text boxes. 
    - Clicking on the tile will attempt to move it and it is animated to slide to its correct position after the move. 
    - Using cheat will display the moves in order from top to bottom the order of the tile numbers of the 
      tile the user has to click/move to finish the puzzle
    
    
    
*/ 
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
  
    MainWindow w;
    
    w.show();
    return a.exec();
}

