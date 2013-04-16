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
}

GUITile::GUITile(PuzzleWindow *cw, int tilenum, double nx, double ny, double w, double h, int vx, int vy ) :
    QGraphicsRectItem(nx, ny, w, h) {
    parent = cw;
    tilenumber = tilenum;
    moving = false;
    x = nx;
    y = ny;
    width = w;
    height = h;
    velocityX = vx;
    velocityY = vy;
    ostringstream oss;
    oss << tilenum;
    string temp = oss.str();
    char* tempchar = new char[temp.size() + 1];
    tempchar[temp.size()] = 0;
    memcpy(tempchar, temp.c_str(), temp.size());
    QString str = tempchar;
    tiletext = new QGraphicsSimpleTextItem(str, this);
    tiletext->setPos(x + width/3, y + height/4);
    tiletext->setZValue(1);
    
    tiletext->setParentItem( this );
    QBrush whiteBrush(Qt::white);
    this->setBrush( whiteBrush );
}

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

/*void GUITile::move( int windowMaxX, int windowMaxY ) {
    //We move by adding the velocity to the current position.
    //Then we test whether we have reached the edge of our moving space
    //If so, we reverse the velocity (y-velocity when we hit the top/bottom and
    //x-velocity when we hit the left/right sides) and undo the position change
    //that moved part of the rectangle off the screen.
    x += velocityX;
    y += velocityY;

    if ( x < 0 ) {
        velocityX = -velocityX;
        x +=velocityX;
    }

    if ( y < 0 ) {
        velocityY = -velocityY;
        y +=velocityY;
    }

    if ( (x+width) > windowMaxX ) {
         velocityX = -velocityX;
         x+=velocityX;
    }

    if ( (y+height) > windowMaxY ) {
         velocityY = -velocityY;
         y+=velocityY;
    }

    //Everything is good. Update the QRectF that is actually displayed.
    QPointF p( x, y );
    QRectF r( rect() );
    r.moveTo(p);
    setRect( r );

} */


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

void GUITile::updateText()
{
    tiletext->update(x, (y+(height/2)), width, height/2);
}

QGraphicsSimpleTextItem* GUITile::getTiletext() const
{
    return tiletext;
}




