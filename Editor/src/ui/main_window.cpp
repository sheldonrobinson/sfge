#include "main_window.hpp"

#include <QtCore/QRegExp>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include "sfge_render_widget.hpp"

#include <exception>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mUi.setupUi(this);

	mOriginalTitle = windowTitle();

	connect(mUi.actionNew,	SIGNAL(triggered()), this, SLOT(OnFileNew()));
	connect(mUi.actionOpen,	SIGNAL(triggered()), this, SLOT(OnFileOpen()));
}

void MainWindow::OnFileNew()
{
	mUi.sfgeRenderWidget->ClearWorld();

	setWindowTitle(mOriginalTitle.arg(tr("[Unnamed]")));

	mUi.sfgeRenderWidget->repaint();
}

void MainWindow::OnFileOpen()
{
	const std::string worldFolder(mUi.sfgeRenderWidget->GetWorldDefsFolder());
	QString worldFile = QFileDialog::getOpenFileName(this, tr("Select a world file..."),
		QString::fromAscii(worldFolder.c_str(), worldFolder.size()),
		tr("World descriptions (*.json)"));

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
