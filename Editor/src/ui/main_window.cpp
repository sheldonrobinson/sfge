#include "main_window.hpp"
#include "sfge_render_widget.hpp"

#include <QtCore/QRegExp>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QTextCursor>
#include <QtGui/QTextDocument>

#include <exception>
#include <algorithm>

#include <sfge/utilities/delegate.hpp>
#include <sfge/utilities/log_manager.hpp>

using namespace sfge;
using namespace std;

enum WorldTreeRoles
{
	WTR_GameObjectPtrRole = Qt::UserRole,
	WTR_BehaviourPtrRole,
};

Q_DECLARE_METATYPE(sfge::GameObjectWeakPtr);
Q_DECLARE_METATYPE(sfge::BehaviourPtr);

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mUi.setupUi(this);

	mUi.menu_View->addAction(mUi.dockWidgetWorld->toggleViewAction());
	mUi.menu_View->addAction(mUi.dockWidgetGODefs->toggleViewAction());

	connect(mUi.actionNew,	SIGNAL(triggered()), this, SLOT(OnFileNew()));
	connect(mUi.actionOpen,	SIGNAL(triggered()), this, SLOT(OnFileOpen()));
	
	mOriginalTitle = windowTitle();
	setWindowTitle(mOriginalTitle.arg(tr("[Unnamed]")));

	DataStore::GODInstantiationListener listener =
		DataStore::GODInstantiationListener::from_method<MainWindow, &MainWindow::OnGameObjectInstantiated>(this);
	DataStore::getSingleton().AddGODInstantiationListener(listener);

	mConsoleLogger = Log::LogListener::from_method<MainWindow, &MainWindow::OnMessageLogged>(this);
	LogManager::getSingleton().GetDefaultLogger()->AddListener(mConsoleLogger);
}

void MainWindow::OnFileNew()
{
	setWindowTitle(mOriginalTitle.arg(tr("[Unnamed]")));

	ClearWorldTree();
	mUi.sfgeRenderWidget->ClearWorld();
	mUi.sfgeRenderWidget->repaint();
}

void MainWindow::OnFileOpen()
{
	const std::string worldFolder(mUi.sfgeRenderWidget->GetWorldDefsFolder());
	QString worldFile = QFileDialog::getOpenFileName(this, tr("Select a world file..."),
		QString::fromAscii(worldFolder.c_str(), worldFolder.size()),
		tr("World descriptions (*.json)"));
	
	mUi.sfgeRenderWidget->ClearWorld();
	ClearWorldTree();

	if (worldFile.isEmpty())
		return;

	try
	{
		QRegExp worldNameRegex(".*/(.+)\\.json", Qt::CaseInsensitive, QRegExp::RegExp2);
		worldNameRegex.exactMatch(worldFile);
		QString worldNameQStr(worldNameRegex.cap(1));

		const string worldName(worldNameQStr.toAscii().data());
		mUi.sfgeRenderWidget->LoadWorld(worldName);
		
		setWindowTitle(mOriginalTitle.arg(worldNameQStr));
		
		mUi.sfgeRenderWidget->repaint();
	}
	catch (const exception &e)
	{
		QMessageBox::critical(this, "SFGE Editor", tr("Couldn't open %1.\nReason: %2").arg(worldFile, e.what()));
	}
}

void MainWindow::ClearWorldTree()
{
	QTreeWidgetItem *worldNode = mUi.treeWidgetWorld->topLevelItem(0);
	Q_ASSERT(worldNode != nullptr);

	QList<QTreeWidgetItem*> children = worldNode->takeChildren();
	for_each(children.begin(), children.end(), [] (QTreeWidgetItem *i) { delete i; } );
}

void MainWindow::OnGameObjectInstantiated(DataStore::GameObjectInstantiated &goiInfos)
{
	QTreeWidgetItem *worldNode = mUi.treeWidgetWorld->topLevelItem(0);
	Q_ASSERT(worldNode != nullptr);

	QString itemText;
	if (goiInfos.mInstanceName.empty())
		itemText = "<unnamed>";
	else
		itemText = QString::fromLocal8Bit(goiInfos.mInstanceName.c_str(), goiInfos.mInstanceName.size());
	itemText += " : " + QString::fromLocal8Bit(goiInfos.mGODName.c_str(), goiInfos.mGODName.size());

	QVariant goVariant;
	goVariant.setValue(goiInfos.mGoPtr);
	
	QTreeWidgetItem *goItem = new QTreeWidgetItem(worldNode);
	goItem->setText(0, itemText);
	goItem->setData(0, WTR_GameObjectPtrRole, goVariant);

	for_each(goiInfos.mBehaviours.begin(), goiInfos.mBehaviours.end(),
		[&] (DataStore::GameObjectInstantiated::Behaviours::value_type &behaviour)
		{
			QTreeWidgetItem *behaviourItem = new QTreeWidgetItem(goItem);
			behaviourItem->setText(0, QString::fromLocal8Bit(behaviour.first.c_str(), behaviour.first.size()));

			QVariant behaviourPtrVariant;
			behaviourPtrVariant.setValue(behaviour.second);
			behaviourItem->setData(0, WTR_BehaviourPtrRole, behaviourPtrVariant);
		} );

	goItem->setExpanded(true);
	worldNode->setExpanded(true);
}

void MainWindow::OnMessageLogged(const std::string &msg)
{
	QTextCursor cursor(mUi.textEditConsole->document());
	cursor.movePosition(QTextCursor::End);
	mUi.textEditConsole->setTextCursor(cursor);
	
	cursor.insertText(QString::fromLocal8Bit(msg.c_str(), msg.size()));
}
