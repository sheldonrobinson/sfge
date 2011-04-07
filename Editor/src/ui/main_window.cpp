#include "main_window.hpp"
#include "sfge_render_widget.hpp"
#include "world_tree_widget.hpp"

#include <QtCore/QRegExp>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QTextCursor>
#include <QtGui/QTextDocument>

#include <sfge/infrastructure/data_store.hpp>
#include <sfge/utilities/delegate.hpp>
#include <sfge/utilities/log_manager.hpp>

using namespace sfge;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mUi.setupUi(this);

	mUi.menu_View->addAction(mUi.dockWidgetWorld->toggleViewAction());
	mUi.menu_View->addAction(mUi.dockWidgetGODefs->toggleViewAction());
	mUi.menu_View->addAction(mUi.dockWidgetProperties->toggleViewAction());

	connect(mUi.actionNew,	SIGNAL(triggered()), this, SLOT(OnFileNew()));
	connect(mUi.actionOpen,	SIGNAL(triggered()), this, SLOT(OnFileOpen()));
	connect(mUi.treeWidgetWorld, SIGNAL(ActiveGameObjectChanged(GameObjectBehaviours*)),
			mUi.treeWidgetProperties, SLOT(OnCurrentGameObjectChanged(GameObjectBehaviours*)));
	
	mOriginalTitle = windowTitle();
	setWindowTitle(mOriginalTitle.arg(tr("[Unnamed]")));

	DataStore::GODInstantiationListener listener =
		DataStore::GODInstantiationListener::from_method<WorldTreeWidget, &WorldTreeWidget::OnGameObjectInstantiated>(mUi.treeWidgetWorld);
	DataStore::getSingleton().AddGODInstantiationListener(listener);

	mConsoleLogger = Log::LogListener::from_method<MainWindow, &MainWindow::OnMessageLogged>(this);
	LogManager::getSingleton().GetDefaultLogger()->AddListener(mConsoleLogger);
}

void MainWindow::OnFileNew()
{
	setWindowTitle(mOriginalTitle.arg(tr("[Unnamed]")));

	mUi.treeWidgetWorld->ClearWorldTree();
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
	mUi.treeWidgetWorld->ClearWorldTree();

	if (worldFile.isEmpty())
		return;

	QRegExp worldNameRegex(".*/(.+)\\.json", Qt::CaseInsensitive, QRegExp::RegExp2);
	worldNameRegex.exactMatch(worldFile);
	QString worldNameQStr(worldNameRegex.cap(1));

	const string worldName(worldNameQStr.toAscii().data());
	mUi.sfgeRenderWidget->LoadWorld(worldName);
		
	setWindowTitle(mOriginalTitle.arg(worldNameQStr));
		
	mUi.sfgeRenderWidget->repaint();
}

void MainWindow::OnMessageLogged(const std::string &msg)
{
	QTextCursor cursor(mUi.textEditConsole->document());
	cursor.movePosition(QTextCursor::End);
	mUi.textEditConsole->setTextCursor(cursor);
	
	cursor.insertText(QString::fromLocal8Bit(msg.c_str(), msg.size()));
}
