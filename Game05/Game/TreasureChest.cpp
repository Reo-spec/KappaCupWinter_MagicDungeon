#include "stdafx.h"
#include "TreasureChest.h"
#include "Player.h"

//宝箱とプレイヤーの距離
static constexpr float OPEN_DISTANCE = 100.0f;//TODO仕様未定

bool TreasureChest::Start() 
{
	m_closeChestRender.Init("Assets/modelData/treasureChest.tkm");
	m_openChestRender.Init("Assets/modelData/treasureChestOpen.tkm");

	m_chestCollisionRender.Init("Assets/modelData/treasureChestCol.tkm");

	//宝箱のモデルのPositionを設定
	m_closeChestRender.SetPosition(m_position);
	m_openChestRender.SetPosition(m_position);

	//宝箱のRotationを設定
	m_closeChestRender.SetRotation(m_rotation);
	m_openChestRender.SetRotation(m_rotation);

	//宝箱の当たり判定の場所を設定する
	m_chestCollisionRender.SetPosition(m_position);
	m_chestCollisionRender.SetRotation(m_rotation);

	m_closeChestRender.Update();
	m_openChestRender.Update();

	m_chestCollisionRender.Update();

	m_chestCollision.CreateFromModel(m_chestCollisionRender.GetModel(), m_chestCollisionRender.GetModel().GetWorldMatrix());

	//仕方なくFindGOを採用βで変更の可能性もある
	m_player = FindGO<Player>("player");

	return true ;
}

void TreasureChest::SetPosition(const Vector3& position)
{
	m_position = position;
}

void TreasureChest::SetRotation(const Quaternion& rotation) 
{
	m_rotation = rotation;
}

void TreasureChest::SetContents(EnMagicType magicType) 
{
	m_magicType = magicType;
}


void TreasureChest::SetTorch() 
{
	m_torch = true;
}

void TreasureChest::Update() 
{
	if (m_player == nullptr) {
		return;
	}
	
	if (m_openChest == true) {
		return;
	}

	Vector3 target = m_player->GetPosition() - m_position;
	float diff = target.Length();

	if (diff < OPEN_DISTANCE && g_pad[0]->IsTrigger(enButtonA)) {
		m_openChest = true;

		if (m_torch == true) {
			K2_LOG("たいまつの宝箱を開けた\n");
		}
		else {
			K2_LOG("魔法を手に入れた:%d\n", static_cast<int>(m_magicType));
		}
	}

}

void TreasureChest::Render(RenderContext& rc) 
{

	if (m_openChest == true) {
		m_openChestRender.Draw(rc);
	}
	else {
		m_closeChestRender.Draw(rc);
	}
	
}