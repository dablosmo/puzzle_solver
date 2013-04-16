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
    
    /** Retrieves the error list so other classes can access it and add messages to it */
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
    /** Allows the start game button to actually create a board and have it display in the middle of the mainwindow with all the
    user specified options */
    void Start();
    /** Allows users to find the solution to the puzzle when pressing the cheat button and selecting which heuristic to use */
    void Cheat();
    /** Quit game function that activates when the quit button is pressed */
    void Quit();
    /** Utilizes the puzzle solver and puzzle heuristic class to find the solutions to the current puzzle and prints it out to the solution List Widget */
    void manhattan(); 
    /** Same as manhattan() except it utilizes the out of place heuristic */
    void outofplace();
    /** Function that allows only one of the radio buttons to be active at one time */
    void handleToggle();
    /** Same as hantleToggle(). Each one makes it so that when one is toggled, the other is shut off*/
    void handleToggle1();
};

#endif // MainWindow_H
