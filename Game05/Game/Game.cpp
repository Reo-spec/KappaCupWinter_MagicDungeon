#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "GameCamera.h"
#include "Magic.h"
#include "MagicSelectUI.h"

bool Game::Start()
{

	m_map = NewGO<Map>(0, "map");
	
	m_player = NewGO<Player>(0, "player");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_msUI = NewGO<MagicSelectUI>(0, "magicSelectUI");

	AttackMagicPoolManager::Init();
	AttackMagicPoolManager::Get().Setup();

	return true;
}

void Game::Update()
{
	AttackMagicPoolManager::Get().Update();
}

void Game::Render(RenderContext&rc)
{
	AttackMagicPoolManager::Get().Render(rc);
}