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
    // ��ʾģ�͵�����
    QPointer<QDockWidget> m_dockMain;
    // ��ʾ������Ϣ������
    QPointer<QDockWidget> m_dockProInfo;

    // �����ļ���
    QPointer<ModelRightTree> m_ptrRightTree;
    //��ʼ������
    void initWindowsLayout();

    //���ļ�
    void openNewFiles(const QStringList& strList);
private slots:
    void recvResponseArgu(int type, QStringList strList);
};
