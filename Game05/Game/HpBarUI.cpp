#include "stdafx.h"
#include "HpBarUI.h"
#include "Player.h"

/**このクラスはプレイヤーのHPが表示される*/
static const Vector3 HP_BAR_POSITION = Vector3(-900.0f, 480.0f, 0.0f);
static const float HP_BAR_WIDTH = 400.0f;
static const float HP_BAR_HEIGHT = 30.0f;

bool HpBarUI::Start() 
{

	m_maxHpBar.Init(HP_BAR_WIDTH, HP_BAR_HEIGHT, Vector4(0.3f, 0.3f, 0.3f, 1.0f));
	m_maxHpBar.SetPosition(HP_BAR_POSITION);

	/**HPバーの色を緑にしている*/
	m_hpBar.Init(HP_BAR_WIDTH, HP_BAR_HEIGHT, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

	m_hpBar.SetPosition(HP_BAR_POSITION);

	return true;

}

void HpBarUI::Update() 
{
	if (m_player == nullptr) {
		return;
	}

	int hp = m_player->GetHp();
	int maxHp = m_player->GetMaxHp();

	if (m_initialMaxHp == 0) {
		m_initialMaxHp = maxHp;
	}

	/**最大HPが0だと0で割ってしまうから何もしない*/
	if (m_initialMaxHp <= 0) {
		return;
	}

	//後ろの灰色：今の最大HP ÷ 最初の最大HP（死ぬたびに短くなる）
	float maxHpRatio = static_cast<float>(maxHp) / static_cast<float>(m_initialMaxHp);

	/**補完の割合を求めている*/
	float ratio = static_cast<float>(hp) / static_cast<float>(m_initialMaxHp);

	m_maxHpBar.SetRatio(maxHpRatio);
	m_hpBar.SetRatio(ratio);

}

void HpBarUI::Render(RenderContext& rc) 
{
	m_maxHpBar.Render(rc);
	m_hpBar.Render(rc);
}
