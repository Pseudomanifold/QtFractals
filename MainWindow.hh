#ifndef MainWindow_hh__
#define MainWindow_hh__

#include <QMainWindow>

class RenderWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    RenderWidget* _renderWidget;
};

#endif
