#pragma once
#include "AttackValue.h"
#include "MagicInfluence.h"


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

	
public:
	Character();
	virtual ~Character();

	void Update()override final;

	//描画処理。
	void Render(RenderContext& rc)override;

	//ダメージを受ける
	void Damage(const AttackValue damage);

	Vector3 GetPosition()const { return m_position; }

	/**HPバーが取得する*/
	int GetHp()const { return m_baseStatus.hp; }
	int GetMaxHp()const { return m_baseStatus.maxHp; }

protected:

	virtual void UpdateAction();

	virtual void Die();

	void MoveAction();

	BaseStatus m_baseStatus;

	/**魔法が当たった後に続く効果*/
	MagicInfluence m_magicInfluence;

	Vector3 m_position;
	ModelRender m_modelRender;

	CharacterController m_characterController;  //キャラクターコントローラー。
	Vector3 m_moveSpeed;		//移動速度。
	Quaternion m_rotation;

	//魔法が当たったかの判定をする
	void CheckHitMagic(const char*magicName);

	/** 点滅を続ける残り時間 */
	float m_activeLimitTime = 0.0f;

	/**Renderがアクティブかどうかを判断している*/
	bool m_isActiveRender = true;

	/**前に入れ替えてからの時間*/
	float m_activeTime = 0.0f;

	/**魔法を撃って攻撃するか*/
	bool m_isMagicAttack = false;

private:

	void ChangeActiveRender();

};

