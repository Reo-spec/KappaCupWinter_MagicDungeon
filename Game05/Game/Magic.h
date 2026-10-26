#pragma once
#include "AttackValue.h"

enum class EnMagicType : uint8_t
{
	Stone,
	Fire,
	Max,
	None
};



/**
 * すべて魔法の基底となるステータス構造体
 */
struct IMagicStatus
{
	/** クールダウン */
	float m_coolDown = 0.0f;		// 今のクールダウン時間					使用したら更新される
	float m_maxCoolDown = 0.0f;		// 決められているクールダウン時間		最初に設定されたもの
};


struct AttackMagicStatus : public IMagicStatus
{
	/** 移動速度 */
	float m_moveSpeed = 0.0f;
	/** 威力(攻撃力) */
	AttackValue m_attackValue = 0.0f;
	/** 消滅時間 */
	float m_lifeTime = 0.0f ;
	float m_maxLifeTime = 0.0f;
};




/**
 * 魔法の基底クラス
 * すべての魔法はこのクラスを継承します
 */
class IMagic :public IGameObject
{
protected:
	IMagicStatus* m_status = nullptr;


public:
	IMagic() {}
	virtual ~IMagic() {}
};



/**
 * 攻撃魔法の基底クラス
 * すべての攻撃魔法はこのクラスを継承します
 */
class AttackMagic : public IMagic
{
private:
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_direction;      //進む方向


public:
	AttackMagic() {};
	~AttackMagic() {};

	bool Start() override;
	void Update() override;	
	void Render(RenderContext& rc) override;

	/**
	 * TODO: あとでパラメータでステータスの情報は渡してほしい
	 */
	void Init(const std::string& modelPath, const AttackMagicStatus& status);

	void SetPositionAndDirection(const Vector3& pos, const Vector3& dir) { m_position = pos; m_direction = dir; }

private:
	void Move();

public:
	AttackMagicStatus* As() { return static_cast<AttackMagicStatus*>(m_status); }
};




