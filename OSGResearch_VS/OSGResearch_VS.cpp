#include "OSGResearch_VS.h"
#include <qguiapplication.h>
#include <qscreen.h>
#include <QLabel>
#include <osgDB/ReadFile>
OSGResearch_VS::OSGResearch_VS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_ptrModelViewer = QSharedPointer<ModelViewer>(new ModelViewer(this));
    initWindowsLayout();

    std::string osgPath = "F:\\OSGB365\\OSGData\\cow.osg";
    osg::Node* node = new osg::Node;
    node = osgDB::readNodeFile(osgPath);
    m_ptrModelViewer->setSceneData(node);
}

OSGResearch_VS::~OSGResearch_VS()
{

}

void OSGResearch_VS::initWindowsLayout()
{
    // 软件名称
    setWindowTitle(QStringLiteral("OSGReaserch"));
    // 软件图标
    setWindowIcon(QIcon(":/OSGResearch_VS/qss/model.png"));
    // 设置大小
    resize(QGuiApplication::primaryScreen()->availableSize() * 16 / 9);
    // 删除中央窗体
    QWidget* centralWidget = takeCentralWidget();
    if (centralWidget)
        delete centralWidget;
    //允许嵌套dock
    setDockNestingEnabled(true);

    // 设置状态栏
    QStatusBar* stBar = statusBar();
    setStatusBar(stBar);
    //添加提示信息到右侧
    QLabel* lab_cprt = new QLabel(QStringLiteral("@版权所属1114809057@qq.com"), this);
    lab_cprt->setStyleSheet("color:#000000;margin-right:10px;");
    stBar->addPermanentWidget(lab_cprt);
    stBar->setStyleSheet("background:#ffffff;border: 1px solid black;");

    // 点云显示区域
    m_dockMain = new QDockWidget(this);
    m_dockMain->setWindowTitle(QStringLiteral("模型"));
    // 设置为可移动可浮动，但不可关闭
    m_dockMain->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    // 可移动范围：左右
    m_dockMain->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // 工程信息
    m_dockProInfo = new QDockWidget(this);
    m_dockProInfo->setWindowTitle(QStringLiteral("工程"));
    m_dockProInfo->setFeatures(QDockWidget::DockWidgetClosable);

    // 点云信息
    m_dockModelInfo = new QDockWidget(this);
    m_dockModelInfo->setWindowTitle(QStringLiteral("属性"));
    m_dockModelInfo->setFeatures(QDockWidget::AllDockWidgetFeatures);

    // 其他信息
    m_dockOtherInfo = new QDockWidget(this);
    m_dockOtherInfo->setWindowTitle(QStringLiteral("其他"));
    m_dockOtherInfo->setFeatures(QDockWidget::AllDockWidgetFeatures);

    // 设置子窗体大小
    m_dockProInfo->setFixedWidth(200);
    m_dockModelInfo->setFixedWidth(200);
    m_dockOtherInfo->setFixedWidth(200);
    m_dockModelInfo->setMaximumHeight(400);

    // 布局方向
    setCentralWidget(m_dockMain);
    addDockWidget(Qt::LeftDockWidgetArea, m_dockProInfo);
    addDockWidget(Qt::RightDockWidgetArea, m_dockModelInfo);
    addDockWidget(Qt::RightDockWidgetArea, m_dockOtherInfo);

    // 布局方向
    splitDockWidget(m_dockModelInfo, m_dockOtherInfo, Qt::Vertical);

    m_dockMain->setWidget(m_ptrModelViewer.data());
}
