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

    // 显示Las的区域
    QPointer<QDockWidget> m_dockMain;
    // 显示工程信息的区域
    QPointer<QDockWidget> m_dockProInfo;
    // 显示信息的区域
    QPointer<QDockWidget> m_dockModelInfo;
    // 显示其他信息的区域
    QPointer<QDockWidget> m_dockOtherInfo;

    //初始化界面
    void initWindowsLayout();
};
