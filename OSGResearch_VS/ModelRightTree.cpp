#include "ModelRightTree.h"
#include <qfileinfo.h>
#include <qdebug.h>
ModelRightTree::ModelRightTree(QWidget *parent)
	: QTreeView(parent)
{

	initTree();
}

ModelRightTree::~ModelRightTree()
{

}

void ModelRightTree::addSubModelItem(const QString& itemName)
{
	
	QStandardItem* itemSub = new QStandardItem;
	itemSub->setText( QFileInfo(itemName).baseName());
	itemSub->setCheckable(true);
	itemSub->setCheckState(Qt::Unchecked);
	itemSub->setData(itemName);
	m_ptrItemModel->appendRow(itemSub);

}

void ModelRightTree::initTree()
{
	m_ptrStandardModel = QSharedPointer<QStandardItemModel>(new QStandardItemModel);
	//3.��ȡģ�͸�item
	QStandardItem* itemTop = m_ptrStandardModel->invisibleRootItem();

	m_ptrStandardModel->setHorizontalHeaderLabels(QStringList(QStringLiteral("����")));
	m_ptrItemModel = QSharedPointer<QStandardItem>( new QStandardItem());
	m_ptrItemModel->setIcon(QIcon(":/OSGResearch_VS/qss/tree_model.png"));
	m_ptrItemModel->setText(QStringLiteral("ģ���ļ�"));

	m_ptrItemVector =  QSharedPointer<QStandardItem>(new QStandardItem());
	m_ptrItemVector->setIcon(QIcon(":/OSGResearch_VS/qss/tree_vector.png"));
	m_ptrItemVector->setText(QStringLiteral("ʸ���ļ�"));


	itemTop->appendRow(m_ptrItemModel.data());
	itemTop->appendRow( m_ptrItemVector.data());
	this->setModel(m_ptrStandardModel.data());
	this->setItemsExpandable(true);
	this->expandAll();
}

