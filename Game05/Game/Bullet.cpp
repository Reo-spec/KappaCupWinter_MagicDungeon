#include "stdafx.h"
#include "Bullet.h"
#include "Magic.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

bool Bullet::Start()
{
	//仮の弾モデル(球など)。
	modelRender.Init("Assets/modelData/kariFireMagic.tkm");
	modelRender.SetPosition(m_position);

	return true;
}

//void Bullet::Init(const Magic::, const Vector3& pos, const Vector3& dir)
//{
//	m_position = pos;
//	m_direction = dir;
//}

void Bullet::Update()
{
	
	modelRender.SetPosition(m_position);
	modelRender.Update();

	//一定時間経ったら、何にも当たらず消える。

	float deltaTime= g_gameTime->GetFrameDeltaTime();

	m_lifeTime -= deltaTime;

	if (m_lifeTime <= 0.0f)
	{
		DeleteGO(this);
		return;
	}

}

void Bullet::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}

void Bullet::CheckHitEnemy()
{
	//	//Gameが持っている「敵のリスト」を取得する。
	//	Game* game = FindGO<Game>("game");
	//	if (game == nullptr)
	//	{
	//		return;
	//	}
	//
	//	//リストの中の敵を、1体ずつすべてチェックする。
	//	for (Enemy* enemy : game->GetEnemyList())
	//	{
	//		if (enemy == nullptr)
	//		{
	//			continue;   //すでに消えている敵は、飛ばして次へ
	//		}
	//
	//		float distance = (position - enemy->position).Length();
	//		if (distance < 80.0f)
	//		{
	//			game->AddScore(500);
	//			game->RemoveEnemyFromList(enemy);   //リストからも取り除く
	//			DeleteGO(enemy);
	//			DeleteGO(this);
	//			return;   //命中したら、そこで終わり
	//		}
	//	}
}


