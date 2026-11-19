#pragma once
#include "Character.h"
#include "Magic.h"
#include "HpBar.h"

class Player;

enum class EnEnemyType :uint8_t
{
	Fire,
	Max
};

/**castする回数を減らすため
	なぜcastする回数が減るかというと勝手にintに変えているから*/
enum EnEnemyAnimationClip {		/**アニメーション。*/
	enEnemyAnimationClip_Idle,
	enEnemyAnimationClip_Walk,
	enEnemyAnimationClip_Attack,
	enEnemyAnimationClip_Die,
	enEnemyAnimationClip_Num,
};

struct EnemyStatus 
{
	//敵のステータスをいれる
	EnMagicType magicType = EnMagicType::None;
	int maxHp = 0; 
	float moveSpeed = 0.0f;
	const char* modelPath = nullptr;
	float attackInterval = 0.0f;
	/**敵が攻撃してくる距離*/
	float attackRange = 0.0f;
	float chaseRange = 0.0f;
	/**animationのパスをいれる*/
	const char* animationPath[enEnemyAnimationClip_Num]{};
	
};

/**
*これは敵の
* 基底クラス
* 親クラスはCharacter
* このクラスは全ての敵に共通する
*/
class IEnemy : public Character
{
public:

	void SetPlayer(Player* player) { m_player = player; }

	/**炎の魔法のステータスとファイルパスをコピーしていれている*/
	void SetMagicStatusAndPath(const AttackMagicStatus& status, const char* modelPath);

	void SetMap(const Map* map) { m_map = map; }

	/**HpBarから持ってきたやつを使えるように*/
	void Render(RenderContext& rc)override;

protected:

	//初期化
	void Init(Vector3 position, const EnemyStatus& status);

	EnemyStatus m_enemyStatus;

	Player* m_player = nullptr;

	/**敵が魔法を打つためのステータス*/
	AttackMagicStatus m_attackMagicStatus;

	/**敵が撃つ魔法のモデルパス*/
	const char* m_modelPath = nullptr;

	void MoveToTarget(const Vector3&target);

	IEnemy() {};
	virtual ~IEnemy() {};

	void Die()override;

	float m_nextAttackLimit = 7.0f;

	/**animationをいれる箱*/
	AnimationClip m_animationClips[enEnemyAnimationClip_Num];		/**アニメーションクリップ。*/

	/**敵のアニメーションを管理*/
	void ManageEnemyState();

	/**魔法で攻撃する*/
	void MagicAttack();

	/**魔法を撃つ準備(作業分け)*/
	void ReadyMagic();

	/**魔法とアニメーションの差を減らす関数*/
	void CountDownMagicShot();

	/**死んだときの処理を受け持つ関数(作業分け)
	{やられのアニメーションを再生して、終わったら消す}*/
	void CountDownDie();

	/**敵のHPバーを動かす*/
	void UpdateHpBar();

	/**頭の上のHPバー*/
	HpBar m_hpBar;

	/**HPバーを見せるか（カメラの後ろ・遠くの敵は見せない）*/
	bool m_isHpBarVisible = false;

	/**敵が追いかけるかどうか*/
	bool m_isChase = false;

	int m_enemyState = 0;

	/**敵が生きているかどうか*/
	bool m_isAlive = true;

	/**アニメーションをステートで振り分ける*/
	void PlayAnimation();

	/**魔法を出すまで残りの時間*/
	float m_magicTimer = 0.0f;

	/**もう魔法を出したか*/
	bool m_isShotDone = false;

private:

	const Map* m_map = nullptr;

};

class FireEnemy :public IEnemy 
{
public:
	void Init(Vector3 position);

protected:
	void UpdateAction()override;

private:

};


