#include <QOpenGLWidget>
#include <osgViewer/Viewer>
#include <QEvent>
#include <osg/TextureCubeMap>
#include <osg/TexMat>
#include <osg/Material>
#include <osg/NodeCallback>
#include <osg/Depth>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
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
    osg::ref_ptr<osg::TextureCubeMap> readCubeMap();
    osg::ref_ptr<osg::Camera> createCamera(int x, int y, int w, int h);

    osg::ref_ptr<osg::Node> createSkyBox();

private:
    osg::ref_ptr<osg::Group> root;
    osgViewer::GraphicsWindow* window;

};
//更新立方体图纹理
struct TexMatCallback : public osg::NodeCallback
{
public:

	TexMatCallback(osg::TexMat& tm) :
		_texMat(tm)
	{
		
	}

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (cv)
		{
			//得到模型视图矩阵并设置旋转角度
			const osg::Matrix& MV = *(cv->getModelViewMatrix());
			const osg::Matrix R = osg::Matrix::rotate(osg::DegreesToRadians(112.0f), 0.0f, 0.0f, 1.0f) *
				osg::Matrix::rotate(osg::DegreesToRadians(90.0f), 1.0f, 0.0f, 0.0f);

			osg::Quat q = MV.getRotate();
			const osg::Matrix C = osg::Matrix::rotate(q.inverse());

			//设置纹理矩阵
			_texMat.setMatrix(C * R);
		}

		traverse(node, nv);
	}

	//纹理矩阵
	osg::TexMat& _texMat;
};

//一个变换类，使天空盒绕视点旋转
class MoveEarthySkyWithEyePointTransform : public osg::Transform
{
public:
    //局部矩阵计算成世界矩阵
    virtual bool computeLocalToWorldMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
    {
        osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
        if (cv)
        {
            osg::Vec3 eyePointLocal = cv->getEyeLocal();
            matrix.preMult(osg::Matrix::translate(eyePointLocal));
        }
        return true;
    }

    //世界矩阵计算为局部矩阵
    virtual bool computeWorldToLocalMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
    {
        osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
        if (cv)
        {
            osg::Vec3 eyePointLocal = cv->getEyeLocal();
            matrix.postMult(osg::Matrix::translate(-eyePointLocal));
        }
        return true;
    }
};