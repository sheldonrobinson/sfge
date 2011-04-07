#include "properties_editor.hpp"

#include <algorithm>

#include <QtCore/QDir>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <sfge/utilities/log_manager.hpp>

using namespace boost;
using namespace boost::property_tree;
using namespace sfge;
using namespace std;

PropertiesEditor::PropertiesEditor(QWidget *parent)
	: QTreeWidget(parent), mCurrentGOB(nullptr)
{
}

void PropertiesEditor::SetGame(Game *game)
{
	mGame = game;
	if (mGame == nullptr)
		return;

	const string &behaviourDescsPath = mGame->GetBehaviourDescsFolder();

	LogManager::getSingleton() << "Parsing Behaviour definitions from " << behaviourDescsPath << "\n";

	const QString qtBehaviourDescFolder(QString::fromLocal8Bit(behaviourDescsPath.c_str(), behaviourDescsPath.size()));
	QDir behaviourDescsDir(qtBehaviourDescFolder);
	QStringList descs = behaviourDescsDir.entryList(QStringList() << "*.json");
	Q_FOREACH(QString descFile, descs)
	{
		ParseBehaviourDesc(qtBehaviourDescFolder + '/' + descFile);
	}
}

void PropertiesEditor::ParseBehaviourDesc(QString filePath)
{
	LogManager &log = LogManager::getSingleton();

	const QByteArray baFilePath(filePath.toLocal8Bit());
	const string stdFilePath(baFilePath.data(), baFilePath.size());

	LogManager::getSingleton() << "Parsing " << stdFilePath << "\n";

	ptree desc;
	try
	{
		json_parser::read_json(stdFilePath, desc);
	}
	catch(const std::exception &e)
	{
		log << e.what() << "\n";
		return;
	}

	const string &fileType = desc.get("type", "");
	if (fileType != "behaviour_definition")
	{
		log	<< "'type' attribute is invalid. Expected 'behaviour_definition', got '"
			<< fileType << "'\n";
		return;
	}

	const string &name = desc.get("name", "");
	if (name.empty())
	{
		log	<< "'name' attribute is invalid (empty).\n";
		return;
	}

	// Parse parameters
	const ptree InvalidPtree;

	Attributes attributes;
	const ptree &paramTree = desc.get_child("params", InvalidPtree);
	for_each(paramTree.begin(), paramTree.end(),
		[&] (ptree::value_type param) { ParseBehaviourParam(param, attributes); } );

	mBehaviourData.insert(make_pair(QString::fromUtf8(name.c_str(), name.size()), attributes));
}

void PropertiesEditor::ParseBehaviourParam(const ptree::value_type &param, Attributes &storage)
{
	LogManager &log = LogManager::getSingleton();

	const ptree &paramDef = param.second;
	if (paramDef.empty())
	{
		log	<< "Found empty attribute definition.\n";
		return;
	}

	const string &paramName = paramDef.get("name", "");
	if (paramName.empty())
	{
		log	<< "No name attribute found.\n";
		return;
	}

	const string &paramType = paramDef.get("type", "");
	if (paramType.empty())
	{
		log	<< "No type attribute found.\n";
		return;
	}

	Attribute attr;
	attr.mName = QString::fromUtf8(paramName.c_str(), paramName.size());
	attr.mType = QString::fromUtf8(paramType.c_str(), paramType.size());

	storage.push_back(attr);
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
			QString name(QString::fromUtf8(gobEntry.first.c_str(), gobEntry.first.size()));
			QTreeWidgetItem *item = new QTreeWidgetItem(this, QStringList() << name);
			item->setBackgroundColor(0, Qt::darkGray);
			item->setBackgroundColor(1, Qt::darkGray);
			item->setTextColor(0, Qt::white);

			DisplayPropertiesFor(name, item);
		} );

	expandAll();
}

void PropertiesEditor::DisplayPropertiesFor(const QString &behaviourName, QTreeWidgetItem *behaviourNode)
{
	BehaviourData::const_iterator it = mBehaviourData.find(behaviourName);
	if (it == mBehaviourData.end())
		return;

	const Attributes &attributes = it->second;
	for_each(attributes.begin(), attributes.end(),
		[&] (const Attribute &attr)
		{
			QTreeWidgetItem *itemName = new QTreeWidgetItem(behaviourNode);
			itemName->setText(0, attr.mName);
			itemName->setText(1, attr.mType);
		} );
}
