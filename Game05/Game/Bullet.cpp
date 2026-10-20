#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

bool Bullet::Start()
{
	//仮の弾モデル(球など)。ファイル名は実際のものに置き換えてください。
	modelRender.Init("Assets/modelData/kariFireMagic.tkm");
	modelRender.SetPosition(position);

	return true;
}

void Bullet::SetPositionAndDirection(const Vector3& pos, const Vector3& dir)
{
	position = pos;
	direction = dir;
}

void Bullet::Update()
{
	//発射方向に、毎フレーム進める。
	position += direction * speed * g_gameTime->GetFrameDeltaTime();
	modelRender.SetPosition(position);
	modelRender.Update();

	//一定時間経ったら、何にも当たらず消える。
	lifeTime -= g_gameTime->GetFrameDeltaTime();
	if (lifeTime <= 0.0f)
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


