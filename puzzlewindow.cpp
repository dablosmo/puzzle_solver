#include <QtGui/QPushButton>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsSimpleTextItem>
#include "puzzlewindow.h"
#include "GUITile.h"
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

PuzzleWindow::PuzzleWindow()  {
    scene = new QGraphicsScene();
    setScene( scene );
    currentboard = new Board(9, 0, 50);
    int dim = static_cast<int>(sqrt(currentboard->getSize()));
    guiboard = new GUITile*[currentboard->getSize()];
    for(int i=0; i < currentboard->getSize(); i++)
    {
      if( (currentboard->getTiles())[i] != 0)
      {
        guiboard[i] = new GUITile( this, (currentboard->getTiles())[i], ( (i%dim)*(TILE_WIDTH + X_SPACE) + UPPER_LEFT_X ),
          ( (i/dim)*(TILE_HEIGHT + Y_SPACE) + UPPER_LEFT_Y ), TILE_WIDTH, TILE_HEIGHT, (TILE_WIDTH + X_SPACE), (TILE_HEIGHT + Y_SPACE) );
        scene->addItem( guiboard[i] );
      }
    }
    this->setFixedSize( WINDOW_MAX_X*2, WINDOW_MAX_Y*2 );
    this->setWindowTitle( "GUITiles" );
}



void PuzzleWindow::setParent(MainWindow *mw)
{
    parent = mw;
}

void PuzzleWindow::moveTile(GUITile *tile)
{
    int dim = static_cast<int>(sqrt(currentboard->getSize()));
    int blankLoc = currentboard->getblankLoc();
    int row;
    int column;
    try
    {
       currentboard->move( tile->getTile() );
       // check the modulus of blankLoc with the dim to get the column tile is in
       // & check the integer division of blankLoc with dim to get the row tile is in
       row = blankLoc/dim;
       column = blankLoc % dim;
       
       
       // update the QRectF that is actually displayed
       QPointF p( column*(TILE_WIDTH + X_SPACE) + UPPER_LEFT_X , row*(TILE_HEIGHT + Y_SPACE) + UPPER_LEFT_Y );
       QRectF r( tile->rect() );
       r.moveTo(p);
       tile->setRect( r );
       QPointF p2( column*(TILE_WIDTH + X_SPACE) + UPPER_LEFT_X , row*(TILE_HEIGHT + Y_SPACE) + UPPER_LEFT_Y + (TILE_HEIGHT/2) );
       QRectF r2( tile->getTiletext()->mapRectToParent( tile->rect() ) );
       r2.moveTo(p);
       tile->getTiletext()->update( r2 );
       // tile->updateText();
       
    }
    catch (exception &e)
    {
      // placeholder for display message in error text box
      cerr << "Tile is not adjacent to blank space! Please try again." << endl;
      cout << endl;
    }
}


PuzzleWindow::~PuzzleWindow()
{

}

