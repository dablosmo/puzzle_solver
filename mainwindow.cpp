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
#include <QRadioButton>
#include <QPushButton>
#include <QListWidget>
#include <QGraphicsView>

using namespace std; 

MainWindow::MainWindow() { 

  setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  
  //Menu Bar at top
  
  file = menuBar()->addMenu(tr("&Game"));
  
  //Start game option
  
  startGame = new QAction ("Start Game", this); 
  file->addAction(startGame); 
  connect(startGame, SIGNAL(triggered()), this, SLOT(Start()));
  
  //Cheat Option
  
  cheat = new QAction ("Cheat", this); 
  file->addAction(cheat); 
  connect(cheat, SIGNAL(triggered()), this, SLOT(Cheat()));
  
  //Quit Option
  
  quit = new QAction("Quit", this); 
  file->addAction(quit); 
  connect(quit, SIGNAL(triggered()), this, SLOT(Quit())); 
  
  //Left widget, game options 
  
  sizeBox = new QLineEdit();
  moveBox = new QLineEdit();
  seedBox = new QLineEdit(); 
  
  //Place to enter size of puzzle
  
  QDockWidget* docksizeBox = new QDockWidget("Puzzle Size", this);
  docksizeBox->setAllowedAreas(Qt::LeftDockWidgetArea);
  docksizeBox->setWidget(sizeBox);
  addDockWidget(Qt::LeftDockWidgetArea, docksizeBox);
  docksizeBox->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  //Enter the number of scrambles 
  
  QDockWidget* dockmoveBox = new QDockWidget("Scrambles", this);
  dockmoveBox->setAllowedAreas(Qt::LeftDockWidgetArea);
  dockmoveBox->setWidget(moveBox);
  addDockWidget(Qt::LeftDockWidgetArea, dockmoveBox);
  dockmoveBox->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  //Enter seed 
  
  QDockWidget* dockseedBox = new QDockWidget("Seed", this);
  dockseedBox->setAllowedAreas(Qt::LeftDockWidgetArea);
  dockseedBox->setWidget(seedBox);
  addDockWidget(Qt::LeftDockWidgetArea, dockseedBox);
  dockseedBox->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  //Right Widget, Radio Buttons, Choose heuristic
  
  manbutton = new QRadioButton();
  oopbutton = new QRadioButton();
  
  QDockWidget* man = new QDockWidget("Manhattan", this);
  man->setAllowedAreas(Qt::RightDockWidgetArea);
  man->setWidget(manbutton);
  addDockWidget(Qt::RightDockWidgetArea, man);
  man->setFeatures(QDockWidget::NoDockWidgetFeatures);
 
  QDockWidget* oop = new QDockWidget("Out Of Place", this);
  oop->setAllowedAreas(Qt::RightDockWidgetArea);
  oop->setWidget(oopbutton);
  addDockWidget(Qt::RightDockWidgetArea, oop);
  oop->setFeatures(QDockWidget::NoDockWidgetFeatures); 
  
  //Solution list at bottom
  
  solutionList = new QListWidget();
 
  QDockWidget* solutions = new QDockWidget("Solutions", this);
  solutions->setAllowedAreas(Qt::BottomDockWidgetArea);
  solutions->setWidget(solutionList);
  addDockWidget(Qt::BottomDockWidgetArea, solutions);
  solutions->setFeatures(QDockWidget::NoDockWidgetFeatures);
  
  //Puzzle, central widget
  
  pw = new PuzzleWindow;
  setCentralWidget(pw);
}

MainWindow::~MainWindow() { 
  
}

Board* MainWindow::getBoard() { 

}

void MainWindow::Start(){
  cout << "Start Game!" << endl;
}

void MainWindow::Cheat(){
  cout << "Cheat!" <<endl; 
}

void MainWindow::Quit(){ 
  exit(EXIT_FAILURE);
}



