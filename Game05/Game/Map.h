#pragma once

class Map :public IGameObject
{
public:
	Map();
	~Map();

	void Update();

	void Render(RenderContext& rc);
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
};

