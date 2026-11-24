#include "stdafx.h"
#include "Magic.h"
#include "Map.h"

static constexpr float MAGIC_COLLISION_RADIUS = 25.0f;//TODO(仕様未定)
static const Vector3 MAGIC_COLLISION_OFFSET = Vector3(0.0f,25.0f,0.0f);
static const float MAGIC_EFFECT_SCALE = 50.0f;//TODO(仕様未定)

AttackMagic::~AttackMagic() 
{
	//魔法の当たり判定とステータスは勝手に消えないから消している
	DeleteGO(m_collision);

	/**ループのエフェクトは自分で止まらないから止めている*/
	if (m_effect != nullptr) {
		m_effect->Stop();
		m_effect = nullptr;
	}

	delete As();
}

bool AttackMagic::Start()
{
	/** 位置と向きは Init のあとの SetPositionAndDirection で入るので、再生はここで始める */
	if (m_effect != nullptr) {
		Quaternion rotation;
		rotation.SetRotationYFromDirectionXZ(m_direction);
		m_effect->SetRotation(rotation);
		m_effect->SetPosition(m_position + MAGIC_COLLISION_OFFSET);
		m_effect->Play();
	}

	return true;
}


void AttackMagic::Update()
{
	// TODO: ここで移動処理などを書く
	Move();

	/**当たり判定の中心と、エフェクトの中心を揃える*/
	const Vector3 centerPosition = m_position + MAGIC_COLLISION_OFFSET;

	if (m_effect != nullptr) {
		m_effect->SetPosition(centerPosition);
	}
	else {
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
	}

	m_collision->SetPosition(m_position + MAGIC_COLLISION_OFFSET);

	//一定時間経ったら、何にも当たらず消える。

	float deltaTime = g_gameTime->GetFrameDeltaTime();

	As()->m_lifeTime += deltaTime;

	if (As()->m_lifeTime >= As()->m_maxLifeTime)
	{
		DeleteGO(this);
		return;
	}

	/**壁と当たったら魔法が消える*/
	if (CheckHitWallCollision()) {
		PlayHitEffect();
		DeleteGO(this);
		return;
	}

}



void AttackMagic::Render(RenderContext& rc)
{
	/**エフェクトがない時だけこっちで書く*/
	if (m_effect == nullptr) {
		m_modelRender.Draw(rc);
	}
}


void AttackMagic::Init(const char* modelPath, const AttackMagicStatus& status)
{
	//魔法の当たり判定を作成している
	m_collision = NewGO<CollisionObject>(0, "collision");
	m_collision->CreateSphere(m_position, Quaternion::Identity, MAGIC_COLLISION_RADIUS);
	m_collision->SetIsEnableAutoDelete(false);

	if (modelPath == nullptr) {
		m_effect = NewGO<EffectEmitter>(0);
		m_effect->Init(GetMagicEffectNumber(status.m_magicType));
		m_effect->SetScale(Vector3(MAGIC_EFFECT_SCALE, MAGIC_EFFECT_SCALE, MAGIC_EFFECT_SCALE));
	}
	else {
		//ModelPathを持ってくる
		m_modelRender.Init(modelPath);

	}

	m_status = new AttackMagicStatus(status);
}

void AttackMagic::PlayHitEffect() 
{
	/**エフェクトが無ければスルー*/
	if (m_effect == nullptr) {
		return;
	}

	EffectEmitter* hitEffect = NewGO<EffectEmitter>(0);
	hitEffect->Init(GetMagicHitEffectNumber(As()->m_magicType));
	hitEffect->SetScale(Vector3(MAGIC_EFFECT_SCALE, MAGIC_EFFECT_SCALE, MAGIC_EFFECT_SCALE));
	hitEffect->SetPosition(m_position + MAGIC_COLLISION_OFFSET);
	hitEffect->Play();
}

/**座標をチェック*/
bool AttackMagic::CheckHitWallCollision() 
{
	if (m_map == nullptr) 
	{
		return false ;
	}

	return m_map->IsWallAndCheckPosition(m_position) ;
}

void AttackMagic::Move()
{
	//発射方向に、毎フレーム進める。
	m_position += m_direction * As()->m_moveSpeed* g_gameTime->GetFrameDeltaTime();
}
