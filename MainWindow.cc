#include "MainWindow.hh"
#include "RenderWidget.hh"

#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , _renderWidget(new RenderWidget(this))

{
  QMenuBar* menuBar  = this->menuBar();
  QMenu* fractalMenu = menuBar->addMenu("Fractals");
  fractalMenu->addAction("Julia fractal",      _renderWidget, SLOT(loadJuliaFractal()));
  fractalMenu->addAction("Mandelbrot fractal", _renderWidget, SLOT(loadMandelbrotFractal()));
  fractalMenu->addSeparator();
  fractalMenu->addAction("Quit", this, SLOT(close()));

  this->setCentralWidget(_renderWidget);
}

MainWindow::~MainWindow()
{
}
