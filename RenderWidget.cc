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

  _shaderProgram.addShaderFromSourceCode(QGLShader::Vertex,
                                         "attribute highp vec2 vertex;\n"
                                         "void main()\n"
                                         "{\n"
                                         "  gl_Position = vec4(vertex.xy, 0.0, 0.0);\n"
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
  int textureLocation = _shaderProgram.attributeLocation("texture");

  _shaderProgram.enableAttributeArray(vertexLocation);
  _shaderProgram.setAttributeArray(vertexLocation, quadVertices, 2);

  glDrawArrays(GL_QUADS, 0, 4);

  _shaderProgram.enableAttributeArray(textureLocation);
  _shaderProgram.setAttributeArray(textureLocation, textureCoordinates, 2);
}
