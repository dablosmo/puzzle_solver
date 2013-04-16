#ifndef GUITILE_H
#define GUITILE_H

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>


using namespace std;

class PuzzleWindow;

class GUITile : public QGraphicsRectItem
{   
  private:
    PuzzleWindow *parent;
    QGraphicsSimpleTextItem* tiletext;
    int tilenumber;
    int x;
    int y;
    int width;
    int height;
    int velocityX;
    int velocityY;
    bool moving;

  public:
    ///Default Constructor
    GUITile();
    ///Constructor that creates a tile with indications to its parent, coordinates, size, and velocity.
    GUITile(PuzzleWindow *cw, int tilenum, double nx, double ny, double w, double h, int vx, int vy );
    ///Destructor
    ~GUITile();
    ///Sets x coordinate of the tile
    void setX( int x );
    ///Sets y coordinate of the tile
    void setY( int y );
    ///Sets velocity of the tile in the x direction
    void setVelocityX( int vx );
    ///Sets velocity of the tile in the y direction
    void setVelocityY( int vy );
    ///Returns the tile
    int getTile() const;
    ///Returns the x coordinate of the tile
    int getX() const;
    ///Returns the x coordinate of the tile
    int getY() const;
    ///Returns the width of the tile
    int getWidth() const;
    ///Returns the length of the tile
    int getHeight() const;
    ///Gets velocity of the tile in the x direction
    int getVelocityX() const;
    ///Gets velocity of the tile in the y direction
    int getVelocityY() const;
    ///Returns puzzlewindow so its functions can be accessed
    PuzzleWindow* getParent() const;
    ///Actual text that is shown on the tile
    QGraphicsSimpleTextItem* getTiletext() const;
    ///Makes sure the text is moving with the tile
    void updateText();
    ///Returns whether the tile is moving or not
    bool getMoving();
    ///Set whether the tile is moving or not
    void setMoving(bool m);
    ///Allows the program to recognize that a tile has been clicked on
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    ///Copy Constructor
    GUITile& operator=(const GUITile& rhs);


};

#endif // GUITILE_H
