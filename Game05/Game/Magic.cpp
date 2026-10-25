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

	//一定時間経ったら、何にも当たらず消える。

	float deltaTime = g_gameTime->GetFrameDeltaTime();

	As()->m_lifeTime += deltaTime;

	if (As()->m_lifeTime >= As()->m_maxLifeTime)
	{
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
	m_modelRender.Init(modelPath.c_str());

	m_status = new AttackMagicStatus(status);
}


void AttackMagic::Move()
{
	//発射方向に、毎フレーム進める。
	m_position += m_direction * As()->m_moveSpeed* g_gameTime->GetFrameDeltaTime();
}
