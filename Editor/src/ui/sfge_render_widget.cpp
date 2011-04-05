#include "sfge_render_widget.hpp"

#include <QtGui/QPainter>
#include <QtGui/QBrush>

#include <sfge/graphics/graphic_system.hpp>
#include <sfge/infrastructure/data_store.hpp>

#include <sstream>

#include <boost/property_tree/json_parser.hpp>

using namespace sfge;
//using namespace sf;
using namespace std;
using namespace boost::property_tree;

SFGERenderWidget::SFGERenderWidget(QWidget *parent)
	: QWidget(parent), mSFGEInitialized(false)
{
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoBackground);
}

void SFGERenderWidget::OnEndSystemInit()
{
	GraphicSystem::InitParams initParams;
	initParams.mHandle		= winId();
	initParams.mMode.Width	= width();
	initParams.mMode.Height	= height();

	GraphicSystem::getSingleton().Create(initParams);
}

void SFGERenderWidget::InitSFGE()
{
	try
	{
		Game::Init();

		const std::string renderJsonParams(
			"{\"shape\": \"circle\","
			"\"center\": [50, 50],"
			"\"radius\": 25,"
			"\"color\": [255, 0, 255]}");
	
		// Setup some parameters
		Parameters refObjDrawableDef;
		json_parser::read_json(istringstream(renderJsonParams), refObjDrawableDef);

		// Declare the 2 gameobject definitions we need
		DataStore &ds = DataStore::getSingleton();

		ds.DeclareGameObjectDef("ControllableThing");

		// Create the links between gameobject definitions and registered behaviours (eventually settings some default params)
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "TransformBehaviour");
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "RenderShapeBehaviour",	refObjDrawableDef);

		GameObjectPtr refGO = ds.InstantiateGameObjectDef("ControllableThing");
		mObjects.push_back(refGO);

		ds.InitializeInstances();
	}
	catch(const exception &e)
	{
		qDebug(e.what());
	}
}

QPaintEngine* SFGERenderWidget::paintEngine() const
{
	return nullptr;
}

void SFGERenderWidget::paintEvent(QPaintEvent *)
{
	if (!mSFGEInitialized)
	{
		InitSFGE();
		mSFGEInitialized = true;
	}

	Game::ProcessOneFrame();
}
