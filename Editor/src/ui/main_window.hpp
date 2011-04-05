#ifndef SFGE_EDITOR_UI_MAIN_WINDOW_HPP
#define SFGE_EDITOR_UI_MAIN_WINDOW_HPP

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);

private slots:
	void OnFileNew();
	void OnFileOpen();

private:
	Ui::MainWindow	mUi;
	QString			mOriginalTitle;
};

#endif
