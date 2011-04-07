#ifndef SFGE_EDITOR_WORLD_TREE_WIDGET_HPP
#define SFGE_EDITOR_WORLD_TREE_WIDGET_HPP

#include <QtGui/QTreeWidget>

#include "ui_types.hpp"

#include <map>

class WorldTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	typedef std::map<sfge::GameObject*, GameObjectBehaviours>	GODetails;

public:
	WorldTreeWidget(QWidget *parent = nullptr);

	void ClearWorldTree();
	void OnGameObjectInstantiated(sfge::DataStore::GameObjectInstantiated &goiInfos);

	GameObjectBehaviours* GetGOBehavioursForCurrentItem();

signals:
	void ActiveGameObjectChanged(GameObjectBehaviours *newGOB);

private slots:
	void OnSelectionChanged();

private:
	GODetails	mGameObjectInfos;
};

#endif
