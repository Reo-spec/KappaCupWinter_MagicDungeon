#pragma once

/**宝箱に渡すためだけに使う*/
class MagicManager;
/**敵に渡すためだけに使う*/
class Player;

/**消すときに使う*/
class FireEnemy;
class TreasureChest;

class Map :public IGameObject
{
public:
	Map();
	~Map();

	void Update();

	void Render(RenderContext& rc);

	bool Start()override;

	/**魔法をいれるセッター*/
	void SetMagicManager(MagicManager* magicManager) { m_magicManager = magicManager; }

	/**敵に渡すPlayerを受け取るセッター*/
	void SetPlayer(Player* player) { m_player = player; }

	/**この座標が壁かどうかを聞いている*/
	bool IsWallAndCheckPosition(const Vector3&position)const;

	/**この座標がゴールのマスならtrueを返す*/
	bool IsGoalPosition(const Vector3&position)const;

private:

	ModelRender m_mapFloorModelRender;
	ModelRender m_mapCeilingModelRender;

	PhysicsStaticObject physicsStaticObject;

	ModelRender m_mapWallRender;

	ModelRender m_wallCollisionRender;

	bool IsWall(int row, int column)const;

	char GetCellChar(int row, int column)const;

	//行と列をもらって座標を返す関数
	Vector3 GetCellPosition(int row, int column)const;

	//壁の位置を配列で持つ
	std::vector<Vector3>m_wallPosition;
	std::vector<Quaternion>m_wallRotation;
	
	//当たり判定の可変長
	std::vector<std::unique_ptr<PhysicsStaticObject>>m_wallCollision;

	MagicManager* m_magicManager = nullptr;

	/**Handleとは物の本体ではなく、物を探すための引換券的な役割をになっている
	あとでさらに勉強する必要がある*/


	/**Map が置いた敵（Map が消えるときに一緒に消す）*/
	std::vector<GOHandle<FireEnemy>>m_enemies;

	/**Map が置いた宝箱（Map が消えるときに一緒に消す）*/
	std::vector<GOHandle<TreasureChest>>m_treasureChest;

	/**敵に渡すためのPlayer(Map自身は使わない)*/
	Player* m_player = nullptr;
};

