#ifndef SFGE_EDITOR_PROPERTIES_EDITOR_HPP
#define SFGE_EDITOR_PROPERTIES_EDITOR_HPP

#include <QtGui/QTreeWidget>

#include "ui_types.hpp"

class PropertiesEditor : public QTreeWidget
{
	Q_OBJECT

public:
	PropertiesEditor(QWidget *parent);

public slots:
	void OnCurrentGameObjectChanged(GameObjectBehaviours *newGOB);

private:
	GameObjectBehaviours *mCurrentGOB;
};

#endif
