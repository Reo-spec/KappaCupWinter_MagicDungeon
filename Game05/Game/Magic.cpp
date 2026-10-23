#include "stdafx.h"
#include "Magic.h"

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

}


void AttackMagic::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


void AttackMagic::Init(const std::string& modelPath, const AttackMagicStatus& status)
{
	m_modelRender.Init(modelPath.c_str());

	m_status = new AttackMagicStatus(status);

	/*int test = 0;
	test = 1;*/
}


void AttackMagic::Move()
{
	//発射方向に、毎フレーム進める。
	m_position += m_direction * As()->m_moveSpeed* g_gameTime->GetFrameDeltaTime();
}




void AttackMagicPool::Init(const std::string& modelPath, const AttackMagicStatus& status)
{
	for (auto& object : m_pool)
	{
		object.magic.Init(modelPath, status);
		object.m_isUse = false;
	}
}


void AttackMagicPool::Update()
{

	for (auto& object : m_pool)
	{
		if (!object.m_isUse) continue;
		// ここからは使っているものを処理する
		auto& magic = object.magic;
		magic.Update();
		auto* status = magic.As();
		if (status->m_coolDown > status->m_maxCoolDown) {
			object.m_isUse = true;
		}
	}

	//一定時間経ったら、何にも当たらず消える。

	float deltaTime = g_gameTime->GetFrameDeltaTime();

	/*m_lifeTime -= deltaTime;

	if (m_lifeTime <= 0.0f)
	{

		return;
	}*/
}

//モデルを1つRenderしている
void AttackMagicPool::Render(RenderContext& rc)
{
	for (auto& object : m_pool)          
	{
		if (!object.m_isUse) continue;    
		auto& magic = object.magic;     
		magic.Render(rc);
	}
}

//UpDateしている
void AttackMagicPoolManager::Update() 
{
	for (auto& pool : m_pools)
	{
		pool.Update();
	}
}

void AttackMagicPoolManager::Render(RenderContext& rc)
{
	for (auto& pool : m_pools)
	{
		pool.Render(rc);
	}
}



AttackMagicPoolManager* AttackMagicPoolManager::m_instance = nullptr;


void AttackMagicPoolManager::Setup()
{
	// TODO: それぞれの魔法の初期化を書く

	// レベル１の炎の初期化を書く
	{
		auto& pool = m_pools[static_cast<uint8_t>(EnMagicType::Fire)];
		AttackMagicStatus status;
		status.m_maxLifeTime = 3.0f;
		status.m_maxCoolDown = 3.0f;
		status.m_moveSpeed = 1000.0f;
		pool.Init("Assets/modelData/kariFireMagic.tkm", status);
	}
	// レベル2の炎
	{
		//auto& pool = m_pools[static_cast<uint8_t>(EnMagicType::Fire)];
		//AttackMagicStatus status;
		//status.m_maxLifeTime = 3.0f;
		//status.m_maxCoolDown = 3.0f;
		//pool.Init("Assets/Model/test.tkm", status);
	}

}