#pragma once
#include <QObject>
#include <QMenuBar>
#include <QToolBar>
#include <QPointer>
#include "CommonArguments.h"


class ModelMenu  : public QMenuBar
{
	Q_OBJECT

public:
	ModelMenu(QWidget *parent);
	~ModelMenu();
	QPointer<QToolBar> getToolBar()
	{
		return m_PtrToolBar;
	}
private:
	// 文件模块
	void menu_File();

	// 工具栏
	QPointer<QToolBar> m_PtrToolBar;
signals:
	void sendResponseArgu(int type,QStringList strList);
private slots:
	void File_new();
};
