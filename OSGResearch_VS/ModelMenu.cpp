#include "ModelMenu.h"
#include <QAction>
#include <QFileDialog>
ModelMenu::ModelMenu(QWidget* parent)
	: QMenuBar(parent)
{
	m_PtrToolBar = new QToolBar;
	m_PtrToolBar->setMovable(false);
	menu_File();
}

ModelMenu::~ModelMenu()
{}

void ModelMenu::menu_File()
{
	QAction* Act_new_file = new QAction(QIcon(":/OSGResearch_VS/qss/new.png"), QStringLiteral("��"), this);
	Act_new_file->setShortcut(Qt::Key_Control & Qt::Key_N);
	connect(Act_new_file, SIGNAL(triggered()), this, SLOT(File_new()));

	QMenu* file = addMenu(QStringLiteral("�ļ�(N)"));
	file->addAction(Act_new_file);
	m_PtrToolBar->addAction(Act_new_file);
}

void ModelMenu::File_new()
{
	QFileDialog* fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(QStringLiteral("ѡ���ļ�"));
	fileDialog->setDirectory("./");
	fileDialog->setNameFilter(tr("osg File(*.osg* *.osgt* *.osgb*)"));
	// ��ѡ
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	fileDialog->setViewMode(QFileDialog::Detail);
	QStringList fileNames;
	if (fileDialog->exec()) {
		fileNames = fileDialog->selectedFiles();
	}
	if (fileNames.size() > 0)
	{
		emit sendResponseArgu(OPENFILE, fileNames);
	}
}