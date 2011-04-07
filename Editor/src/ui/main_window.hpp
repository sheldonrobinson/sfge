#ifndef SFGE_EDITOR_UI_MAIN_WINDOW_HPP
#define SFGE_EDITOR_UI_MAIN_WINDOW_HPP

#include "ui_mainwindow.h"

#include <sfge/infrastructure/data_store.hpp>
#include <sfge/utilities/log.hpp>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);

private slots:
	void OnFileNew();
	void OnFileOpen();

private:
	void ClearWorldTree();
	void OnGameObjectInstantiated(sfge::DataStore::GameObjectInstantiated &goiInfos);

	void OnMessageLogged(const std::string &msg);

private:
	Ui::MainWindow			mUi;
	QString					mOriginalTitle;
	sfge::Log::LogListener	mConsoleLogger;
};

#endif
