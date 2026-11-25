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

struct FrostState 
{
	/**残りの凍り時間*/
	float remainingTime = 0.0f;
	/**速さの倍率,魔法を重ね掛けすると下がる*/
	float frozenTimeRate = 1.0f;
	/**凍りが溶けてから、倍率が1.0に戻るまでの残り時間*/
	float rateResetTimer = 0.0f;

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

	/**凍っている時間を数える*/
	void CountDownFrost();

	/**続いている魔法の効果を全部消す*/
	void ClearInfluence();

	/**スピードを低下の倍率を返す*/
	float GetSpeedMagnification()const;

	/**凍っているかどうかを返す*/
	bool IsFrozen()const;

	/**1回目に凍る時間を決めている、playerと敵に最初に私ている*/
	void SetBaseFrozenTime(const float baseFrozenTime) { m_baseFrozenTime = baseFrozenTime; }

private:

	/**燃焼状態*/
	BurnState m_burnState;

	/**凍り状態*/
	FrostState m_frostState;

	/**1回目に凍る時間、2回目以降はここに倍率を掛ける、死んでも変わらない*/
	float m_baseFrozenTime = 0.0f;
};

