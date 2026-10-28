#pragma once
#include "AttackValue.h"


/**
 * HPを持ち、ダメージや燃焼を受けるものの基底クラス
 * Player と敵はこのクラスを継承する
 */
class Character :public IGameObject
{
public:
	
	//基本ステータス
	struct BaseStatus
	{
		int hp = 0;
		
		int maxHp = 0;
	};

	//燃えている最中の状態
	struct BurnState 
	{

		//残りの燃える時間
		float remainingTime = 0.0f;
		//1回のダメージ
		AttackValue damage = 0;
		//ダメージをいれる間隔
		float damageInterval = 0.0f;
		//次のダメージまでの時間を数える
		float intervalTimer = 0.0f;

	};

public:
	Character();
	virtual ~Character();

	void Update()override final;

	//ダメージを受ける
	void Damage(const AttackValue damage);

	void SetStartFireDamage(const BurnState&burnState) {m_burnState = burnState;}

protected:

	virtual void UpdateAction();

	virtual void Die();

	BaseStatus m_baseStatus;
	BurnState m_burnState;

private:

	void UpdateBurnDamage();

};

