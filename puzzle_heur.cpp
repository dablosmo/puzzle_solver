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
    /// Set solvedIndex equal to the value of the tile at index i, (position if puzzle is solved)
    /// Blank space is not technically a tile so don't have to calculate its solved index.
    if (tiles[i] != 0)
    {
      solvedIndex = tiles[i];
      /// Viewing the array of tiles as a 2d array allows us to calculate the shortest distance from the solved index easier
      
      vDistance = abs( (solvedIndex % dim) - (i % dim) );   
      /// Take modulus of a tile's current index and its solved index by dim gives the  row numbers of the two indices
      /// Subtracting the two indices and then getting the absolute value is the difference in rows
      
      hDistance = abs( (solvedIndex/dim) - (i/dim) );  
      /// Taking the integer divisions of the two indives by dim gives the number of columns of each index
      /// Subtracting the two indices and then getting the absolute value  returns the difference in columns
      
      hscore = hscore + vDistance + hDistance;   
      /// Addition of these two differences is the distance the tile is away from the solved index.
      /// This is done for every tile to get the total distance for the Manhattan Heuristic
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
  /// Go through all the tiles and checks if each tile matches its index. If it doesnt, it adds one to the hscore until it is equal.
  for (int i = 0; i < size; i++)
  {
    if ( (tiles[i] != 0) && (tiles[i] != i) )
    {
      hscore++;
    }
  }
  return hscore;
}
