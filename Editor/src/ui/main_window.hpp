#ifndef SFGE_EDITOR_UI_MAIN_WINDOW_HPP
#define SFGE_EDITOR_UI_MAIN_WINDOW_HPP

#include "ui_mainwindow.h"

#include <sfge/infrastructure/data_store.hpp>

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

private:
	Ui::MainWindow	mUi;
	QString			mOriginalTitle;
};

#endif
