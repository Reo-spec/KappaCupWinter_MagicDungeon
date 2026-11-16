#pragma once

class Title;

class Clear:public IGameObject
{
public:

	Clear();
	~Clear();

	bool Start()override;

	void Update()override;

	void Render(RenderContext& rc)override;

private:

	void SetAlpha();

	FontRender m_clearRender;
	/**Gameのpointerを作った*/
	Title* title = nullptr;

	float m_alphaTime = 0.0f;

	bool m_isVisible = false;

	/**Aボタンを押したら押されたという判定を持たせる。それによって早点滅を行う*/
	bool m_isPress = false;

	float m_pressedTime = 0.0f;

};

