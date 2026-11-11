#pragma once
/**前方宣言だけだとわからないことが出たためファイルを読みこむ*/
#include "Magic.h"
class MagicManager;

class MagicSelectUI :public IGameObject
{
public:
	MagicSelectUI();
	~MagicSelectUI();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	//回転操作を実際に行う関数
	void RotateRight();
	void RotateLeft();

	void SetMagicManager(MagicManager* magicManager) { m_magicManager = magicManager; }

private:

	//UIの中心位置と半径の設定
	Vector3 m_centerPosition = Vector3(-700.0f, -300.0f,0.0f);
	float m_radius = 80.0f;

	//角度管理をする(ラジアン)
	float m_currentAngle = 1.5708f;
	float m_targetAngle = 1.5708f;

	SpriteRender m_baseSpriteRender;

	/**魔法の種類ごとのアイコンの絵にしている*/
	SpriteRender m_magicIconSprites[static_cast<int>(EnMagicType::Max)];

	MagicManager* m_magicManager = nullptr;

};

