#include <QtGui/QApplication>

#include "ui\main_window.hpp"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(true);

	MainWindow mw;
	mw.show();

	return app.exec();
}
