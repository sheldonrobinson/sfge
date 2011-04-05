/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 5. Apr 19:06:42 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "sfge_render_widget.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionImages;
    SFGERenderWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_View;
    QStatusBar *statusbar;
    QDockWidget *dockWidgetImages;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidgetImages;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(783, 681);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setShortcutContext(Qt::ApplicationShortcut);
        actionImages = new QAction(MainWindow);
        actionImages->setObjectName(QString::fromUtf8("actionImages"));
        actionImages->setCheckable(true);
        actionImages->setChecked(true);
        centralwidget = new SFGERenderWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 783, 18));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_View = new QMenu(menubar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockWidgetImages = new QDockWidget(MainWindow);
        dockWidgetImages->setObjectName(QString::fromUtf8("dockWidgetImages"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidgetImages = new QListWidget(dockWidgetContents);
        listWidgetImages->setObjectName(QString::fromUtf8("listWidgetImages"));

        verticalLayout->addWidget(listWidgetImages);

        dockWidgetImages->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetImages);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_View->menuAction());
        menu_File->addAction(actionQuit);
        menu_View->addAction(actionImages);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionImages, SIGNAL(toggled(bool)), dockWidgetImages, SLOT(setVisible(bool)));
        QObject::connect(dockWidgetImages, SIGNAL(visibilityChanged(bool)), actionImages, SLOT(setChecked(bool)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SFGE Editor", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QString());
        actionImages->setText(QApplication::translate("MainWindow", "Images", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
        dockWidgetImages->setWindowTitle(QApplication::translate("MainWindow", "Images", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
