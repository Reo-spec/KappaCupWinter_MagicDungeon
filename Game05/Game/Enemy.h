#pragma once
#include "Character.h"
#include "Magic.h"

enum class EnEnemyType :uint8_t
{
	Fire,
	Max
};

struct EnemyStatus 
{
	//敵のステータスをいれる
	EnMagicType magicType = EnMagicType::None;
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

protected:

	//初期化
	void Init(Vector3 position,const char*modelPath,int hp,EnMagicType magicType);

	EnemyStatus m_enemyStatus;

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

};


