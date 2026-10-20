#pragma once

class Map :public IGameObject
{
public:
	Map();
	~Map();

	void Render(RenderContext& rc);
private:
	ModelRender mapModelRender;
	PhysicsStaticObject physicsStaticObject;
};

