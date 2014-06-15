#include "RenderWidget.hh"

#include <QDebug>

RenderWidget::RenderWidget(QWidget* parent)
  : QGLWidget(parent)
{
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::initializeGL()
{
  this->initializeOpenGLFunctions();
  this->qglClearColor(Qt::black);

  glEnable(GL_DEPTH_TEST);

  bool fragmentShaderAdded
    = _shaderProgram.addShaderFromSourceFile(QGLShader::Fragment,
                                             ":/Mandelbrot.glsl");

  if(!fragmentShaderAdded)
    qDebug() << _shaderProgram.log();
}

void RenderWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
