#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QGraphicsSimpleTextItem>
#include <QString>
#include "GUITile.h"
#include "puzzlewindow.h"
#include <sstream>
#include <iostream>

using namespace std;

GUITile::GUITile()
{
  tiletext = new QGraphicsSimpleTextItem();
}

///Constructor that creates a tile with indications to its parent, coordinates, size, and velocity.
GUITile::GUITile(PuzzleWindow *cw, int tilenum, double nx, double ny, double w, double h, int vx, int vy ) :
    ///Indicates position and size of the tile
    QGraphicsRectItem(nx, ny, w, h) {
    ///sets the parent to be the puzzle window
    parent = cw;
    ///initializes private variables
    tilenumber = tilenum;
    moving = false;
    x = nx;
    y = ny;
    width = w;
    height = h;
    velocityX = vx;
    velocityY = vy;
    ///string stream needed to change int into a qstring
    ostringstream oss;
    oss << tilenum;
    string temp = oss.str();
    char* tempchar = new char[temp.size() + 1];
    tempchar[temp.size()] = 0;
    memcpy(tempchar, temp.c_str(), temp.size());
    QString str = tempchar;
    ///Adds text to the tile
    tiletext = new QGraphicsSimpleTextItem(str, this);
    ///Sets position
    tiletext->setPos(x + width/3, y + height/4);
    ///Makes sure text is visible
    tiletext->setZValue(1);
    
    ///set parent
    tiletext->setParentItem( this );
    ///Color of tile is white
    QBrush whiteBrush(Qt::white);
    this->setBrush( whiteBrush );
}

///Destructor
GUITile::~GUITile()
{
    delete tiletext;
}

int GUITile::getVelocityX() const {
    return velocityX;
}

int GUITile::getVelocityY() const {
    return velocityY;
}

int GUITile::getTile() const {
    return tilenumber;
}

void GUITile::setVelocityX( int vx ) {
    velocityX = vx;
}

void GUITile::setVelocityY( int vy ) {
    velocityY = vy;
}

int GUITile::getX() const {
    return x;
}

int GUITile::getY() const {
    return y;
}

int GUITile::getWidth() const {
    return width;
}

int GUITile::getHeight() const {
    return height;
}

PuzzleWindow* GUITile::getParent() const {
    return parent;
}

void GUITile::setX(int nx) {
    x = nx;
}

void GUITile::setY(int ny) {
    y = ny;
}

bool GUITile::getMoving() {
    return moving;
}

void GUITile::setMoving(bool m) {
    moving = m;
}

void GUITile::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    if (!moving) {
      parent->moveTile( this );
    }
}  

///Copy Constructor
GUITile& GUITile::operator=(const GUITile& rhs)
{
    parent = rhs.getParent();
    tilenumber = rhs.getTile();
    moving = false;
    x = rhs.getX();
    y = rhs.getY();
    width = rhs.getWidth();
    height = rhs.getHeight();
    velocityX = rhs.getVelocityX();
    velocityY = rhs.getVelocityY();
    ostringstream oss;
    oss << tilenumber;
    string temp = oss.str();
    char* tempchar = new char[temp.size() + 1];
    tempchar[temp.size()] = 0;
    memcpy(tempchar, temp.c_str(), temp.size());
    QString str = tempchar;
    tiletext = new QGraphicsSimpleTextItem(str, this);
    

    tiletext->setZValue(1);
    QBrush whiteBrush(Qt::white);
    this->setBrush( whiteBrush );
    return *this;
}

///Makes sure the tile moves with the tile
void GUITile::updateText()
{
    tiletext->update(x, (y+(height/2)), width, height/2);
}

QGraphicsSimpleTextItem* GUITile::getTiletext() const
{
    return tiletext;
}




