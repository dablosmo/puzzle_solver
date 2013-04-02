#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include "puzzle_solver.h"
#include "pmminlist.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "mylist.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b)
{
  b_ = b;
  expansions_ = 0;
  solution = new MyList<int>;
}


PuzzleSolver::~PuzzleSolver()
{
  delete solution;
}

int PuzzleSolver::run(PuzzleHeuristic *ph)
{
  map<int, Board*> moveMap;
  map<int, Board*>::iterator it;
  vector<PuzzleMove*> garbage;
  PMMinList openList;
  BoardSet closedList;
  BoardSet::iterator set_it;
  Board* boardMaker = new Board(b_);
  PuzzleMove* move = new PuzzleMove(b_);
  PuzzleMove* moveMaker;
  bool boardClosed = false;
  
  move->h_ = ph->calc( (move->b_->getTiles()), (move->b_->getSize()) );
  
  /// Add starting board to the open list
  openList.push(move);
  /// Add starting board to the closed list
  closedList.insert(boardMaker);
  
  while ( !(openList.empty()) && !(b_.solved()) )
  {
    /// Move is the board with the lowest f-value from the open list
    move = openList.top();
    /// Delete it at add it to the garbage list
    openList.pop();
    garbage.push_back(move);
    
    if ( move->b_->solved() )
    {
      /// Put the rest of the moves into the garbage because the board is solved
      while ( !(openList.empty()) )
      {
        garbage.push_back(openList.top());
        openList.pop();
      }
      while ( move->prev_ != NULL )
      {
        /// Moves are stored in reverse order to have lower Big-O
        solution->push_back(move->tileMove_);
        move = move->prev_;
      }
      break;
    }
    /// Make expansions (potential moves)
    moveMap = move->b_->potentialMoves();
    /// For loop goes through each potential move
    for (it = moveMap.begin(); it != moveMap.end(); ++it)
    {
      /// Closed through set to check if potential move exists in the closed list or not
      /// If it does, the boolean variable "boardClosed" will be true and the potential move is already checked.
      for (set_it = closedList.begin(); set_it != closedList.end(); ++set_it)
      {
        if ( *(it->second) == **(set_it) )
        {
          boardClosed = true;
          /// Deallocate the copy of the repeated board in the map.
          delete it->second;
          break;
        }
      }
      if (boardClosed == false)
      {
        /// Makes puzzle moves based on generated potential moves
        moveMaker = new PuzzleMove( (it->first), (it->second), move );  
        /// Calculate h score for puzzle move
        moveMaker->h_ = ph->calc( (moveMaker->b_->getTiles()), (moveMaker->b_->getSize()) );  
        /// Board is added to the closed list while the move is added to the open list
        closedList.insert(moveMaker->b_);
        openList.push(moveMaker);
        /// Keeps track of the number of expansions
        expansions_++;
      }
      boardClosed = false;
    }
    boardClosed = false;
  }
  
  /// Deletes all puzzle moves in the garbage to clear memory
  for (unsigned int i=0; i < garbage.size(); i++)
  {
    delete (garbage[i]);
  }
  /// Deletes starting board that doesn't actually belong to a puzzle move.
  delete boardMaker;
  
  return solution->size();
}


MyList<int>* PuzzleSolver::getSolution()
{
  return solution;
}


int PuzzleSolver::getNumExpansions()
{
  return expansions_;
}


