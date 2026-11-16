#include "stdafx.h"
#include "HpBar.h"

void HpBar::Init(float width, float heigh, const Vector4& color) 
{

	//真っ白な四角の絵を、決めた大きさで読み込む
	m_spriteRender.Init("Assets/sprite/hpBar.dds", width, heigh);

	//基準を「左端の、上下の真ん中」にする（縮むときに右から縮むように）
	m_spriteRender.SetPivot(Vector2(0.0f, 0.5f));

	//白い絵に色をかけて、緑や赤にする
	m_spriteRender.SetMulColor(color);

	m_spriteRender.Update();
}

void HpBar::SetRatio(float ratio) 
{
	/**ここよくわかってない*/
	//0より小さく・1より大きくならないようにする
	if (ratio < 0.0f)
	{
		ratio = 0.0f;
	}
	if (ratio > 1.0f)
	{
		ratio = 1.0f;
	}

	//横だけ ratio 倍にする（縦と奥はそのまま）
	m_spriteRender.SetScale(Vector3(ratio, 1.0f, 1.0f));
	m_spriteRender.Update();
}

void HpBar::SetPosition(const Vector3& position) 
{
	m_spriteRender.SetPosition(position);
	m_spriteRender.Update();
}

void HpBar::Render(RenderContext& rc) 
{
	m_spriteRender.Draw(rc);
}
