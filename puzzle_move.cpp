#include "puzzle_move.h"
#include "puzzle_heur.h"

using namespace std;

PuzzleMove::PuzzleMove(Board &b) 
{ 
  ManhattanHeuristic calculator;
  tileMove_ = -1;
  b_ = new Board(b);
  prev_ = NULL;
  g_ = 0;
  h_ = calculator.compute(b_->getTiles(), b_->getSize());
}

PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent)
{
  ManhattanHeuristic calculator;
  tileMove_ = tile; 
  b_ = b; 
  prev_ = parent; 
  g_ = prev_->g_+1; 
  h_ = calculator.compute(b_->getTiles(), b_->getSize());
}

PuzzleMove::~PuzzleMove() 
{
  delete b_; 
} 


// Compare to PuzzleMoves based on f distance (needed for priority queue
bool PuzzleMove::operator<(const PuzzleMove& p) const
{
  if((g_ + h_) < (p.g_ + p.h_)){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ > p.g_)){
    return true;
  }
  else {
    return false;
  }
}
bool PuzzleMove::operator>(const PuzzleMove& p) const
{
  if( (g_ + h_) > (p.g_ + p.h_) ){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ < p.g_) ){
    return true;
  }
  else {
     return false;
  }
  
}

bool PuzzleMove::operator==(const PuzzleMove& p) const 
{ 
  if((g_+h_ == p.g_+p.h_) && (g_==p.g_)) 
  {
    return true; 
  } 
  return false;
}

