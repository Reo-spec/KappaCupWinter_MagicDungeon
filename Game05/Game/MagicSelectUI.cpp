#include "stdafx.h"
#include "MagicSelectUI.h"
#include "Magic.h"
#include <cmath>

//Mathの方が安定するそして他のプラットフォームでも使える
static constexpr float ONE_THIRD_CIRCLE = Math::PI2 / 3.0f; // 120度（ラジアン）


MagicSelectUI::MagicSelectUI()
{
}

MagicSelectUI::~MagicSelectUI()
{
}

bool MagicSelectUI::Start()
{
	m_baseSpriteRender.Init("Assets/MagicIcon/BaseMagicCircle.dds", 270.0f, 270.0f);
	m_baseSpriteRender.SetPosition(m_centerPosition);
	m_baseSpriteRender.Update();

	m_slotSprites[0].Init("Assets/MagicIcon/Rock.dds", 64.0f, 64.0f);
	m_magicTypeSlot[0] = EnMagicType::Stone;

	m_slotSprites[1].Init("Assets/MagicIcon/FireIcon_circle.dds", 64.0f, 64.0f);
	m_magicTypeSlot[1] = EnMagicType::Fire;

	//m_slotSprites[2].Init("Assets/MagicIcon/Ice_circle.dds", 64.0f, 64.0f);
	m_magicTypeSlot[2] = EnMagicType::None;
	
	return true;

}

void MagicSelectUI::Update() 
{

	//回転の入力を受け付ける
	//変更したいと思う時の例(入力動作を全てひとまとめにしたいと思うなど)
	if (g_pad[0]->IsTrigger(enButtonLB1)) {
		RotateLeft();
	}
	else if (g_pad[0]->IsTrigger(enButtonRB1)) {
		RotateRight();
	}

	//イージング補完。動きを滑らかに
	m_currentAngle += (m_targetAngle - m_currentAngle) * 0.15f;

	float baseRotation = m_currentAngle - 1.5708f;

	m_baseSpriteRender.SetPosition(m_centerPosition);

	Quaternion rot;
	rot.SetRotation(Vector3::AxisZ, baseRotation);
	m_baseSpriteRender.SetRotation(rot);

	m_baseSpriteRender.Update(); // ★追加

	//各スロットの三角関数出の座標計算
	for (int i = 0;i < 3;i++) {

		//空欄のスロットは読み込まないので計算しない
		if (m_magicTypeSlot[i] == EnMagicType::None) {
			continue;
		}

		//120度ずつスロットを回転させる
		float slotAngle = m_currentAngle + (i * ONE_THIRD_CIRCLE);

		//円周上の座標を算出
		Vector3 pos;
		pos.x = m_centerPosition.x + m_radius * cosf(slotAngle);
		pos.y = m_centerPosition.y + m_radius * sinf(slotAngle);
		pos.z = m_centerPosition.z;

		m_slotSprites[i].SetPosition(pos);
		m_slotSprites[i].Update();
	}
}

void MagicSelectUI::Render(RenderContext& rc)
{
	m_baseSpriteRender.Draw(rc);

	for (int i = 0;i < 3;i++) {

		if (m_magicTypeSlot[i] == EnMagicType::None) {
			continue;
		}

		m_slotSprites[i].Draw(rc);
	}
}

void MagicSelectUI::RotateLeft() 
{
	m_targetAngle += ONE_THIRD_CIRCLE;
	m_selectedSlot = (m_selectedSlot + 2) % 3;
}

void MagicSelectUI::RotateRight()
{
	m_targetAngle -= ONE_THIRD_CIRCLE;
	m_selectedSlot = (m_selectedSlot + 1) % 3;
}