#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "GameCamera.h"
#include "Magic.h"
#include "MagicSelectUI.h"
#include "Enemy.h"

bool Game::Start()
{

	m_map = NewGO<Map>(0, "map");
	
	m_player = NewGO<Player>(0, "player");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_msUI = NewGO<MagicSelectUI>(0, "magicSelectUI");

	//Playerが打つ魔法をUIに聞けるようにUIを渡す
	m_player->SetUI(m_msUI);

	m_fireEnemy = NewGO<FireEnemy>(0, "fireEnemy");

	m_fireEnemy->Init(Vector3(800.0f, 0.0f, 700.0f));

	return true;
}

void Game::Update()
{
}

void Game::Render(RenderContext&rc)
{


}