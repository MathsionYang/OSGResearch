#include "ModelRightTree.h"
#include <qfileinfo.h>
#include <qdebug.h>
ModelRightTree::ModelRightTree(QWidget *parent)
	: QTreeWidget(parent)
{
	initTree();
}

ModelRightTree::~ModelRightTree()
{

}

void ModelRightTree::addSubModelItem(const QString& itemName)
{
	int index = m_ptrItemModel->childCount();
	QTreeWidgetItem* newModel =new QTreeWidgetItem();
	newModel->setText(0, QFileInfo(itemName).baseName());
	newModel->setData(0, Qt::UserRole + 1, itemName);
	newModel->setCheckState(0, Qt::Checked);
	m_ptrItemModel->insertChild(index, newModel);
	qDebug() <<"size:" << m_ptrItemModel->childCount();
	
	delete newModel;
	newModel = nullptr;
	this->insertTopLevelItem(0, m_ptrItemModel.data());
	this->expandAll();
}

void ModelRightTree::initTree()
{
	this->setHeaderHidden(true);
	m_ptrItemModel = QSharedPointer<QTreeWidgetItem>( new QTreeWidgetItem(this));
	m_ptrItemModel->setIcon(0, QIcon(":/OSGResearch_VS/qss/tree_model.png"));
	m_ptrItemModel->setText(0, QStringLiteral("模型文件"));

	m_ptrItemVector =  QSharedPointer<QTreeWidgetItem>(new QTreeWidgetItem(this));
	m_ptrItemVector->setIcon(0, QIcon(":/OSGResearch_VS/qss/tree_vector.png"));
	m_ptrItemVector->setText(0, QStringLiteral("矢量文件"));


	this->insertTopLevelItem(0,m_ptrItemModel.data());
	this->insertTopLevelItem(1, m_ptrItemVector.data());
	this->setItemsExpandable(true);
	this->expandAll();
}

