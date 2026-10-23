#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Map;
class GameCamera;
//仮実装UIManagerが出来次第移動
class MagicSelectUI;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	
	Vector3 m_pos;
	Map* m_map=nullptr;
	Player* m_player=nullptr;
	GameCamera* m_gameCamera=nullptr;
	MagicSelectUI* m_msUI=nullptr;
};

