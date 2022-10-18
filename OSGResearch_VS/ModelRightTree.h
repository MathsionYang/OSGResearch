#pragma once
#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSharedPointer>
class ModelRightTree  : public QTreeWidget
{
	Q_OBJECT

public:
	ModelRightTree(QWidget *parent);
	~ModelRightTree();

	void addSubModelItem(const QString& itemName);

private:
	void initTree();

	QSharedPointer<QTreeWidgetItem> m_ptrItemModel;
	QSharedPointer<QTreeWidgetItem> m_ptrItemVector;
};
