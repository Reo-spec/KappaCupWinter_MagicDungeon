#pragma once

#include "Level3DRender/LevelRender.h"
/**本体を持たせるため前方宣言では足りない*/
#include "MagicManager.h"

class Player;
class Map;
class GameCamera;
class FireEnemy;
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
	FireEnemy* m_fireEnemy = nullptr;
	GameCamera* m_gameCamera=nullptr;
	MagicSelectUI* m_msUI=nullptr;

	MagicManager m_magicManager;

	/**デバッグGUIの魔法のパネル（F1 → メニューの Game → Magic で開く）*/
	DebugGuiPanel m_debugMagicPanel;
};

