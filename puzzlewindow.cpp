#include <QtGui/QPushButton>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsSimpleTextItem>
#include "puzzlewindow.h"
#include "GUITile.h"
#include "mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include <iostream>

const int UPPER_LEFT_X = 0;
const int UPPER_LEFT_Y = 0;
const int TILE_WIDTH = 30;
const int TILE_HEIGHT = 30;
const int X_SPACE = 4;
const int Y_SPACE = 4;

///Default constructor
PuzzleWindow::PuzzleWindow() { 
    scene = new QGraphicsScene();
    currentboard = new Board();
    guiboard = new GUITile*[1];
    timer = new QTimer();
}

///Constructor that creates the puzzle board
PuzzleWindow::PuzzleWindow(int size, int scrambles, int seed)  {
    scene = new QGraphicsScene();
    setScene( scene );
    ///Gives passes arguments so that a board is created with user specified game options modified by the user inputs
    currentboard = new Board(size, scrambles, seed); 
    ///Gives constant to work with depending on the size of the board.
    int dim = static_cast<int>(sqrt(currentboard->getSize()));
    guiboard = new GUITile*[currentboard->getSize()];
    ///Creates a board of tiles
    for(int i=0; i < currentboard->getSize(); i++)
    {
      if( (currentboard->getTiles())[i] != 0)
      { 
        ///Makes sure all the tiles spawn in the correct coordinates and are of the right size and velocity
        guiboard[i] = new GUITile( this, (currentboard->getTiles())[i], ( (i%dim)*(TILE_WIDTH + X_SPACE) + UPPER_LEFT_X ),
          ( (i/dim)*(TILE_HEIGHT + Y_SPACE) + UPPER_LEFT_Y ), TILE_WIDTH, TILE_HEIGHT, (TILE_WIDTH + X_SPACE) , (TILE_HEIGHT + Y_SPACE) );
        scene->addItem( guiboard[i] );
      }
    }
    ///Sets size and name of the central window
    this->setFixedSize( WINDOW_MAX_X, WINDOW_MAX_Y );
    this->setWindowTitle( "GUITiles" );
    ///Starts timer for the tile animation function to work
    timer = new QTimer(); 
    timer->setInterval(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
}

///Destructor
PuzzleWindow::~PuzzleWindow()
{
    delete scene;
    delete currentboard;
    delete guiboard;
    delete timer;
}

///Sets parent
void PuzzleWindow::setParent(MainWindow *mw)
{
    parent = mw;
}

///Move tile function that allows user to click on a tile and have it slide over to its correct position
void PuzzleWindow::moveTile(GUITile *tile)
{
    int dim = static_cast<int>(sqrt(currentboard->getSize()));
    int blankLoc = currentboard->getblankLoc();
    int tileLoc;
    int initrow;
    int initcol;
    int finalrow;
    int finalcol;

    try
    {
       currentboard->move( tile->getTile() );
       
       // Check what column the tile is in
       // Check what row the tile is in
       tileLoc = currentboard->getblankLoc(); 
       currentTile = tile; 
       
       initx = currentTile->getX();
       inity = currentTile->getY();
       
       initrow = tileLoc/dim; 
       finalrow = blankLoc/dim;
       
       initcol = tileLoc % dim; 
       finalcol = blankLoc % dim;
       
       ///Find X and Y distance that the tile has to move
       xdist = finalcol - initcol;
       ydist = finalrow - initrow; 
       
       ///Starts timer for animation function to work.
       timer->start();
       
       if(currentboard->solved() == true) 
       { 
         parent->getErrorList()->setPlainText("You solved the puzzle!"); 
       }
       
    }
    ///Exception handling for clicking on tiles that are not supposed to be able to move.
    catch (exception &e)
    {
      parent->getErrorList()->setPlainText( "Tile is not adjacent to blank space. Click a valid tile to move.");
    }
}

///Timer makes sure that the tile moves the right amount of distance
void PuzzleWindow::handleTimer() 
{ 
    ///If the tile has moved the specified distance, the timer is stopped and the tile is no longer moving
    if ( (initx + (xdist)*(TILE_WIDTH + X_SPACE) == currentTile->getX()) && (inity + (ydist)*(TILE_HEIGHT + Y_SPACE) == currentTile->getY()) )
    {
      timer->stop(); 
      currentTile->setMoving(false); 
    } 
    ///Otherwise keep moving
    else
    {
      animateTile();
    }
} 

///Actual function that animates the tile frame by frame
void PuzzleWindow::animateTile() 
{
  ///Variable that indicates that the tile is moving
  currentTile->setMoving(true); 
  ///Find current x and y coordinates of the tile
  double currX = currentTile->getX(); 
  double currY = currentTile->getY(); 
  ///Set the x and y coordinates of the tile to the place that it should be after one move
  currentTile->setX( currX + xdist ); 
  currentTile->setY( currY + ydist ); 
  ///Update the tile so that it actually moves there
  QPointF p( UPPER_LEFT_X + currentTile->getX(), UPPER_LEFT_Y + currentTile->getY() ); 
  QRectF r(currentTile->rect() ); 
  r.moveTo(p); 
  currentTile->setRect(r); 
  ///Text also is moved the same amount
  QPointF p2( UPPER_LEFT_X + currentTile->getX() + TILE_WIDTH/3, UPPER_LEFT_Y + currentTile->getY() + TILE_HEIGHT/4);
  currentTile->getTiletext()->setPos( p2 );
} 

///Returns the current puzzleboard
Board* PuzzleWindow::getBoard() { 
  return currentboard;
}

