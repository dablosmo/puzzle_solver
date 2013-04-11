#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <vector>
#include <QMenuBar>
#include <QLineEdit>
#include <QRadioButton>
#include <QListWidget>

#include "puzzlewindow.h"
#include "board.h"

class MainWindow : public QMainWindow  {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
    
    Board* getBoard();
    
private: 
    PuzzleWindow* pw;  
    QMenu* file; 
    QAction* quit;
    QAction* startGame; 
    QAction* cheat;
    QLineEdit* sizeBox;
    QLineEdit* moveBox;
    QLineEdit* seedBox;
    QListWidget* solutionList;
    QRadioButton* manbutton;
    QRadioButton* oopbutton;
    

public slots: 
    void Start();
    void Cheat();
    void Quit();
};

#endif // MainWindow_H
