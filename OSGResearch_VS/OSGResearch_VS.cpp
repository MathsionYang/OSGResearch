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
    // �������
    setWindowTitle(QStringLiteral("OSGReaserch"));
    // ���ͼ��
    setWindowIcon(QIcon(":/OSGResearch_VS/qss/model.png"));
    // ���ô�С
    resize(QGuiApplication::primaryScreen()->availableSize() * 16 / 9);
    // ɾ�����봰��
    QWidget* centralWidget = takeCentralWidget();
    if (centralWidget)
        delete centralWidget;
    //����Ƕ��dock
    setDockNestingEnabled(true);

    // ����״̬��
    QStatusBar* stBar = statusBar();
    setStatusBar(stBar);
    //�����ʾ��Ϣ���Ҳ�
    QLabel* lab_cprt = new QLabel(QStringLiteral("@��Ȩ����1114809057@qq.com"), this);
    lab_cprt->setStyleSheet("color:#000000;margin-right:10px;");
    stBar->addPermanentWidget(lab_cprt);
    stBar->setStyleSheet("background:#ffffff;border: 1px solid black;");

    // ������ʾ����
    m_dockMain = new QDockWidget(this);
    m_dockMain->setWindowTitle(QStringLiteral("ģ��"));
    // ����Ϊ���ƶ��ɸ����������ɹر�
    m_dockMain->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    // ���ƶ���Χ������
    m_dockMain->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // ������Ϣ
    m_dockProInfo = new QDockWidget(this);
    m_dockProInfo->setWindowTitle(QStringLiteral("����"));
    m_dockProInfo->setFeatures(QDockWidget::DockWidgetClosable);

    // ������Ϣ
    m_dockModelInfo = new QDockWidget(this);
    m_dockModelInfo->setWindowTitle(QStringLiteral("����"));
    m_dockModelInfo->setFeatures(QDockWidget::AllDockWidgetFeatures);

    // ������Ϣ
    m_dockOtherInfo = new QDockWidget(this);
    m_dockOtherInfo->setWindowTitle(QStringLiteral("����"));
    m_dockOtherInfo->setFeatures(QDockWidget::AllDockWidgetFeatures);

    // �����Ӵ����С
    m_dockProInfo->setFixedWidth(200);
    m_dockModelInfo->setFixedWidth(200);
    m_dockOtherInfo->setFixedWidth(200);
    m_dockModelInfo->setMaximumHeight(400);

    // ���ַ���
    setCentralWidget(m_dockMain);
    addDockWidget(Qt::LeftDockWidgetArea, m_dockProInfo);
    addDockWidget(Qt::RightDockWidgetArea, m_dockModelInfo);
    addDockWidget(Qt::RightDockWidgetArea, m_dockOtherInfo);

    // ���ַ���
    splitDockWidget(m_dockModelInfo, m_dockOtherInfo, Qt::Vertical);

    m_dockMain->setWidget(m_ptrModelViewer.data());
}
