#include "stdafx.h"
#include "MagicInfluence.h"

/**燃焼1回分のダメージ*/
static constexpr int ONCE_FIRE_DAMAGE = 5;//TODO(仕様未定)

/**燃焼だめーじの間隔*/
static constexpr float BURN_DAMAGE_INTERVAL = 3.0f;//TODO(仕様未定)

/**燃える時間*/
static constexpr float BURN_REMAINING_TIME = 6.0f;//TODO(仕様未定)

void MagicInfluence::StartInfluence(const EnMagicType magicType) 
{
	switch (magicType) 
	{
	case EnMagicType::Fire:
		m_burnState.remainingTime = BURN_REMAINING_TIME;
		m_burnState.damage = ONCE_FIRE_DAMAGE;
		m_burnState.damageInterval = BURN_DAMAGE_INTERVAL;

		m_burnState.intervalTimer = 0.0f;
		break;
	default:
		/**永続効果などが無ければここは無視して進む*/
		break;
	}
}

AttackValue MagicInfluence::CountDownBurn() 
{
	/**燃えていなければダメージがない*/
	if (m_burnState.remainingTime <= 0.0f) {
		return 0;
	}

	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	m_burnState.remainingTime -= deltaTime;
	m_burnState.intervalTimer += deltaTime;

	if (m_burnState.intervalTimer >= m_burnState.damageInterval)
	{
		m_burnState.intervalTimer = 0.0f;

		return m_burnState.damage;
	}

	return 0;

}

void MagicInfluence::ClearInfluence() 
{
	/**最初の値をBaseStateに入れなおす*/
	m_burnState = BurnState();
}
