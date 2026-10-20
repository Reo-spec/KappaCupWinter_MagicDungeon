#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "GameCamera.h"

bool Game::Start()
{

	m_map = NewGO<Map>(0, "map");
	
	m_player = NewGO<Player>(0, "player");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	return true;
}

void Game::Update()
{
	
}

