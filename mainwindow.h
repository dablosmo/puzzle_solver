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
#include <QTextEdit>
#include <string>

#include "puzzlewindow.h"
#include "board.h"

class MainWindow : public QMainWindow  {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
    
    QTextEdit* getErrorList();
    
private: 
    PuzzleWindow* pw;  
    QMenu* file; 
    
    QPushButton* quitButton;
    QPushButton* startGame; 
    QPushButton* cheatButton;
    
    QLineEdit* sizeBox;
    QLineEdit* moveBox;
    QLineEdit* seedBox;
    
    QListWidget* solutionList;
    QTextEdit* errorList;
    
    QRadioButton* manbutton;
    QRadioButton* oopbutton;
    
    int puzzleSize; 
    int numScrambles; 
    int Seed;
    bool startgame;
    

public slots: 
    void Start();
    void Cheat();
    void Quit();
    void manhattan(); 
    void outofplace();
    void handleToggle();
    void handleToggle1();
};

#endif // MainWindow_H
