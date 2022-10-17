#include <QOpenGLWidget>
#include <osgViewer/Viewer>
#include <QEvent>
class QInputEvent;
class ModelViewer : public QOpenGLWidget, public osgViewer::Viewer
{
public:
	ModelViewer(QWidget* parent = 0);
	~ModelViewer();

	bool event(QEvent* event);

    void setKeyboardModifiers(QInputEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent* event);
    void moveEvent(QMoveEvent* event);
    void timerEvent(QTimerEvent*);

    osgViewer::Viewer* getOSGViewer() { return this; }
    osg::Group* getRoot() { return root; }
protected:
    virtual void paintGL();

private:
    void init3D();
    osg::ref_ptr<osg::Camera> createCamera(int x, int y, int w, int h);

private:
    osg::ref_ptr<osg::Group> root;
    osgViewer::GraphicsWindow* window;

};

