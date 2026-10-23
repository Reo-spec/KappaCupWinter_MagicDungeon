#pragma once


enum class EnMagicType : uint8_t
{
	Fire,
	Max
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



using AttackValue = int;


struct AttackMagicStatus : public IMagicStatus
{
	/** 移動速度 */
	float m_moveSpeed;
	/** 威力(攻撃力) */
	AttackValue m_attackValue;
	/** 消滅時間 */
	float m_lifeTime;
	float m_maxLifeTime;
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




/**
 * 攻撃魔法のオブジェクトプールを作る
 * 見た目ごとに作ってください
 */
class AttackMagicPool : Noncopyable
{
	static constexpr uint8_t MAX_NUM = 50;

	struct PoolObject
	{
		AttackMagic magic;
		bool m_isUse;
	};


private:
	std::array<PoolObject, MAX_NUM> m_pool;


public:
	AttackMagicPool() {}
	~AttackMagicPool() {}

	void Init(const std::string& modelPath, const AttackMagicStatus& status);
	void Update();
	//こいつは書くために必要
	void Render(RenderContext& rc);

	AttackMagic* Use()
	{
		for (auto& object : m_pool) {
			if (!object.m_isUse) {
				object.m_isUse = true;
				return &object.magic;
			}
		}
		// 見つからない
		return nullptr;
	}
};





class AttackMagicPoolManager : Noncopyable
{
private:
	std::array<AttackMagicPool, static_cast<uint8_t>(EnMagicType::Max)> m_pools;


private:
	AttackMagicPoolManager() {}
	~AttackMagicPoolManager() {}

public:
	void Setup();
	void Update();
	void Render(RenderContext& rc);

public:
	AttackMagicPool* GetPool(EnMagicType type)
	{
		return &m_pools[static_cast<uint8_t>(type)];
	}




private:
	static AttackMagicPoolManager* m_instance;

public:
	static void Init()
	{
		m_instance = new AttackMagicPoolManager();
	}
	static AttackMagicPoolManager& Get()
	{
		return *m_instance;
	}
	static void Finalize()
	{
		if (m_instance) {
			delete m_instance;
			m_instance = nullptr;
		}
	}
};
