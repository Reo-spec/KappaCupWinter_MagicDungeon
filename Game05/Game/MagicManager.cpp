#include "stdafx.h"
#include "MagicManager.h"

MagicManager::MagicManager() 
{
	
	for (int i = 0;i < 3;i++)
	{
		m_magicSlot[i] = EnMagicType::None;
	}

	//クールダウンの残り時間を全部 0 にする（最初からすぐ撃てるように）
	for (int i = 0; i < static_cast<int>(EnMagicType::Max); i++)
	{
		m_coolDownTimer[i] = 0.0f;
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

void MagicManager::CoolDownLimit() 
{

	float deltaTime = g_gameTime->GetFrameDeltaTime();

	for (int i = 0; i < static_cast<int>(EnMagicType::Max);i++) {
		/**残り時間をフレーム分を減らす*/
		m_coolDownTimer[i] -= deltaTime;

		/**クールダウンの減少で0になったら止める*/
		if (m_coolDownTimer[i] <= 0.0f) {
			m_coolDownTimer[i] = 0.0f;
		}
	}
}

bool MagicManager::IsReady(EnMagicType magicType)const {

	/**その魔法の残り時間を取り出す*/
	float coolDownTimer = m_coolDownTimer[static_cast<int>(magicType)];

	/**残り時間が0以下なら撃てる*/
	return coolDownTimer <= 0.0f;
}


void MagicManager::UseMagic(EnMagicType magicType) {
	m_coolDownTimer[static_cast<int>(magicType)] = m_baseStatus[static_cast<int>(magicType)].m_maxCoolDown;
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