#pragma once
#include "HpBar.h"

class Player;

class HpBarUI:public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	/**Gameからplayerを受け取る*/
	void SetPlayer(Player* player) { m_player = player; }

private:

	HpBar m_hpBar;
	/**MAXHPようのバー*/
	HpBar m_maxHpBar;
	Player* m_player = nullptr;

	int  m_initialMaxHp = 0;

};

