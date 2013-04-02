#include <iostream>
#include <cstdlib>
#include <deque>
#include <map>
#include <stdexcept>
#include <cmath>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "pmminlist.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 4){
    cerr << "Usage: ./puzzle size initMoves seed" << endl;
    return 1;
  } 
  
  if(argc > 4)
  {
    cerr << "More than 4 command line arguments" <<endl; 
    return 1;
  } 

  int size, initMoves, seed;

  size = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]); 
  
  if(sqrt(size) != floor(sqrt(size)))
  {
    cerr << "Invalid size, please enter a size that would create a square." <<endl;
    return 1; 
  }

  Board b(size,initMoves,seed);

  //**** Implement the gameplay here
  
  OutOfPlaceHeuristic selectHeuristic;
  int selectTile = -100; 
  while (true) 
  {
    cout << b; 
    cout << endl; 
    cout << "Enter number of the tile to move or -1 for cheat "; 
    cin >> selectTile; 
    
    ///Error handling to see if user entered an integer or not 
    if (cin.fail()) 
    {
      cerr << "Please enter the number of a tile on the board" <<endl;; 
      cout << endl; 
      cin.clear();
      cin.ignore(1000, '\n'); 
      continue; 
    } 
    
    ///Error handling to see if tile is a tile on the board
    if (selectTile >= b.getSize() || selectTile < -1 || selectTile == 0) 
    {
      cerr << "That tile is not a valid selection. Please enter a tile that actually exists on the board";
      cout << endl; 
      continue; 
    } 
    
    /// If the user wants to cheat 
    if (selectTile == -1) 
    {
      PuzzleSolver solver(b); 
      solver.run(&selectHeuristic); 
      cout << "Try this sequence: "; 
      for (int i=(solver.getSolution())->size(); i>0; i--) 
      {
        cout << (*(solver.getSolution()))[i-1] << " "; 
      } 
      cout << endl; 
      cout << "(Expansions = " << solver.getNumExpansions() << ")" <<endl; 
      cout << endl; 
    } 
    
    else
    {
      try
      {
        b.move(selectTile); 
        cout << endl; 
      } 
      catch(invalid_argument &i)
      {
        cerr << i.what() << endl;
        cout<<endl; 
        continue; 
      } 
      catch(exception &e) 
      {
        cerr << "Tile is not next to a blank. Enter a valid tile that is adjacent to the blank" << endl; 
        cout << endl; 
        continue; 
      }
    
      if (b.solved()) 
      {
        cout << b; 
        cout << "You did it!" << endl; 
        break; 
      } 
    } 
  }
  return 0;
}

