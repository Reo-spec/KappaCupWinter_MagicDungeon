#pragma once

class HpBar
{
public:

	/**HPバーを準備する*/
	void Init(float width, float height, const Vector4& color);

	/**HPの割りあいを(0~1)で横の長さを決める*/
	void SetRatio(float ratio);

	/**画面のどこに出すかを決める*/
	void SetPosition(const Vector3& position);


	void Render(RenderContext& rc);

private:
	SpriteRender m_spriteRender;
};

