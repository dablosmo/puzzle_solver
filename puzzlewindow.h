#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton> 
#include <QMenuBar> 
#include <QLineEdit> 
#include <QRadioButton> 
#include <QListWidget>
#include <QTextEdit>

#include "board.h"
#include "GUITile.h"

#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 250

using namespace std;

class MainWindow;

class PuzzleWindow : public QGraphicsView {
    Q_OBJECT
    
public:
    ///Default Constructor 
    PuzzleWindow();
    ///Constructor
    explicit PuzzleWindow(int size, int scrambles, int seed);
    ///Destructor
    ~PuzzleWindow();
    ///Sets the parent of this class to mainwindow. Allows access to some of mainwindow's functions
    void setParent(MainWindow *mw);
    ///Function that allows the tile to move when its clicked on
    void moveTile(GUITile* tile);
    ///Used to animate the tile and slide to its correct location after it is clicked on
    void animateTile();
    ///Returns the current puzzle board
    Board* getBoard();

    
private:
    MainWindow *parent;
    QGraphicsScene *scene;
    Board *currentboard;
    GUITile **guiboard;
    QTimer *timer;
    double initx;
    double inity; 
    int xdist; 
    int ydist; 
    GUITile* currentTile; 


public slots:
    ///Handle timer is used to make sure that the tile stops in the right place
    void handleTimer();

};

#endif // PUZZLEWINDOW_H
