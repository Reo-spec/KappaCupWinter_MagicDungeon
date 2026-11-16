#pragma once

class Game;

class Title:public IGameObject
{
public:

	Title();
	~Title();

	bool Start()override;

	void Update()override;

	void Render(RenderContext& rc)override;

private:

	void SetAlpha();

	FontRender m_titleRender;
	/**Gameのpointerを作った*/
	Game* game = nullptr;

	float m_alphaTime = 0.0f;

	bool m_isVisible = false;

	/**Aボタンを押したら押されたという判定を持たせる。それによって早点滅を行う*/
	bool m_isPress = false;

	float m_pressedTime = 0.0f;

};

