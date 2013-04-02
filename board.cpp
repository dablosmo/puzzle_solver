#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


/** Init a board of given size and scramble it with numInitMoves 
 * by moving the space tile with a randomly chosen direction N, W, S, E
 * some of which may be invalid, in which case we skip that move 
 * 
 *  @param size Number of tiles for the game.  \
 *      Should be a perfect square (4, 16, 25)
 *  @param numInitMoves Number of tile moves to attempt to scramble the board
 *  @param seed Use to seed the random number generator (srand) 
 */
Board::Board(int size, int numInitMoves, int seed )
{
  size_ = size;
  tiles_ = new int[size_];
  int dim = static_cast<int>(sqrt(size_));
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  for(int i=0; i < numInitMoves; i++){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
    }
  } 
  blankLoc_ = blankLoc;
}


/** Default constructor. provide documentation here */
Board::Board()
{
}

/** Copy constructor that performs a deep copy */
Board::Board(const Board &b)
{
  size_ = b.getSize();
  blankLoc_ = b.getblankLoc();
  tiles_ = new int[size_];  
  for(int i=0; i<b.size_; i++) 
  {
    tiles_[i] = (b.tiles_)[i];
  }
}

/** Another kind of "copy" constructor, Makes a board with input tiles and size */

Board::Board(int *tiles, int size)
{
  size_ = size;
  tiles_ = new int[size_]; 
  for(int i=0; i<size_; i++) 
  {
    tiles_[i] = tiles[i];
    if(tiles[i] == 0) 
    {
      blankLoc_ = i; 
    } 
  } 
}

/** Default destructor. Deletes the tile data */
Board::~Board()
{
  delete[] tiles_;
}

/** Swaps the blank with the specified tile */
void Board::move(int tile)
{
  int tileIndex = -100; 
  
  ///Go through Board to find the index of selected tile 
  for(int i = 0; i < size_; i++)
  {
    if(tiles_[i] == tile)
    {
      tileIndex = i;
      break;
    }
  } 
  
  ///Error handling in case the tile was not found on the board. 
  if(tileIndex == -100) 
  {
    throw invalid_argument("Tile is not on the board"); 
  } 
  
  ///Check to see if tile is adjacent to the blank tile 
  ///makes the direction where tiles do not exist invalid by making them negative.
  int dim = static_cast<int>(sqrt(size_));
  int n = blankLoc_ - dim;
  int e = blankLoc_ + 1;
  int s = blankLoc_ + dim;
  int w = blankLoc_ - 1;
  
  ///Check blocks left, right and below of blank space to see if they exist. 
  ///Checking the block above is unnecessary because if the blank is on the top row then blankLoc - dim is negative.
  ///Check Right
  if (e % dim == 0)
  {
    e = -1; 
  }
  ///Check Below
  if (s >= size_)
  {
    s = -1;
  }
  ///Check Left
  if (blankLoc_ % dim == 0)
  {
    w = -1;
  }
  
  ///Utilize values of n, e, s, and w to see if the index of the selected tile is next to blank or not.
  ///If it isn't then an exception is thrown. 
  ///This is to prevent the valid between the blank that is in the far right and a tile to the right of it.
  if ((tileIndex != n) && (tileIndex != e) && (tileIndex != s) && (tileIndex != w)) 
  {
    throw exception(); 
  } 
  
  ///swap the location of the blank with the selected tile 
  tiles_[blankLoc_] = tile;
  tiles_[tileIndex] = 0;
  blankLoc_ = tileIndex;
}

 /** Generate potential moves and returns new boards
   * Key=tile, Value=Ptr to corresponding Board */
std::map<int, Board*> Board::potentialMoves()
{
  map<int, Board*> moves; 
  int dim = static_cast<int>(sqrt(size_));
  Board* makeBoard; 
  
  ///utilize similar code as constructor to check if tiles exist adjecent to blank space. 
  ///if there are, then makes a copy of the current Board* and makes the move with selected tile
  ///adds the Board* post move to map 
  int n = blankLoc_ - dim;
  int e = blankLoc_ + 1;
  int s = blankLoc_ + dim;
  int w = blankLoc_ - 1; 
  
  ///above the blank 
  if(n >= 0) 
  {
    makeBoard = new Board(tiles_, size_); 
    makeBoard->move(tiles_[n]); 
    moves[tiles_[n]] = makeBoard; 
  }  
  
  ///right of the blank 
  if((e%dim) != 0)
  {
    makeBoard = new Board(tiles_, size_); 
    makeBoard->move(tiles_[e]); 
    moves[tiles_[e]] = makeBoard; 
  }
  
  ///below the blank 
  if(s<size_) 
  {
    makeBoard = new Board(tiles_, size_); 
    makeBoard->move(tiles_[s]); 
    moves[tiles_[s]] = makeBoard; 
  } 
  
  ///left of the blank 
  if((blankLoc_%dim) != 0) 
  {
    makeBoard = new Board(tiles_, size_); 
    makeBoard->move(tiles_[w]); 
    moves[tiles_[w]] = makeBoard; 
  }
  return moves;
}

 /** Returns true if the board is solved, false otherwise */
 ///goes through board and checks if each tile is in the right position
 ///if return false is never reached, it means that everything is in the right place so it returns true.
bool Board::solved()
{
  for(int i=0; i<size_; i++) 
  {
    if(i != (tiles_[i])) 
    {
      return false; 
    } 
  }
  return true;
}

///Overload operator << so that it prints out the board. 
///Added accomodations of space in case the tile numbers get too large.
ostream& operator<<(std::ostream &os, const Board &b)
{
  int dim = static_cast<int>(sqrt(b.getSize())); 
  int width; 
  if(b.getSize() < 10)
  {
    width = 2; 
  } 
  else if(b.getSize() < 100)  //accounts for two digit numbers, so more space is given to accomodate them 
  {
    width = 3; 
  } 
  else  //accounts for 3 digit numbers when the size is greater than 100
  {
    width = 4;
  } 
  for(int i=0; i<dim; i++)
  {
    for(int j=0; j<dim; j++)
    {
      if((b.getTiles())[dim*i + j] == 0)  ///makes it so that blank space just prints a space.
      {
        os << setw(width) << " "; 
      }
      else
      {
        os << setw(width) << (b.getTiles())[dim*i + j]; 
      } 
    } 
    os << endl; 
  } 
  return os;
} 

//added equal operator to help compare boards for future parts
Board& Board::operator=(const Board &rhs)
{
  size_ = rhs.getSize();
  blankLoc_ = rhs.getblankLoc();
  tiles_ = new int[size_];
  for (int i=0; i < size_; i++)
  {
    tiles_[i] = (rhs.tiles_)[i];
  }
  return *this;
}

///Goes through the tiles of each board and checks if they are the same. 
///If the Boards aren't the same size then it automatically returns false.
bool Board::operator==(const Board& rhs) const
{
  if(size_ != rhs.size_)
  {
    return false; 
  } 
  for(int i=0; i<size_; i++)
  {
    if(tiles_[i] != rhs.tiles_[i]) 
    {
      return false; 
    } 
  }
  return true; 
}

bool Board::operator<(const Board& rhs) const
{
  if(size_ < rhs.size_){
    return true;
  }
  bool val = false;
  for(int i=0; i < size_; i++){
    if(tiles_[i] < rhs.tiles_[i]){
       //val = true;
       //break;
       return true;
     }
     else if(tiles_[i] > rhs.tiles_[i]){
       //break;
       return false;
     }
  }
  return val;
}

///Almost the same as the == operator except the returns are backward
bool Board::operator!=(const Board& rhs) const
{
  if(size_ != rhs.size_)
  {
    return true; 
  } 
  for(int i=0; i<size_; i++)
  {
    if(tiles_[i] != rhs.tiles_[i]) 
    {
      return true; 
    } 
  }
  return false; 
}

int* Board::getTiles() const
{
  return tiles_;
}
int  Board::getSize() const
{
  return size_;
}
int  Board::getblankLoc() const
{
  return blankLoc_;
}
