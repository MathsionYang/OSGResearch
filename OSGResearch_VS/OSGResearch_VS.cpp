#include "OSGResearch_VS.h"
#include <qguiapplication.h>
#include <qscreen.h>
#include <QLabel>
#include <osgDB/ReadFile>
#include <qdebug.h>
#include <QFileInfo>
OSGResearch_VS::OSGResearch_VS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_ptrModelViewer = QSharedPointer<ModelViewer>(new ModelViewer(this));
    m_ptrModelMenu = QSharedPointer<ModelMenu>(new ModelMenu(this));
    this->setMenuBar(m_ptrModelMenu.data());
    this->addToolBar(m_ptrModelMenu->getToolBar());

    //��ʼ�������ļ���
    m_ptrRightTree = new ModelRightTree(this);
   

    initWindowsLayout();

   


    connect(m_ptrModelMenu.data(), SIGNAL(sendResponseArgu(int, QStringList)), this, SLOT(recvResponseArgu(int, QStringList)));

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
    // �����Ӵ����С
    m_dockProInfo->setFixedWidth(200);
    // ���ַ���
    setCentralWidget(m_dockMain);
    addDockWidget(Qt::LeftDockWidgetArea, m_dockProInfo);

    m_dockMain->setWidget(m_ptrModelViewer.data());

    m_dockProInfo->setWidget(m_ptrRightTree);
}
void OSGResearch_VS::openNewFiles(const QStringList& strList)
{
    if (strList.size() <= 0)
        return;
    for (QString str : strList)
    {
        if (QFileInfo(str).suffix().contains("osg", Qt::CaseInsensitive))
        {
            m_ptrRightTree->addSubModelItem(str);
        }
    }
    m_ptrRightTree->update();
  
    m_dockProInfo->update();
    std::string osgPath = "F:\\OSGB365\\OSGData\\cow.osg";
    osg::Node* node = new osg::Node;
    node = osgDB::readNodeFile(osgPath);
    m_ptrModelViewer->setSceneData(node);
    m_ptrModelViewer->run();
}
void OSGResearch_VS::recvResponseArgu(int type, QStringList strList)
{
    if (type = 0 || strList.size() <= 0)
        return;
    switch (type)
    {
    case OPENFILE:
        openNewFiles(strList);
        break;
    default:
        break;
    }
}