#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "GameCamera.h"
#include "Magic.h"
#include "MagicSelectUI.h"
#include "HpBarUI.h"
#include "MagicManager.h"
#include "Clear.h"

bool Game::Start()
{

	m_map = NewGO<Map>(0, "map");

	/**宝箱に魔法を渡すためにMAPを経由している*/
	m_map->SetMagicManager(&m_magicManager);

	m_player = NewGO<Player>(0, "player");

	/**敵を置くときに渡すため、Map に Player を渡す*/
	m_map->SetPlayer(m_player);

	/**プレイヤーが魔法を聞く*/
	m_player->SetMagicManager(&m_magicManager);

	m_player->SetMap(m_map);

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_msUI = NewGO<MagicSelectUI>(0, "magicSelectUI");

	m_msUI->SetMagicManager(&m_magicManager);

	/**HPばーを呼び出す*/
	m_hpBarUI = NewGO<HpBarUI>(0, "hpBarUI");
	m_hpBarUI->SetPlayer(m_player);

	/**デバッグGUI：魔法を持つ・持たないを切り替えるパネル（中身は DebugMagicPanel）*/
	m_debugMagicPanel.Init(&m_magicManager);

	return true;
}

void Game::Update()
{
	m_magicManager.CoolDownLimit();

	/**プレイヤーがゴールのマスに入ったかどうか*/
	if (m_map->IsGoalPosition(m_player->GetPosition()))
	{
		m_clear = NewGO<Clear>(0, "clear");
		DeleteGO(this);

		return;
	}
}

void Game::Render(RenderContext&rc)
{


}

Game::~Game() 
{
	/**飛んでいる魔法を消す*/
	const std::vector<AttackMagic*>& playerMagics = FindGOs<AttackMagic>("magic");
	for (int i = 0;i < playerMagics.size();i++) {
		DeleteGO(playerMagics[i]);
	}

	const std::vector<AttackMagic*>& enemyMagics = FindGOs<AttackMagic>("enemyMagic");
	for (int i = 0;i < enemyMagics.size();i++) {
		DeleteGO(enemyMagics[i]);
	}

	DeleteGO(m_map);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_msUI);
	DeleteGO(m_hpBarUI);
}
