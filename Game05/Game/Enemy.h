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

protected:

	//初期化
	void Init(Vector3 position, const EnemyStatus& status);

	EnemyStatus m_enemyStatus;

	Player* m_player = nullptr;

	void MoveToTarget(const Vector3&target);

	IEnemy() {};
	virtual ~IEnemy() {};

	void Die()override;

private:
};

class FireEnemy :public IEnemy 
{
public:
	void Init(Vector3 position);

protected:
	void UpdateAction()override;

private:

};


