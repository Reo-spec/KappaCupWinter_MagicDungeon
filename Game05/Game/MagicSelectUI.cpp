#include "stdafx.h"
#include "MagicSelectUI.h"
#include "Magic.h"
#include "MagicManager.h"
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

	m_magicIconSprites[static_cast<int>(EnMagicType::Stone)].Init("Assets/MagicIcon/Rock.dds", 64.0f, 64.0f);
	
	m_magicIconSprites[static_cast<int>(EnMagicType::Fire)].Init("Assets/MagicIcon/FireIcon_circle.dds", 64.0f, 64.0f);
	
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

		//スロット i に入っている魔法を MagicManager に聞く
		EnMagicType magicType = m_magicManager->GetNumberISlot(i);

		//空欄のスロットは読み込まないので計算しない
		if (magicType == EnMagicType::None) {
			continue;
		}

		//120度ずつスロットを回転させる
		float slotAngle = m_currentAngle + (i * ONE_THIRD_CIRCLE);

		//円周上の座標を算出
		Vector3 pos;
		pos.x = m_centerPosition.x + m_radius * cosf(slotAngle);
		pos.y = m_centerPosition.y + m_radius * sinf(slotAngle);
		pos.z = m_centerPosition.z;

		m_magicIconSprites[static_cast<int>(magicType)].SetPosition(pos);
		m_magicIconSprites[static_cast<int>(magicType)].Update();
	}
}

void MagicSelectUI::Render(RenderContext& rc)
{
	m_baseSpriteRender.Draw(rc);

	for (int i = 0;i < 3;i++) {

		EnMagicType magicType = m_magicManager->GetNumberISlot(i);

		if (magicType == EnMagicType::None) {
			continue;
		}

		m_magicIconSprites[static_cast<int>(magicType)].Draw(rc);
	}
}

void MagicSelectUI::RotateLeft() 
{
	m_targetAngle += ONE_THIRD_CIRCLE;
	/**ゲッターがManagerに聞く->計算する->セッターが渡すという作りになっている*/
	m_magicManager->SetSelectedSlot((m_magicManager->GetSelectedSlot() + 2) % 3);
}

void MagicSelectUI::RotateRight()
{
	m_targetAngle -= ONE_THIRD_CIRCLE;
	m_magicManager->SetSelectedSlot((m_magicManager->GetSelectedSlot() + 1) % 3);
}