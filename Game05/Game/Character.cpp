#include "stdafx.h"
#include "Character.h"
#include "Magic.h"

static constexpr int ONCE_FIRE_DAMAGE = 5;//TODO(仕様未定)
static constexpr float BURN_DAMAGE_INTERVAL = 3.0f;//TODO(仕様未定)
static constexpr float BURN_REMAINING_TIME = 6.0f;//TODO(仕様未定)


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

	//絵描きの更新処理。
	m_modelRender.Update();

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

void Character::MoveAction() 
{
	//重力を発生させる。
	m_moveSpeed.y -= 23.0f;

	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	if (m_characterController.IsOnGround()) {
		m_moveSpeed.y = 0.0f;
	}

	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed, deltaTime);

	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Character::Die() 
{
}

void Character::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}

//魔法に当たっているかを確認する
void Character::CheckHitMagic(const char* magicName)
{
	//とりあえずFindGOsで魔法を探す
	//配列を参照で渡している

	/**オーナーを持たせる*/
	//FindGOsを使わずにプレイヤーに配列を持たせてそれで球を打ったときに
	//プレイヤーの持ちものにすることで綺麗になる
	/**エラーの温床*/
	const std::vector<AttackMagic*>&magics=FindGOs<AttackMagic>(magicName);
	//魔法を1つづ取り出して確認している
	for (AttackMagic* magic : magics)
	{
		if (magic->GetCollision()->IsHit(m_characterController) == false) {
			continue;
		}

		if (magic->GetMagicType() == EnMagicType::Fire)
		{
			BurnState burnState;

			burnState.remainingTime = BURN_REMAINING_TIME;
			burnState.damage = ONCE_FIRE_DAMAGE;
			burnState.damageInterval = BURN_DAMAGE_INTERVAL;

			SetStartFireDamage(burnState);
		}

		Damage(magic->GetAttackValue());
		DeleteGO(magic);

		return;

	}

}
