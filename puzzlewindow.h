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

#define WINDOW_MAX_X 150
#define WINDOW_MAX_Y 150

using namespace std;

class MainWindow;

class PuzzleWindow : public QGraphicsView {
    Q_OBJECT
    
public:
    explicit PuzzleWindow(int size, int scrambles, int seed);
    ~PuzzleWindow();
    void setParent(MainWindow *mw);
    void moveTile(GUITile* tile);
    void animateTile();
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
    
    //QGraphicsView *view;
    //QTimer *secondtimer;
    //BouncingRectangle *item;
    //QPushButton *button;
    //vector<BouncingRectangle*> list;

public slots:
    void handleTimer();

};

#endif // PUZZLEWINDOW_H
