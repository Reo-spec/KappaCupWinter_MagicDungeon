#pragma once
#include "MagicType.h"

class MagicType;
class Magic;

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
	//void Init(const MagicParam& param, const Vector3& pos, const Vector3& dir);

public:
	Vector3 m_position;
	Vector3 m_direction;      //進む方向

	void SetSpeed(float s) { m_speed = s; }
	void SetLifeTime(float t) { m_lifeTime = t; }

	// パラメータ保持用
	float m_speed = 0.0f;
	float m_lifeTime = 0.0f;
	int m_damage = 0;

	ModelRender modelRender;
};

