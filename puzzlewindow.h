#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QGraphicsItemAnimation>

#include "board.h"
#include "GUITile.h"

#define WINDOW_MAX_X 150
#define WINDOW_MAX_Y 150

using namespace std;

class MainWindow;

class PuzzleWindow : public QGraphicsView {
    Q_OBJECT
    
public:
    explicit PuzzleWindow();
    ~PuzzleWindow();
    void setParent(MainWindow *mw);
    void moveTile(GUITile* tile);

    
private:
    MainWindow *parent;
    QGraphicsScene *scene;
    Board *currentboard;
    GUITile **guiboard;
    //QGraphicsView *view;
    //QTimer *timer;
    //QTimer *secondtimer;
    //BouncingRectangle *item;
    //QPushButton *button;
    //vector<BouncingRectangle*> list;

public slots:
    //void handleTimer();
    //void buttonControl();
    //void spawnRectangle();

};

#endif // PUZZLEWINDOW_H
