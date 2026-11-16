#include "stdafx.h"
#include "Clear.h"
#include "Title.h"

/**明度が変わる時間を定数にしている*/
static constexpr float IS_CHANGE_ALPHA = 0.5f;//TODO(仕様未定)

/**明度が変わる時のMaxの時間を定数にしている*/
static constexpr float IS_MAX_CHANGE_ALPHA = 0.05f;//TODO(仕様未定)

/**Aボタンを押したを保持する時間*/
static constexpr float IS_PRESS_TIME = 1.0f;//TODO(仕様未定)

Clear::Clear()
{
}

Clear::~Clear()
{
}

bool Clear::Start()
{
	m_clearRender.SetText(L"See you again soon");
	m_clearRender.SetPosition(Vector3(-200.0f, 0.0f, 0.0f));
	m_clearRender.SetColor(0.0f, 0.0f, 0.0f, 1.0f);

	return true;
}

void Clear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{

		if (m_isPress) { return; }

		m_isPress = true;

	}

	if (m_isPress)
	{

		float deltaTime = g_gameTime->GetFrameDeltaTime();

		m_pressedTime += deltaTime;

		if (m_pressedTime >= IS_PRESS_TIME)
		{
			title = NewGO<Title>(0, "title");
			DeleteGO(this);

			return;
		}

	}


	//SetAlpha();

}

void Clear::Render(RenderContext& rc)
{
	m_clearRender.Draw(rc);
}

void Clear::SetAlpha()
{

	float deltaTime = g_gameTime->GetFrameDeltaTime();

	m_alphaTime += deltaTime;

	if (m_isPress)
	{
		if (m_alphaTime >= IS_MAX_CHANGE_ALPHA)
		{
			m_alphaTime = 0.0f;

			m_isVisible = !m_isVisible;
		}
	}

	if (m_alphaTime >= IS_CHANGE_ALPHA) {

		m_alphaTime = 0.0f;

		m_isVisible = !m_isVisible;
	}

	if (m_isVisible)
	{
		m_clearRender.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		m_clearRender.SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

}