#pragma once
#include "AttackValue.h"
#include "Magic.h"

//燃えている最中の状態
struct BurnState
{

	/**残りの燃える時間*/
	float remainingTime = 0.0f;
	/**1回のダメージ*/
	AttackValue damage = 0;
	/**ダメージをいれる間隔*/
	float damageInterval = 0.0f;
	/**次のダメージまでの時間を数える*/
	float intervalTimer = 0.0f;

};

/**
魔法が当たった後に続く効果を持つクラス
Characterがメンバで1つ持つHPはこちらでは変えない*/
class MagicInfluence
{
public:

	/**魔法が当たったときに、その種類にあった効果を出す*/
	void StartInfluence(const EnMagicType magicType);

	/**燃焼の時間を数えて、このフレームに受けるダメージを返す*/
	AttackValue CountDownBurn();

	/**続いている魔法の効果を全部消す*/
	void ClearInfluence();

private:

	/**燃焼状態*/
	BurnState m_burnState;
};

