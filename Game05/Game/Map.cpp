#include "stdafx.h"
#include "Map.h"
Map::Map() 
{
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	mapModelRender.Init("Assets/modelData/kariMap.tkm");

	physicsStaticObject.CreateFromModel(mapModelRender.GetModel(), mapModelRender.GetModel().GetWorldMatrix());
}

Map::~Map()
{
}

void Map::Render(RenderContext& rc) 
{
	mapModelRender.Draw(rc);
}