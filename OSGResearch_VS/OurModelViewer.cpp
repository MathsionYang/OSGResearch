#include "OurModelViewer.h"
#include <QInputEvent>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <QApplication>
#include <osg/TexGen>
#include <osgUtil/Optimizer>
ModelViewer::ModelViewer(QWidget* parent) : QOpenGLWidget(parent)
{
    init3D();
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

ModelViewer::~ModelViewer()
{
}



bool ModelViewer::event(QEvent* event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchEnd:
    case QEvent::TouchUpdate: {
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent*>(event)->touchPoints();
        unsigned int id = 0;
        unsigned int tapCount = touchPoints.size();

        osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(NULL);
        osgGA::GUIEventAdapter::TouchPhase phase = osgGA::GUIEventAdapter::TOUCH_UNKNOWN;
        foreach(const QTouchEvent::TouchPoint & touchPoint, touchPoints) {
            if (!osgEvent) {
                if (event->type() == QEvent::TouchBegin) {
                    phase = osgGA::GUIEventAdapter::TOUCH_BEGAN;
                    osgEvent = window->getEventQueue()->touchBegan(id, osgGA::GUIEventAdapter::TOUCH_BEGAN, touchPoint.pos().x(), touchPoint.pos().y());
                }
                else if (event->type() == QEvent::TouchEnd) {
                    phase = osgGA::GUIEventAdapter::TOUCH_ENDED;
                    osgEvent = window->getEventQueue()->touchEnded(id, osgGA::GUIEventAdapter::TOUCH_ENDED, touchPoint.pos().x(), touchPoint.pos().y(), tapCount);
                }
                else if (event->type() == QEvent::TouchUpdate) {
                    phase = osgGA::GUIEventAdapter::TOUCH_MOVED;
                    osgEvent = window->getEventQueue()->touchMoved(id, osgGA::GUIEventAdapter::TOUCH_MOVED, touchPoint.pos().x(), touchPoint.pos().y());
                }
            }
            else {
                osgEvent->addTouchPoint(id, osgGA::GUIEventAdapter::TOUCH_ENDED, touchPoint.pos().x(), touchPoint.pos().y());
                osgEvent->addTouchPoint(id, phase, touchPoint.pos().x(), touchPoint.pos().y());
            }
            id++;
        }
        break;
    }
    default:
        break;
    }
    return QOpenGLWidget::event(event);
}

void ModelViewer::setKeyboardModifiers(QInputEvent* event)
{
    int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
    unsigned int mask = 0;
    if (modkey & Qt::ShiftModifier) {
        mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
    }
    if (modkey & Qt::ControlModifier) {
        mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
    }
    if (modkey & Qt::AltModifier) {
        mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
    }

    window->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
    update();
}

void ModelViewer::keyPressEvent(QKeyEvent* event)
{
    setKeyboardModifiers(event);
    window->getEventQueue()->keyPress(event->key());
    QOpenGLWidget::keyPressEvent(event);
    update();
}

void ModelViewer::keyReleaseEvent(QKeyEvent* event)
{
    setKeyboardModifiers(event);
    window->getEventQueue()->keyRelease(event->key());
    QOpenGLWidget::keyReleaseEvent(event);
    update();
}

void ModelViewer::mousePressEvent(QMouseEvent* event)
{
    int button = 0;
    switch (event->button()) {
    case Qt::LeftButton: button = 1; break;
    case Qt::MidButton: button = 2; break;
    case Qt::RightButton: button = 3; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }
    setKeyboardModifiers(event);
    window->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
    update();
}

void ModelViewer::mouseReleaseEvent(QMouseEvent* event)
{
    int button = 0;
    switch (event->button()) {
    case Qt::LeftButton: button = 1; break;
    case Qt::MidButton: button = 2; break;
    case Qt::RightButton: button = 3; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }
    setKeyboardModifiers(event);
    window->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);

    QOpenGLWidget::mouseReleaseEvent(event);
    update();
}

void ModelViewer::mouseDoubleClickEvent(QMouseEvent* event)
{
    int button = 0;
    switch (event->button()) {
    case Qt::LeftButton: button = 1; break;
    case Qt::MidButton: button = 2; break;
    case Qt::RightButton: button = 3; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }
    setKeyboardModifiers(event);
    window->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);

    QOpenGLWidget::mouseDoubleClickEvent(event);
    update();
}

void ModelViewer::mouseMoveEvent(QMouseEvent* event)
{
    setKeyboardModifiers(event);
    window->getEventQueue()->mouseMotion(event->x(), event->y());
    QOpenGLWidget::mouseMoveEvent(event);
    update();
}

void ModelViewer::wheelEvent(QWheelEvent* event)
{
    setKeyboardModifiers(event);
    window->getEventQueue()->mouseScroll(
        event->orientation() == Qt::Vertical ?
        (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
        (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
    QOpenGLWidget::wheelEvent(event);
    update();
}

void ModelViewer::resizeEvent(QResizeEvent* event)
{
    const QSize& size = event->size();
    window->resized(x(), y(), size.width(), size.height());
    window->getEventQueue()->windowResize(x(), y(), size.width(), size.height());
    window->requestRedraw();
    QOpenGLWidget::resizeEvent(event);
}

void ModelViewer::moveEvent(QMoveEvent* event)
{
    const QPoint& pos = event->pos();
    window->resized(pos.x(), pos.y(), width(), height());
    window->getEventQueue()->windowResize(pos.x(), pos.y(), width(), height());

    QOpenGLWidget::moveEvent(event);
}

void ModelViewer::timerEvent(QTimerEvent*)
{
    update();
}

void ModelViewer::paintGL()
{
    if (isVisibleTo(QApplication::activeWindow())) {
        frame();
    }
}

void ModelViewer::init3D()
{
    root = new osg::Group;
    root->setName("Root");
    root->addChild(createSkyBox());
    //�Ż���������
    osgUtil::Optimizer optimzer;
    optimzer.optimize(root.get());

    setCamera(createCamera(0, 0, width(), height()));
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
    setCameraManipulator(manipulator);
    addEventHandler(new osgViewer::StatsHandler);
    addEventHandler(new osgViewer::ThreadingHandler());
    addEventHandler(new osgViewer::HelpHandler);
    addEventHandler(new osgGA::StateSetManipulator(this->getCamera()->getOrCreateStateSet()));
    setThreadingModel(osgViewer::Viewer::SingleThreaded);

    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
   this->setSceneData(root);
  
    startTimer(10);
}
osg::ref_ptr<osg::TextureCubeMap>ModelViewer::readCubeMap()
{
    osg::ref_ptr<osg::TextureCubeMap> cubemap = new osg::TextureCubeMap;

    osg::ref_ptr<osg::Image> imagePosX = osgDB::readImageFile("qss/west.png");
    osg::ref_ptr<osg::Image> imageNegX = osgDB::readImageFile("qss/east.png");
    osg::ref_ptr<osg::Image> imagePosY = osgDB::readImageFile("qss/north.png");
    osg::ref_ptr<osg::Image> imageNegY = osgDB::readImageFile("qss/south.png");
    osg::ref_ptr<osg::Image> imagePosZ = osgDB::readImageFile("qss/top.png");
    osg::ref_ptr<osg::Image> imageNegZ = osgDB::readImageFile("qss/bottom.png");

    if (imagePosX.get() && imageNegX.get() && imagePosY.get() && imageNegY.get() && imagePosZ.get() && imageNegZ.get())
    {
        //��������ͼ�����������ͼ
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, imagePosX.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, imageNegX.get());
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, imagePosY.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, imageNegY.get());
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, imagePosZ.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, imageNegZ.get());

        //����������ģʽ
        cubemap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        cubemap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
        cubemap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

        //�����˲������κ�mipmap
        cubemap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
        cubemap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    }

    return cubemap.get();
}

osg::ref_ptr<osg::Camera> ModelViewer::createCamera(int x, int y, int w, int h)
{
    window = new osgViewer::GraphicsWindowEmbedded(x, y, w, h);
    //    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = true;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(window);
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->setProjectionMatrixAsPerspective(
        30.0f, double(traits->width) / double(traits->height), 1.0f, 10000.0f);
    camera->setClearColor(osg::Vec4(0.3, 0.3, 0.6, 0.1));

    return camera.release();
}
//������պ�
osg::ref_ptr<osg::Node> ModelViewer::createSkyBox()
{
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

    //��������ӳ�䷽ʽ��ָ��Ϊ�����ʽ���������е���ɫ����ԭ������ɫ
    osg::ref_ptr<osg::TexEnv> te = new osg::TexEnv;
    te->setMode(osg::TexEnv::REPLACE);
    stateset->setTextureAttributeAndModes(0, te.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    //�Զ������������꣬���䷽ʽ(REFLECTION_MAP)
    /*
    NORMAL_MAP����׼ģʽ������ͼ����
    REFLECTION_MAP������ģʽ����������
    SPHERE_MAP������ģ�ͣ���������
    */
    osg::ref_ptr<osg::TexGen> tg = new osg::TexGen;
    tg->setMode(osg::TexGen::NORMAL_MAP);
    stateset->setTextureAttributeAndModes(0, tg.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    //�����������
    osg::ref_ptr<osg::TexMat> tm = new osg::TexMat;
    stateset->setTextureAttribute(0, tm.get());

    //��������ͼ����
    osg::ref_ptr<osg::TextureCubeMap> skymap = readCubeMap();
    stateset->setTextureAttributeAndModes(0, skymap.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->setMode(GL_CULL_FACE, osg::StateAttribute::OFF);

    //���������ΪԶƽ��
    osg::ref_ptr<osg::Depth> depth = new osg::Depth;
    depth->setFunction(osg::Depth::ALWAYS);
    depth->setRange(1.0, 1.0);//Զƽ��   
    stateset->setAttributeAndModes(depth, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    //������Ⱦ˳��Ϊ-1������Ⱦ
    stateset->setRenderBinDetails(-1, "RenderBin");

    osg::ref_ptr<osg::Drawable> drawable = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), 1));

    //��������뵽Ҷ�ڵ�
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->setCullingActive(false);
    geode->setStateSet(stateset.get());
    geode->addDrawable(drawable.get());

    //���ñ任
    osg::ref_ptr<osg::Transform> transform = new MoveEarthySkyWithEyePointTransform();
    transform->setCullingActive(false);
    transform->addChild(geode.get());

    osg::ref_ptr<osg::ClearNode> clearNode = new osg::ClearNode;
    clearNode->setCullCallback(new TexMatCallback(*tm));
    clearNode->addChild(transform.get());

    return clearNode.get();
}

