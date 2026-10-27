#include "stdafx.h"
#include "Character.h"

Character::Character() 
{
}

Character::~Character() 
{
}

void Character::Update() 
{
	//燃えるダメージの処理
	UpdateBurnDamage();
	//子の行動を更新する
	UpdateAction();
}

void Character::Damage(const AttackValue damage)
{
	if (m_baseStatus.hp<=0) {
		return;
	}

	m_baseStatus.hp -= damage;

	if (m_baseStatus.hp <= 0) {
		m_baseStatus.hp = 0;
		Die();
	}
}

void Character::UpdateAction() 
{
	// 何もしない。行動の中身は子（Player など）の UpdateAction に書く
	//TODO Player側のUpdateをUpdateActionに書き換える
}

//継続ダメージを食らう処理
void Character::UpdateBurnDamage() 
{
	if (m_burnState.remainingTime <= 0) 
	{
		return;
	}

	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	m_burnState.remainingTime -= deltaTime;
	m_burnState.intervalTimer += deltaTime;

	if (m_burnState.intervalTimer >= m_burnState.damageInterval) 
	{
		Damage(m_burnState.damage);

		m_burnState.intervalTimer = 0.0f;
	}
	
}

void Character::Die() 
{
}