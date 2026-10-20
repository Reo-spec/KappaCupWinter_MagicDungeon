#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Map;
class GameCamera;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	//void Render(RenderContext& rc);

private:
	
	Vector3 m_pos;
	Map* m_map;
	Player* m_player;
	GameCamera* m_gameCamera;

};

