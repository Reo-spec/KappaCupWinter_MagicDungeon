#include "stdafx.h"
#include "Map.h"
#include "TreasureChest.h"

/**迷路の行の数(縦マスの数)*/
static constexpr int MAZE_ROW_COUNT = 31;

/**迷路の列の数(横マスの数)*/
static constexpr int MAZE_COLUMN_COUNT = 31;


/**スタートの行の数*/
static constexpr int START_CORRIDOR_ROW_COUNT = 6;
/**スタートの列の数*/
static constexpr int START_CORRIDOR_COLUMN_COUNT = 13;
/**スタートの通路の0行目が迷路で数えて何行目にあたるか*/
static constexpr int START_CORRIDOR_ROW_OFFSET = 31;
/**スタート通路の0列目が迷路で何列目に当たるか*/
static constexpr int START_CORRIDOR_COLUMN_OFFSET = 0;

/**1マスの大きさ*/
static constexpr float CELL_SIZE = 400.0f;//TODO(仕様未定)

/**世界の座標を渡す*/
static const Vector3  MAZE_CORNER_POSITION = Vector3(-11.5f * CELL_SIZE, 0.0f, 35.5f * CELL_SIZE);

//これは1次元配列で複数回これを通ることで2つの値がわかるようになる
//2次元配列だと制限が多いらしい
constexpr const char* MAZE_MAP[] = {
		"#################G#############",
		"#...#.....#.................#T#",
		"#.#.#.#.#.#.###############.#.#",
		"#.#...#.#...#...#.......O.#...#",
		"#.#####.#####.#.#.#####.#.###.#",
		"#.#...#.#...#.#.#.#.....#E..#.#",
		"#.#.#.#.#.#.#.#.#.#.#####.#.#.#",
		"#.#.#T#...#...#...#.....#.#.#.#",
		"#.#.###########.#######.#.#.#.#",
		"#.#..E..#.....#T#.......#.#.#.#",
		"#.###.###.###.###.#####O#.#.#.#",
		"#.....#...#.#.....#....T#.#.#.#",
		"#######.###.#########.###.#.#.#",
		"#.....#...#.....#.....#.....#.#",
		"#.###.#.#.###.#.#.###O#.###.#.#",
		"#.#.#.#.#.O..E#...#...#...#...#",
		"#.#.#.###.#.#.#####.#.###.#####",
		"#.#.......#.#.#...#.#...#.....#",
		"#.#.#######.#.#.#.#.#.#######.#",
		"#..E#.#.....#.#.#.#.#.......#.#",
		"###.#.#.###.###.#.#.###.#.#.#.#",
		"#...#.#...#.....#...#...#.#.#.#",
		"#.###.###.#O#########.###.#.#.#",
		"#.#.....#.#..F#.......#...#T#.#",
		"#.###.###.#.###.###.###.#####.#",
		"#...#.....#....E..#.#...#...#.#",
		"#.#.#.###########.#.#.###.#.#.#",
		"#.#.#.#.......#...#.#.....#.#.#",
		"#.#.#.###.###.#####.#######.#.#",
		"#.........#...............#...#",
		"###.###########################",
};

constexpr const char* START_CORRIDOR_MAP[] =
{
	"###.#######L#",
	"##M.........#",
	"###########.#",
	"###########.#",
	"###########S#",
	"#############",
};


bool Map::IsWall(int row,int column)const
{
	if (0 <= row && row < MAZE_ROW_COUNT && 0 <= column && column < MAZE_COLUMN_COUNT) 
	{
		return MAZE_MAP[row][column] == '#';
	}

	int corridorRow = row - START_CORRIDOR_ROW_OFFSET;
	int corridorColumn = column - START_CORRIDOR_COLUMN_OFFSET;

	if (0 <= corridorRow && corridorRow < START_CORRIDOR_ROW_COUNT && 0 <= corridorColumn && corridorColumn < START_CORRIDOR_COLUMN_COUNT) 
	{
		return START_CORRIDOR_MAP[corridorRow][corridorColumn] == '#';
	}

	return true;
}

char Map::GetCellChar(int row, int column)const
{
	if (0 <= row && row < MAZE_ROW_COUNT && 0 <= column && column < MAZE_COLUMN_COUNT)
	{
		return MAZE_MAP[row][column];
	}

	int corridorRow = row - START_CORRIDOR_ROW_OFFSET;
	int corridorColumn = column - START_CORRIDOR_COLUMN_OFFSET;

	if (0 <= corridorRow && corridorRow < START_CORRIDOR_ROW_COUNT && 0 <= corridorColumn && corridorColumn < START_CORRIDOR_COLUMN_COUNT)
	{
		return START_CORRIDOR_MAP[corridorRow][corridorColumn];
	}
	return '#';
}


Vector3 Map::GetCellPosition(int row,int column) const
{
	//ワールド座標をとってMAPを配置する準備をしている
	Vector3 cellPosition;
	cellPosition.x = MAZE_CORNER_POSITION.x + column * CELL_SIZE + CELL_SIZE / 2;
	cellPosition.y = 0.0f;
	cellPosition.z = MAZE_CORNER_POSITION.z - (row * CELL_SIZE + CELL_SIZE / 2);

	return cellPosition;
}

Map::Map() 
{
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_mapFloorModelRender.Init("Assets/modelData/mazeFloor.tkm");

	m_mapCeilingModelRender.Init("Assets/modelData/mazeCeiling.tkm");

	Vector3 cellPosition = GetCellPosition(35, 11);

	int mapWallCounter = 0;

	for (int row = 0; row < MAZE_ROW_COUNT+ START_CORRIDOR_ROW_COUNT; row++)
	{
		//行と列を定数の回数見る
		for (int column = 0;column < MAZE_COLUMN_COUNT;column++) 
		{
			if (IsWall(row, column))
			{

				Vector3 wallCenterPosition = GetCellPosition(row, column);

				//MAPの上が壁かどうかを確認している
				if (!IsWall(row - 1, column))
				{
					Vector3 Position = wallCenterPosition;
					Position.z += CELL_SIZE / 2;
					Quaternion Rotation;
					Rotation.SetRotationDegY(0.0f);
					m_wallPosition.push_back(Position);
					m_wallRotation.push_back(Rotation);
					mapWallCounter++;
				}
				
				//MAPの下が壁かどうかを調べている
				if (!IsWall(row + 1, column))
				{
					Vector3 Position = wallCenterPosition;
					Position.z -= CELL_SIZE / 2;
					Quaternion Rotation;
					Rotation.SetRotationDegY(180.0f);
					m_wallPosition.push_back(Position);
					m_wallRotation.push_back(Rotation);
					mapWallCounter++;
				}
				
				//MAPの左が壁かどうかを調べる
				if (!IsWall(row , column - 1))
				{
					Vector3 Position = wallCenterPosition;
					Position.x -= CELL_SIZE / 2;
					Quaternion Rotation;
					Rotation.SetRotationDegY(-90.0f);
					m_wallPosition.push_back(Position);
					m_wallRotation.push_back(Rotation);
					mapWallCounter++;
				}
				
				//MAPの右が壁かどうかを調べている
				if (!IsWall(row , column +1))
				{
					Vector3 Position = wallCenterPosition;
					Position.x += CELL_SIZE / 2;
					Quaternion Rotation;
					Rotation.SetRotationDegY(90.0f);
					m_wallPosition.push_back(Position);
					m_wallRotation.push_back(Rotation);
					mapWallCounter++;
				}

				K2_LOG("覚えた板の数:%d\n", (int)m_wallPosition.size());
			}
		}
	}

	//引数はもともと7つ
	m_mapWallRender.Init("Assets/modelData/dungeonWall.tkm",nullptr,0,enModelUpAxisZ,true,m_wallPosition.size(), false);

	m_wallCollisionRender.Init("Assets/modelData/dungeonWallCol.tkm");

	for (int i = 0;i < m_wallPosition.size();i++) 
	{
		//初期設定
		m_wallCollisionRender.SetPosition(m_wallPosition[i]);
		m_wallCollisionRender.SetRotation(m_wallRotation[i]);
		m_wallCollisionRender.Update();

		//配列に詰める
		auto wallCollision = std::make_unique<PhysicsStaticObject>();

		//当たり判定の作成
		wallCollision->CreateFromModel(m_wallCollisionRender.GetModel(), m_wallCollisionRender.GetModel().GetWorldMatrix());

		//中身をコピーして使うからmoveをお使っている
		m_wallCollision.push_back(std::move(wallCollision));
	}

	
	m_mapFloorModelRender.SetPosition(MAZE_CORNER_POSITION);
	m_mapCeilingModelRender.SetPosition(MAZE_CORNER_POSITION);

	m_mapFloorModelRender.Update();
	m_mapCeilingModelRender.Update();

	physicsStaticObject.CreateFromModel(m_mapFloorModelRender.GetModel(), m_mapFloorModelRender.GetModel().GetWorldMatrix());

	K2_LOG("板の枚数:%d\n",mapWallCounter);
	K2_LOG("座標: x=%f y=%f z=%f\n", cellPosition.x,cellPosition.y,cellPosition.z);

}

bool Map::Start() 
{
	for (int row = 0; row < MAZE_ROW_COUNT + START_CORRIDOR_ROW_COUNT; row++)
	{
		//行と列を定数の回数見る
		for (int column = 0;column < MAZE_COLUMN_COUNT;column++)
		{

			if (GetCellChar(row, column))
			{
				char mapText = GetCellChar(row, column);

				Quaternion chestRotation;

				if (!IsWall(row - 1, column))
				{
					chestRotation.SetRotationDegY(0.0f);
				}
				else if (!IsWall(row + 1, column))
				{
					chestRotation.SetRotationDegY(180.0f);
				}
				else if (!IsWall(row, column - 1))
				{
					chestRotation.SetRotationDegY(-90.0f);
				}
				else if (!IsWall(row, column + 1))
				{
					chestRotation.SetRotationDegY(90.0f);
				}


				if (mapText == 'M')
				{
					//石の魔法が入った宝箱
					TreasureChest* tc = NewGO<TreasureChest>(0, "treasureChest");
					tc->SetPosition(GetCellPosition(row, column));
					tc->SetRotation(chestRotation);
					tc->SetContents(EnMagicType::Stone);
					tc->SetMagicManager(m_magicManager);
				}
				if (mapText == 'F')
				{
					//炎の魔法が入った宝箱
					TreasureChest* tc = NewGO<TreasureChest>(0, "treasureChest");
					tc->SetPosition(GetCellPosition(row, column));
					tc->SetRotation(chestRotation);
					tc->SetContents(EnMagicType::Fire);
					tc->SetMagicManager(m_magicManager);
				}
				if (mapText == 'L')
				{
					//たいまつの宝箱（α版では開けたらログを出すだけ）
					TreasureChest* tc = NewGO<TreasureChest>(0, "treasureChest");
					tc->SetPosition(GetCellPosition(row, column));
					tc->SetRotation(chestRotation);
					tc->SetTorch();
				}

			}
		}
	}
	return true;
}

Map::~Map()
{
}

void Map::Update() 
{
	for (int i = 0;i < m_wallPosition.size();i++) 
	{
		//インスタンシングで、933かい指令を出さないといけないところを1回にまとめている
		m_mapWallRender.UpdateInstancingData(i, m_wallPosition[i], m_wallRotation[i], Vector3::One);
	}
}

void Map::Render(RenderContext& rc) 
{
	m_mapFloorModelRender.Draw(rc);
	m_mapCeilingModelRender.Draw(rc);
	m_mapWallRender.Draw(rc);
}