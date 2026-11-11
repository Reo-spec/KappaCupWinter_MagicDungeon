#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "GameCamera.h"
#include "Magic.h"
#include "MagicSelectUI.h"
#include "MagicManager.h"
#include "Enemy.h"

bool Game::Start()
{

	m_map = NewGO<Map>(0, "map");

	/**宝箱に魔法を渡すためにMAPを経由している*/
	m_map->SetMagicManager(&m_magicManager);
	
	m_player = NewGO<Player>(0, "player");

	/**プレイヤーが魔法を聞く*/
	m_player->SetMagicManager(&m_magicManager);

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_msUI = NewGO<MagicSelectUI>(0, "magicSelectUI");

	m_msUI->SetMagicManager(&m_magicManager);

	m_fireEnemy = NewGO<FireEnemy>(0, "fireEnemy");

	m_fireEnemy->Init(Vector3(800.0f, 0.0f, 700.0f));

	m_fireEnemy->SetPlayer(m_player);

	return true;
}

void Game::Update()
{
}

void Game::Render(RenderContext&rc)
{


}