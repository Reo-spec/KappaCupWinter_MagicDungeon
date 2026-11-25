#include "stdafx.h"
#include "Character.h"
#include "Magic.h"

static constexpr float ACTIVE_TIME = 0.1f;//TODO(仕様未定)
static constexpr float DAMAGE_BLINK_TIME = 1.0f;//TODO(仕様未定)


Character::Character() 
{
}

Character::~Character() 
{
}

void Character::Update() 
{
	/**燃焼など、続く効果のダメージを受ける
	魔法で炎以外でも後遺ダメージがあればここを変える*/
	const AttackValue influenceDamage = m_magicInfluence.CountDownBurn();
	if (influenceDamage > 0) {
		Damage(influenceDamage);
	}
	/**凍り状態の処理*/
	m_magicInfluence.CountDownFrost();

	//子の行動を更新する
	UpdateAction();
	/**点滅表示に使用する関数*/
	ChangeActiveRender();

	//絵描きの更新処理。
	m_modelRender.Update();

}

void Character::Damage(const AttackValue damage)
{

	if (m_baseStatus.hp<=0) {
		return;
	}

	m_activeLimitTime = DAMAGE_BLINK_TIME;
	m_activeTime = 0.0f;

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

void Character::MoveAction() 
{
	//重力を発生させる。
	m_moveSpeed.y -= 23.0f;

	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	if (m_characterController.IsOnGround()) {
		m_moveSpeed.y = 0.0f;
	}

	/**凍った時とそうでないときの移動速度を変えるためにスピードをコピーしている*/
	Vector3 frozenMoveSpeed = m_moveSpeed;
	/*低下倍率を聞く**/
	const float frozenMagnification =  m_magicInfluence.GetSpeedMagnification();

	frozenMoveSpeed.x *= frozenMagnification;
	frozenMoveSpeed.z *= frozenMagnification;

	/**凍った時の移動速度*/ //キャラクターコントローラーを使って座標を移動させる。
	m_position = m_characterController.Execute(frozenMoveSpeed, deltaTime);

	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Character::Die() 
{
}

void Character::Render(RenderContext& rc) {

	if (m_isActiveRender) {
		m_modelRender.Draw(rc);
	}
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

		/**魔法の処理を渡す*/
		m_magicInfluence.StartInfluence(magic->GetMagicType());

		Damage(magic->GetAttackValue());
		magic->PlayHitEffect();
		DeleteGO(magic);

		return;

	}

}

void Character::ChangeActiveRender() 
{
	if (m_activeLimitTime <= 0) {
		return;
	}

	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	m_activeLimitTime -= deltaTime;

	m_activeTime += deltaTime;

	if (m_activeLimitTime <= 0) {
		m_isActiveRender = true;

		return;
	}

	if (m_activeLimitTime >= ACTIVE_TIME)
	{
		m_isActiveRender = !m_isActiveRender;

		m_activeTime = 0.0f;
	}
}
