#pragma once

enum class EnMagicType:uint8_t;

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

	//現在選択されているスロット(0,1,2)を取得
	int GetSelectedSlot()const { return m_selectedSlot; }

	//今の魔法のタイプを取得している
	EnMagicType GetMagicType()const { return m_magicTypeSlot[m_selectedSlot]; }

private:

	//スロットごとの魔法の種類を記憶している
	EnMagicType m_magicTypeSlot[3];

	//UIの中心位置と半径の設定
	Vector3 m_centerPosition = Vector3(-700.0f, -300.0f,0.0f);
	float m_radius = 80.0f;

	//角度管理をする(ラジアン)
	float m_currentAngle = 1.5708f;
	float m_targetAngle = 1.5708f;

	//現在選択しているSlotを記憶している
	int m_selectedSlot = 0;

	SpriteRender m_baseSpriteRender;

	//Slotアイコンの描画を担当する
	SpriteRender m_slotSprites[3];

};

