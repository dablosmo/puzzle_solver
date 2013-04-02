#include "puzzle_heur.h"
#include <cstdlib>
#include <cmath>

using namespace std;

ManhattanHeuristic::ManhattanHeuristic()
{

}

ManhattanHeuristic::~ManhattanHeuristic()
{

}

int ManhattanHeuristic::calc(int *tiles, int size)
{
  int hscore = 0;
  int dim = static_cast<int>(sqrt(size));
  int solvedIndex = -1;
  int vDistance = 0;
  int hDistance = 0;
  for (int i = 0; i < size; i++)
  { 
    /// set solvedIndex equal to the value of the tile at index i, (position if puzzle is solved)
    /// blank space is not technically a tile so don't have to calculate its solved index.
    if (tiles[i] != 0)
    {
      solvedIndex = tiles[i];
      ///viewing the array of tiles as a 2d array allows us to calculate the shortest distance from the solved index easier
      vDistance = abs( (solvedIndex % dim) - (i % dim) );   ///row numbers of the two indices
      hDistance = abs( (solvedIndex/dim) - (i/dim) );  ///column numbers of the two indices
      hscore = hscore + vDistance + hDistance;   ///addition of these two values is the distance the tile is away from the solved index.
    }
  }
  return hscore;
}


OutOfPlaceHeuristic::OutOfPlaceHeuristic()
{
}

OutOfPlaceHeuristic::~OutOfPlaceHeuristic()
{
}



int OutOfPlaceHeuristic::calc(int *tiles, int size)
{
  int hscore = 0;
  ///go through all the tiles and checks if each tile matches its index. If it doesnt, it adds one to the hscore until it is equal.
  for (int i = 0; i < size; i++)
  {
    if ( (tiles[i] != 0) && (tiles[i] != i) )
    {
      hscore++;
    }
  }
  return hscore;
}
