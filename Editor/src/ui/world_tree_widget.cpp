#include "world_tree_widget.hpp"

#include <algorithm>

#include <sfge/utilities/log_manager.hpp>

using namespace sfge;
using namespace std;

enum WorldTreeRoles
{
	WTR_GameObjectPtrRole = Qt::UserRole
};

Q_DECLARE_METATYPE(sfge::GameObjectWeakPtr);

WorldTreeWidget::WorldTreeWidget(QWidget *parent)
	: QTreeWidget(parent)
{
	connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(OnSelectionChanged()));
}

void WorldTreeWidget::ClearWorldTree()
{
	QTreeWidgetItem *worldNode = topLevelItem(0);
	Q_ASSERT(worldNode != nullptr);

	QList<QTreeWidgetItem*> children = worldNode->takeChildren();
	for_each(children.begin(), children.end(), [] (QTreeWidgetItem *i) { delete i; } );

	mGameObjectInfos.clear();
}

void WorldTreeWidget::OnGameObjectInstantiated(DataStore::GameObjectInstantiated &goiInfos)
{
	QTreeWidgetItem *worldNode = topLevelItem(0);
	Q_ASSERT(worldNode != nullptr);

	// Create the Game Object node
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

	// Store all the Behaviours relevant to this game object definition
	mGameObjectInfos.insert(make_pair(goiInfos.mGoPtr.lock().get(), goiInfos.mBehaviours));

	worldNode->setExpanded(true);
}

void WorldTreeWidget::OnSelectionChanged()
{
	emit ActiveGameObjectChanged(GetGOBehavioursForCurrentItem());
}

GameObjectBehaviours* WorldTreeWidget::GetGOBehavioursForCurrentItem()
{
	QList<QTreeWidgetItem*> items = selectedItems();
	if (items.size() == 0)
		return nullptr;

	QVariant goPtrVariant = items.at(0)->data(0, WTR_GameObjectPtrRole);
	if (!goPtrVariant.isValid())
		return nullptr;

	GameObjectWeakPtr goPtr = goPtrVariant.value<GameObjectWeakPtr>();
	if (goPtr.expired())
	{
		LogManager::getSingleton() << "Tried to get behaviours' informations on an expired GameObject.\n";
		return nullptr;
	}

	GODetails::iterator it = mGameObjectInfos.find(goPtr.lock().get());
	if (it == mGameObjectInfos.end())
	{
		LogManager::getSingleton() << "Tried to get behaviours' informations on an unknown GameObject.\n";
		return nullptr;
	}

	return &it->second;
}
