#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

static constexpr EnemyStatus FIRE_ENEMY_STATUS =
{
	EnMagicType::Fire,
	300,// TODO(仕様未定)
	120.0f,// TODO(仕様未定)
	"Assets/modelData/fireSlime.tkm",
	3.0f,//TODO(仕様未定)
	170.0f//TODO(仕様未定)
};


void IEnemy::Init(Vector3 position,const EnemyStatus&status)
{
	m_enemyStatus = status;
	m_position = position;
	m_modelRender.Init(m_enemyStatus.modelPath);
	m_modelRender.SetPosition(m_position);
	m_characterController.Init(40.0f, 50.0f, position);
	m_baseStatus.maxHp = m_enemyStatus.maxHp;
	m_baseStatus.hp = m_baseStatus.maxHp;
}

void IEnemy::Die() 
{
	DeleteGO(this);
}

//最初はプレイヤーに向かって歩くだけ
//だがあとから改良できるようにTargetになっている
void IEnemy::MoveToTarget(const Vector3& target) 
{
	Vector3 diff = target - m_position;
	diff.y = 0.0f;

	if (diff.Length() <= 165.0f) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z= 0.0f;
		return;
	}

	diff.Normalize();
	m_moveSpeed.x = m_enemyStatus.moveSpeed * diff.x;
	m_moveSpeed.z = m_enemyStatus.moveSpeed * diff.z;

	//キャラクターの方向を変える。
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	//回転を伝える。
	m_modelRender.SetRotation(m_rotation);
	
}

void IEnemy::SetMagicStatusAndPath(const AttackMagicStatus& status, const char* modelPath) 
{
	/**魔法のステータスとファイルパスをコピーして渡す*/
	m_attackMagicStatus = status;
	m_modelPath = modelPath;
}

void FireEnemy::Init(Vector3 position) 
{
	IEnemy::Init(position,FIRE_ENEMY_STATUS);

}

void FireEnemy::UpdateAction() 
{
	MoveAction();

	//毎フレーム魔法にあったっているかをとっている
	CheckHitMagic("magic");

	//プレイヤーが渡されていなかったら動かない
	if (m_player == nullptr) {
		return;
	}

	MoveToTarget(m_player->GetPosition());

	float deltaTime = g_gameTime->GetFrameDeltaTime();

	m_nextAttackLimit -= deltaTime;

	Vector3 diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f;

	if (diff.Length() <= m_enemyStatus.attackRange &&m_nextAttackLimit <= 0.0f) {
		MagicAttack();
		m_nextAttackLimit = m_enemyStatus.attackInterval;
	}
}

void IEnemy::MagicAttack() 
{
	if (m_modelPath == nullptr) {
		return;
	}

	//向いてる方向をとる
	Vector3 diff = m_player->GetPosition()-m_position;
	diff.y = 0.0f;

	diff.Normalize();

	Vector3 magicPos = m_position + diff * 50.0f;
	magicPos.y += 100.0f;

	//魔法の種類ごとにモデルとステータスを決める
	const char* modelPath = m_modelPath;
	AttackMagicStatus status = m_attackMagicStatus;

	AttackMagic* magic = NewGO<AttackMagic>(0, "enemyMagic");

	if (magic == nullptr) {
		return;
	}
	magic->Init(modelPath, status);
	magic->SetPositionAndDirection(magicPos, diff);

}
