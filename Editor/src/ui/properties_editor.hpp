#ifndef SFGE_EDITOR_PROPERTIES_EDITOR_HPP
#define SFGE_EDITOR_PROPERTIES_EDITOR_HPP

#include <QtGui/QTreeWidget>

#include <map>
#include <vector>

#include <sfge/infrastructure/game.hpp>

#include <boost/property_tree/ptree.hpp>

#include "ui_types.hpp"

class PropertiesEditor : public QTreeWidget
{
	Q_OBJECT

public:
	PropertiesEditor(QWidget *parent);

	void SetGame(sfge::Game *game);

public slots:
	void OnCurrentGameObjectChanged(GameObjectBehaviours *newGOB);

private:
	struct Attribute
	{
		QString mName;
		QString mType;
	};

	typedef std::vector<Attribute>				Attributes;
	typedef std::map<QString, Attributes>		BehaviourData;

private:
	void ParseBehaviourDesc(QString filePath);
	void ParseBehaviourParam(const boost::property_tree::ptree::value_type &param, Attributes &storage);
	
	void DisplayPropertiesFor(const QString &behaviourName, QTreeWidgetItem *behaviourNode);

private:
	GameObjectBehaviours*	mCurrentGOB;
	sfge::Game*				mGame;

	BehaviourData			mBehaviourData;
};

#endif
