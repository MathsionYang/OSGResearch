#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OSGResearch_VS.h"
#include <QPointer>
#include <QDockWidget>
#include "OurModelViewer.h"
#include <QSharedPointer>
#include "ModelMenu.h"
#include <QTreeWidget>
#include "ModelRightTree.h"
class OSGResearch_VS : public QMainWindow
{
    Q_OBJECT

public:
    OSGResearch_VS(QWidget *parent = nullptr);
    ~OSGResearch_VS();

private:
    Ui::OSGResearch_VSClass ui;

    QSharedPointer<ModelViewer>m_ptrModelViewer;
    QSharedPointer<ModelMenu>m_ptrModelMenu;
    // 显示模型的区域
    QPointer<QDockWidget> m_dockMain;
    // 显示工程信息的区域
    QPointer<QDockWidget> m_dockProInfo;

    // 工程文件树
    QPointer<ModelRightTree> m_ptrRightTree;
    //初始化界面
    void initWindowsLayout();

    //打开文件
    void openNewFiles(const QStringList& strList);
private slots:
    void recvResponseArgu(int type, QStringList strList);
};
