#pragma once
#include <QObject>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem >
#include <QSharedPointer>
class ModelRightTree  : public QTreeView
{
	Q_OBJECT

public:
	ModelRightTree(QWidget *parent);
	~ModelRightTree();

	void addSubModelItem(const QString& itemName);

private:
	void initTree();
	QSharedPointer<QStandardItemModel> m_ptrStandardModel;
	QSharedPointer<QStandardItem > m_ptrItemModel;
	QSharedPointer<QStandardItem > m_ptrItemVector;
};
