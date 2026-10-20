#pragma once

class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();
	void CheckHitEnemy();
	void Render(RenderContext& rc);

	//発射時に、初期位置と進む方向を設定する。
	void SetPositionAndDirection(const Vector3& pos, const Vector3& dir);

public:
	Vector3 position;
	Vector3 direction;      //進む方向

	void SetSpeed(float s) { speed = s; }
	void SetLifeTime(float t) { lifeTime = t; }

	float speed = 600.0f;  //弾の速さ
	float lifeTime = 3.0f;  //この秒数が経ったら、当たらなくても消える

	ModelRender modelRender;
};

