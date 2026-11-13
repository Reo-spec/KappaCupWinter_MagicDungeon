#include "stdafx.h"
#include "Magic.h"
#include "Map.h"

static constexpr float MAGIC_COLLISION_RADIUS = 25.0f;//TODO(仕様未定)
static const Vector3 MAGIC_COLLISION_OFFSET = Vector3(0.0f,25.0f,0.0f);

AttackMagic::~AttackMagic() 
{
	//魔法の当たり判定とステータスは勝手に消えないから消している
	DeleteGO(m_collision);
	delete As();
}

bool AttackMagic::Start()
{
	// 特にすることないはず
	return true;
}


void AttackMagic::Update()
{
	// TODO: ここで移動処理などを書く
	Move();
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

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
		DeleteGO(this);
		return;
	}

}



void AttackMagic::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


void AttackMagic::Init(const std::string& modelPath, const AttackMagicStatus& status)
{
	//魔法の当たり判定を作成している
	m_collision = NewGO<CollisionObject>(0, "collision");
	m_collision->CreateSphere(m_position, Quaternion::Identity, MAGIC_COLLISION_RADIUS);
	m_collision->SetIsEnableAutoDelete(false);

	//ModelPathを持ってくる
	m_modelRender.Init(modelPath.c_str());

	m_status = new AttackMagicStatus(status);
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
