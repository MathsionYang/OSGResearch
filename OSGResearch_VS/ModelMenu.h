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
	// �ļ�ģ��
	void menu_File();

	// ������
	QPointer<QToolBar> m_PtrToolBar;
signals:
	void sendResponseArgu(int type,QStringList strList);
private slots:
	void File_new();
};
