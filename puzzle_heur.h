#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H

using namespace std;

class PuzzleHeuristic
{
 public:
  virtual int calc(int *tiles, int size) = 0;
};


// Define actual Heuristic Classes here
class ManhattanHeuristic : public PuzzleHeuristic
{
  public:
   ManhattanHeuristic();
   ~ManhattanHeuristic();
   ///Calculates the Manhattan h score 
   int calc(int *tiles, int size);
};

class OutOfPlaceHeuristic : public PuzzleHeuristic
{
  public:
   OutOfPlaceHeuristic();
   ~OutOfPlaceHeuristic();
   ///Calculates the Out of Place h score
   int calc(int *tiles, int size);
};

#endif
