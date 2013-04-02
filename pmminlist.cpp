#include "puzzle_move.h"
#include "pmminlist.h"
using namespace std;

/**
 * Default Constructor
 */
PMMinList::PMMinList() : slist_()
{

}

/**
 * Destructor
 */
PMMinList::~PMMinList()
{

}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest (if 
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::push(PuzzleMove* pm)
{
  list<PuzzleMove*>::iterator it = slist_.begin();
 
  //---- Add your implementation to iterate through the list
  //---- to find the correct location to insert pm and then
  //---- use the insert() method of std::List to insert it
  //---- See http://www.cplusplus.com/reference/list/list/insert/

  if(empty())
  { 
    slist_.insert(slist_.begin(), pm); 
  }
  ///if slist is already populated
  else
  { 
    ///go through the list until an element with a higher f store is located and put pm before that element 
    for (it = slist_.begin(); it != slist_.end(); ++it)
    {
      if (*(pm) < **(it))
      {
        slist_.insert(it, pm);
        return;
      }
    }
    slist_.insert(slist_.end(), pm);
    }
}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::pop()
{
  slist_.pop_front();
}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest
 * @param val Value to add to the sorted PuzzleMove list
 * @return reference to the minimum-scored PuzzleMove*
 */
PuzzleMove* PMMinList::top()
{
  return slist_.front();
}

