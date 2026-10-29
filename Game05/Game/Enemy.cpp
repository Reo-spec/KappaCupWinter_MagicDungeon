#include "stdafx.h"
#include "Enemy.h"

//ここは様々な種類を複数体作る予定だからここから移す
//一旦プロトタイプを急ぐためこの形
static constexpr int FIRE_ENEMY_HP = 300; //TODO(仕様未定)
static constexpr const char* FIRE_MODEL_PATH = "Assets/modelData/fireSlime.tkm";

void IEnemy::Init(Vector3 position, const char*modelPath, int hp, EnMagicType magicType)
{
	m_position = (position);
	m_modelRender.Init(modelPath);
	m_modelRender.SetPosition(m_position);
	m_characterController.Init(40.0f, 50.0f, position);
	m_baseStatus.maxHp = hp;
	m_baseStatus.hp = m_baseStatus.maxHp;
	m_enemyStatus.magicType=magicType;
}

void IEnemy::Die() 
{
	DeleteGO(this);
}

void FireEnemy::Init(Vector3 position) 
{
	
	IEnemy::Init(position, FIRE_MODEL_PATH, FIRE_ENEMY_HP, EnMagicType::Fire);

}

void FireEnemy::UpdateAction() 
{
	MoveAction();
}
