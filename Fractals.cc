#include <QApplication>

#include "MainWindow.hh"

int main(int argc, char* argv[])
{
  QApplication application(argc, argv);
  application.setApplicationName("Fractals");
  application.setApplicationVersion("0.1");

  MainWindow mainWindow;
  mainWindow.show();

  return application.exec();
}
