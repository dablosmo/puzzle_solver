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

  public:
    GUITile();
    GUITile(PuzzleWindow *cw, int tilenum, double nx, double ny, double w, double h, int vx, int vy );
    ~GUITile();
    void setX( int x );
    void setY( int y );
    void setVelocityX( int vx );
    void setVelocityY( int vy );
    int getTile() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    int getVelocityX() const;
    int getVelocityY() const;
    PuzzleWindow* getParent() const;
    QGraphicsSimpleTextItem* getTiletext() const;
    void updateText();
    
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void move(int windowMaxX, int windowMaxY );

    GUITile& operator=(const GUITile& rhs);


};

#endif // GUITILE_H
