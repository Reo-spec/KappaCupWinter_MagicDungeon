#pragma once
#include "Character.h"
#include "Magic.h"

class Player;

enum class EnEnemyType :uint8_t
{
	Fire,
	Max
};

struct EnemyStatus 
{
	//敵のステータスをいれる
	EnMagicType magicType = EnMagicType::None;
	int maxHp = 0; 
	float moveSpeed = 0.0f;
	const char* modelPath = nullptr;
	float attackInterval = 0.0f;
	float attackRange = 0.0f;

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

	void MagicAttack();

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


