#include "stdafx.h"
#include "MagicManager.h"

MagicManager::MagicManager() 
{
	
	for (int i = 0;i < 3;i++)
	{
		m_magicSlot[i] = EnMagicType::None;
	}

	//石の魔法のステータス
	//TODO(仕様未定) 石の数値
	m_modelPath[static_cast<int>(EnMagicType::Stone)] = "Assets/modelData/kariFireMagic.tkm";
	m_baseStatus[static_cast<int>(EnMagicType::Stone)].m_magicType = EnMagicType::Stone;
	m_baseStatus[static_cast<int>(EnMagicType::Stone)].m_moveSpeed = 500.0f;
	m_baseStatus[static_cast<int>(EnMagicType::Stone)].m_maxCoolDown = 3.0f;
	m_baseStatus[static_cast<int>(EnMagicType::Stone)].m_maxLifeTime = 3.0f;
	m_baseStatus[static_cast<int>(EnMagicType::Stone)].m_attackValue = 30;

	//炎の魔法のステータス
	// TODO(仕様未定) 炎の数値
	m_modelPath[static_cast<int>(EnMagicType::Fire)] = "Assets/modelData/kariFireMagic.tkm";
	m_baseStatus[static_cast<int>(EnMagicType::Fire)].m_magicType = EnMagicType::Fire;
	m_baseStatus[static_cast<int>(EnMagicType::Fire)].m_moveSpeed = 1000.0f;
	m_baseStatus[static_cast<int>(EnMagicType::Fire)].m_maxCoolDown = 3.0f;
	m_baseStatus[static_cast<int>(EnMagicType::Fire)].m_maxLifeTime = 3.0f;
	m_baseStatus[static_cast<int>(EnMagicType::Fire)].m_attackValue = 50;

}

//空いている１番前のスロットを探して一覧にいれる
void MagicManager::AddMagic(EnMagicType magicType) 
{
	m_magicTypes.push_back(magicType);

	for (int i = 0;i < 3;i++) 
	{
		if (m_magicSlot[i] == EnMagicType::None) 
		{
			//もらった魔法(引数)を入れる
			m_magicSlot[i] = magicType;

			return;
		}
	}

}

//β版に実装予定の魔法のレベル用に個数を数えている関数
int MagicManager::CountMagic(EnMagicType magicType)const 
{
	/**ここの関数のイメージは一旦前部データをいれてそこから全部見て何個入っているかを判断する関数*/

	int LevelCount = 0;

	for (int i = 0;i < m_magicTypes.size();i++) 
	{
		if (m_magicTypes[i] == magicType)
		{
			LevelCount++;
		}
	}

	return LevelCount;
}