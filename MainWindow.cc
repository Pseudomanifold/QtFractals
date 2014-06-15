#include "MainWindow.hh"
#include "RenderWidget.hh"

#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  QMenuBar* menuBar  = this->menuBar();
  QMenu* fractalMenu = menuBar->addMenu("Fractals");
  fractalMenu->addAction("Quit", this, SLOT(close()));

  _renderWidget = new RenderWidget(this);
  this->setCentralWidget(_renderWidget);
}

MainWindow::~MainWindow()
{
}
