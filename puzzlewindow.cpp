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

PuzzleWindow::PuzzleWindow(int size, int scrambles, int seed)  {
    scene = new QGraphicsScene();
    setScene( scene );
    currentboard = new Board(size, scrambles, seed);
    int dim = static_cast<int>(sqrt(currentboard->getSize()));
    guiboard = new GUITile*[currentboard->getSize()];
    for(int i=0; i < currentboard->getSize(); i++)
    {
      if( (currentboard->getTiles())[i] != 0)
      {
        guiboard[i] = new GUITile( this, (currentboard->getTiles())[i], ( (i%dim)*(TILE_WIDTH + X_SPACE) + UPPER_LEFT_X ),
          ( (i/dim)*(TILE_HEIGHT + Y_SPACE) + UPPER_LEFT_Y ), TILE_WIDTH, TILE_HEIGHT, (TILE_WIDTH + X_SPACE) , (TILE_HEIGHT + Y_SPACE) );
        scene->addItem( guiboard[i] );
      }
    }
    this->setFixedSize( WINDOW_MAX_X*2, WINDOW_MAX_Y*2 );
    this->setWindowTitle( "GUITiles" );
    timer = new QTimer(); 
    timer->setInterval(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
}

PuzzleWindow::~PuzzleWindow()
{

}

void PuzzleWindow::setParent(MainWindow *mw)
{
    parent = mw;
}

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
       // check the modulus of blankLoc with the dim to get the column tile is in
       // & check the integer division of blankLoc with dim to get the row tile is in
       
       // update the QRectF that is actually displayed  
       tileLoc = currentboard->getblankLoc(); 
       currentTile = tile; 
       
       initx = currentTile->getX();
       inity = currentTile->getY();
       
       initrow = tileLoc/dim; 
       finalrow = blankLoc/dim;
       
       initcol = tileLoc % dim; 
       finalcol = blankLoc % dim;
       
       xdist = finalcol - initcol;
       ydist = finalrow - initrow; 
       
       timer->start();
       
          
       /*QPointF p( column*(TILE_WIDTH + X_SPACE) + UPPER_LEFT_X , row*(TILE_HEIGHT + Y_SPACE) + UPPER_LEFT_Y );
       QRectF r( tile->rect() );
       r.moveTo(p);
       tile->setRect( r );
       QPointF p2( column*(TILE_WIDTH + X_SPACE) + UPPER_LEFT_X + TILE_WIDTH/3 , row*(TILE_HEIGHT + Y_SPACE) + UPPER_LEFT_Y + (TILE_HEIGHT/4) );
       tile->getTiletext()->setPos( p2 ); */
       if(currentboard->solved() == true) 
       { 
         parent->getErrorList()->setPlainText("You solved the puzzle!"); 
       }
       
    }
    catch (exception &e)
    {
      parent->getErrorList()->setPlainText( "Tile is not adjacent to blank space. Click a valid tile to move.");
    }
}

void PuzzleWindow::handleTimer() 
{ 
    if ( (initx + (xdist)*(TILE_WIDTH + X_SPACE) == currentTile->getX()) && (inity + (ydist)*(TILE_HEIGHT + Y_SPACE) == currentTile->getY()) )
    {
      timer->stop(); 
      currentTile->setMoving(false); 
    } 
    else
    {
      animateTile();
    }
} 

void PuzzleWindow::animateTile() 
{
  currentTile->setMoving(true); 
  double currX = currentTile->getX(); 
  double currY = currentTile->getY(); 
  currentTile->setX( currX + xdist ); 
  currentTile->setY( currY + ydist ); 
  QPointF p( UPPER_LEFT_X + currentTile->getX(), UPPER_LEFT_Y + currentTile->getY() ); 
  QRectF r(currentTile->rect() ); 
  r.moveTo(p); 
  currentTile->setRect(r); 
  
  QPointF p2( UPPER_LEFT_X + currentTile->getX() + TILE_WIDTH/3, UPPER_LEFT_Y + currentTile->getY() + TILE_HEIGHT/4);
  currentTile->getTiletext()->setPos( p2 );
} 

Board* PuzzleWindow::getBoard() { 
  return currentboard;
}

