#include "properties_editor.hpp"

#include <algorithm>

using namespace std;

PropertiesEditor::PropertiesEditor(QWidget *parent)
	: QTreeWidget(parent), mCurrentGOB(nullptr)
{
}

void PropertiesEditor::OnCurrentGameObjectChanged(GameObjectBehaviours *newGOB)
{
	if (mCurrentGOB == newGOB)
		return;

	mCurrentGOB = newGOB;
	clear();

	if (mCurrentGOB == nullptr)
		return;

	for_each(mCurrentGOB->begin(), mCurrentGOB->end(),
		[&] (const GameObjectBehaviours::value_type &gobEntry)
		{
			QString text(QString::fromUtf8(gobEntry.first.c_str(), gobEntry.first.size()));
			new QTreeWidgetItem(this, QStringList() << text);
		} );
}
