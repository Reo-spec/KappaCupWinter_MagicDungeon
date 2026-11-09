#include "stdafx.h"
#include "TreasureChest.h"
#include "Player.h"

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

}

void TreasureChest::Render(RenderContext& rc) 
{
	m_closeChestRender.Draw(rc);
}