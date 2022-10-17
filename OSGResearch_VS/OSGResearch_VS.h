#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OSGResearch_VS.h"
#include <QPointer>
#include <QDockWidget>
#include "OurModelViewer.h"
#include <QSharedPointer>
class OSGResearch_VS : public QMainWindow
{
    Q_OBJECT

public:
    OSGResearch_VS(QWidget *parent = nullptr);
    ~OSGResearch_VS();

private:
    Ui::OSGResearch_VSClass ui;

    QSharedPointer<ModelViewer>m_ptrModelViewer;

    // ��ʾLas������
    QPointer<QDockWidget> m_dockMain;
    // ��ʾ������Ϣ������
    QPointer<QDockWidget> m_dockProInfo;
    // ��ʾ��Ϣ������
    QPointer<QDockWidget> m_dockModelInfo;
    // ��ʾ������Ϣ������
    QPointer<QDockWidget> m_dockOtherInfo;

    //��ʼ������
    void initWindowsLayout();
};
