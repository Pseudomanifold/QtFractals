#include "RenderWidget.hh"

#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>

RenderWidget::RenderWidget(QWidget* parent)
  : QGLWidget(parent)
  , _iterations(512)
  , _centre(0.f, 0.f)
  , _scale(1.f)
{
  this->setFocusPolicy(Qt::StrongFocus);
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::initializeGL()
{
  this->initializeOpenGLFunctions();
  this->qglClearColor(Qt::black);

  glEnable(GL_DEPTH_TEST);

  _shaderProgram.addShaderFromSourceCode(QGLShader::Vertex,
                                         "attribute highp vec4 vertex;\n"
                                         "attribute highp vec2 texture_in;\n"
                                         "varying   highp vec2 texture_out;\n"
                                         "void main()\n"
                                         "{\n"
                                         "  gl_Position = vertex;\n"
                                         "  texture_out = texture_in;\n"
                                         "}\n");

  bool fragmentShaderAdded
    = _shaderProgram.addShaderFromSourceFile(QGLShader::Fragment,
                                             ":/Mandelbrot.glsl");

  if(!fragmentShaderAdded)
    qDebug() << _shaderProgram.log();

  _shaderProgram.link();
  _shaderProgram.bind();

  qDebug() << _shaderProgram.log();
}

void RenderWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _shaderProgram.setUniformValue("scale", _scale);
  _shaderProgram.setUniformValue("centre", _centre);
  _shaderProgram.setUniformValue("iterations", _iterations);

  const GLfloat quadVertices[] =
  {
    -1.f, -1.f,
    1.f, -1.f,
    1.f, 1.f,
    -1.f, 1.f
  };

  const GLfloat textureCoordinates[] =
  {
    0.f, 0.f,
    1.f, 0.f,
    1.f, 1.f,
    0.f, 1.f
  };

  int vertexLocation  = _shaderProgram.attributeLocation("vertex");
  int textureLocation = _shaderProgram.attributeLocation("texture_in");

  _shaderProgram.enableAttributeArray(vertexLocation);
  _shaderProgram.setAttributeArray(vertexLocation, quadVertices, 2);
  _shaderProgram.enableAttributeArray(textureLocation);
  _shaderProgram.setAttributeArray(textureLocation, textureCoordinates, 2);

  glDrawArrays(GL_QUADS, 0, 4);
}

void RenderWidget::mousePressEvent(QMouseEvent* event)
{
  double xrange[] = { ( -2.0 * _scale + _centre.x() ), ( 1.0 * _scale + _centre.x() ) };
  double yrange[] = { ( -1.0 * _scale + _centre.y() ), ( 1.0 * _scale +  _centre.y() ) };

  QPointF windowPosition   = event->windowPos();
  QPointF absolutePosition = QPointF(  ( xrange[1] - xrange[0] ) / this->width() * windowPosition.x()  + xrange[0],
                                      -( yrange[1] - yrange[0] ) / static_cast<float>(this->height()) * windowPosition.y() + yrange[1] );

  _centre = absolutePosition;

  this->update();
}

void RenderWidget::keyPressEvent(QKeyEvent* event)
{
  bool update = false;

  if(event->type() == QEvent::KeyPress)
  {
    if(event->key() == Qt::Key_Plus)
    {
      _scale *= 0.9f;
      update  = true;
    }
    else if(event->key() == Qt::Key_Minus)
    {
      _scale *= 1.1f;
      update = true;
    }
  }

  if(update)
    this->update();
}
