#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include "mainwindow.h"
#include "puzzlewindow.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <QtGui>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QListWidget>
#include <QGraphicsView>
#include "puzzle_heur.h" 
#include "puzzle_solver.h"
#include "pmminlist.h"

using namespace std; 

MainWindow::MainWindow() { 

  setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  
 
///Left widget, game options and buttons
  
  sizeBox = new QLineEdit(); 
  moveBox = new QLineEdit(); 
  seedBox = new QLineEdit(); 
  
  ///Place to enter size of puzzle
  
  QDockWidget* docksizeBox = new QDockWidget("Puzzle Size", this);
  docksizeBox->setAllowedAreas(Qt::LeftDockWidgetArea);
  docksizeBox->setWidget(sizeBox);
  addDockWidget(Qt::LeftDockWidgetArea, docksizeBox);
  docksizeBox->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  ///Enter the number of scrambles 
  
  QDockWidget* dockmoveBox = new QDockWidget("Scrambles", this);
  dockmoveBox->setAllowedAreas(Qt::LeftDockWidgetArea);
  dockmoveBox->setWidget(moveBox);
  addDockWidget(Qt::LeftDockWidgetArea, dockmoveBox);
  dockmoveBox->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  ///Enter seed 
  
  QDockWidget* dockseedBox = new QDockWidget("Seed", this);
  dockseedBox->setAllowedAreas(Qt::LeftDockWidgetArea);
  dockseedBox->setWidget(seedBox);
  addDockWidget(Qt::LeftDockWidgetArea, dockseedBox);
  dockseedBox->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  ///Start game option
  
  startGame = new QPushButton ("Start Game");  
  
  QDockWidget* start = new QDockWidget( this);
  start->setAllowedAreas(Qt::LeftDockWidgetArea);
  start->setWidget(startGame);
  addDockWidget(Qt::LeftDockWidgetArea, start);
  start->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  connect(startGame, SIGNAL(clicked()), this, SLOT(Start()));
  
  ///Cheat Option
  
  cheatButton = new QPushButton ("Cheat"); 
  
  QDockWidget* cheat = new QDockWidget( this);
  cheat->setAllowedAreas(Qt::LeftDockWidgetArea);
  cheat->setWidget(cheatButton);
  addDockWidget(Qt::LeftDockWidgetArea, cheat);
  cheat->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  connect(cheatButton, SIGNAL(clicked()), this, SLOT(Cheat()));
  
  ///Quit Option
  
  quitButton = new QPushButton("Quit"); 
  
  QDockWidget* quit = new QDockWidget( this);
  quit->setAllowedAreas(Qt::LeftDockWidgetArea);
  quit->setWidget(quitButton);
  addDockWidget(Qt::LeftDockWidgetArea, quit);
  quit->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  connect(quitButton, SIGNAL(clicked()), this, SLOT(Quit())); 
  
///Right Widget, Radio Buttons, Choose heuristic
  
  manbutton = new QRadioButton();
  
  QDockWidget* man = new QDockWidget("Manhattan", this);
  man->setAllowedAreas(Qt::RightDockWidgetArea);
  man->setWidget(manbutton);
  addDockWidget(Qt::RightDockWidgetArea, man);
  man->setFeatures(QDockWidget::NoDockWidgetFeatures);
  connect(manbutton, SIGNAL(toggled(bool)), this, SLOT(handleToggle()));
  
  oopbutton = new QRadioButton();
 
  QDockWidget* oop = new QDockWidget("Out Of Place", this);
  oop->setAllowedAreas(Qt::RightDockWidgetArea);
  oop->setWidget(oopbutton);
  addDockWidget(Qt::RightDockWidgetArea, oop);
  oop->setFeatures(QDockWidget::NoDockWidgetFeatures); 
  connect(oopbutton, SIGNAL(toggled(bool)), this, SLOT(handleToggle1()));
  
  ///Messages 
  
  errorList = new QTextEdit();
 
  QDockWidget* errors = new QDockWidget("Game Message", this);
  errors->setAllowedAreas(Qt::RightDockWidgetArea);
  errors->setWidget(errorList);
  addDockWidget(Qt::RightDockWidgetArea, errors);
  errors->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
///Solution list at bottom of main window
  
  solutionList = new QListWidget();
 
  QDockWidget* solutions = new QDockWidget("Solutions", this);
  solutions->setAllowedAreas(Qt::BottomDockWidgetArea);
  solutions->setWidget(solutionList);
  addDockWidget(Qt::BottomDockWidgetArea, solutions);
  solutions->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  ///Puzzleboard in central widget, blank at start
  
  QWidget* BlankWidget = new QWidget(); 
  BlankWidget->setFixedSize(300,220);
  setCentralWidget(BlankWidget);
  
  //initialize
  startgame = false;
}

MainWindow::~MainWindow() { 
  
}

QTextEdit* MainWindow::getErrorList() {
  return errorList; 
  errorList->clear();
}

void MainWindow::Start(){
  startgame = true;
  QString size = sizeBox->text();
  QString move = moveBox->text(); 
  QString seed = seedBox->text(); 
  string ssize = size.toUtf8().constData(); 
  string smove = move.toUtf8().constData(); 
  string sseed = seed.toUtf8().constData();
  puzzleSize = atoi(ssize.c_str()); 
  numScrambles = atoi(smove.c_str()); 
  Seed = atoi(sseed.c_str());
  
  if( (puzzleSize == 9 || puzzleSize == 16) && numScrambles > 0 && Seed != 0)  
  {
    pw = new PuzzleWindow(puzzleSize, numScrambles, Seed); 
    pw->setParent(this);
    setCentralWidget(pw);
  } 
  else if(!(puzzleSize == 9 || puzzleSize == 16))
  {
    errorList->clear();
    errorList->setPlainText("Please select either 9 or 16 as the size of the puzzle"); 
  } 
  else if(!(numScrambles > 0))
  {
    errorList->clear(); 
    errorList->setPlainText("Please enter a number above 0 for the number of scrambles"); 
  } 
  else if(Seed == 0)
  {
    errorList->clear(); 
    errorList->setPlainText("Please enter a number for Seed"); 
  }
  else  
  {
    errorList->clear(); 
    errorList->setPlainText("One or more of your puzzle inputs are invalid"); 
  }
}

void MainWindow::Cheat(){
  if(manbutton->isChecked() && (!(oopbutton->isChecked()))) 
  {
    manhattan(); 
  } 
  else if(oopbutton->isChecked() && (!(manbutton->isChecked())))
  {
    outofplace();
  } 
  else if(oopbutton->isChecked() && manbutton->isChecked()) //should never get here
  {
    errorList->clear(); 
    errorList->setPlainText("Please select only one of the puzzle heuristics.");
  }
  else if(startgame == false)
  {
    errorList->clear(); 
    errorList->setPlainText("Please start the game first");
  }
  else if((!(manbutton->isChecked())) && (!(oopbutton->isChecked()))) 
  {
    errorList->clear(); 
    errorList->setPlainText("Please select one of the puzzle heuristics first.");
  }
  else  //shouldn't get here
  {
    errorList->clear(); 
    errorList->setPlainText("One or more invalid inputs.");
  }
}

void MainWindow::Quit(){ 
  exit(EXIT_FAILURE);
}




