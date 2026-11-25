#include "stdafx.h"
#include "MagicInfluence.h"

/**燃焼1回分のダメージ*/
static constexpr int ONCE_FIRE_DAMAGE = 5;//TODO(仕様未定)

/**燃焼だめーじの間隔*/
static constexpr float BURN_DAMAGE_INTERVAL = 3.0f;//TODO(仕様未定)

/**燃える時間*/
static constexpr float BURN_REMAINING_TIME = 6.0f;//TODO(仕様未定)

/**移動速度の低下させる倍率*/
static constexpr float FROZEN_MAGNIFICATION = 0.0f;//TODO(仕様未定)

/**凍る度に、次に凍る時間に掛ける倍率*/
static constexpr float FROZEN_TIME_DECAY_RATE = 0.5f;//TODO(仕様未定)

/**凍りが溶けてから、凍る時間がもとの長さに戻るまでの時間*/
static constexpr float FROZEN_TIME_RESET_TIME = 4.0f;//TODO(仕様未定)

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
	case EnMagicType::Ice:
		if (IsFrozen()) {
			break;
		}

		/**今の倍率で凍らせてから、次の攻撃のために倍率を下げる*/
		m_frostState.remainingTime = m_baseFrozenTime * m_frostState.frozenTimeRate;
		m_frostState.frozenTimeRate *= FROZEN_TIME_DECAY_RATE;

		/**もとの長さに戻るための時間を数えなおす*/
		m_frostState.rateResetTimer = FROZEN_TIME_RESET_TIME;
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

void MagicInfluence::CountDownFrost()
{

	const float deltaTime = g_gameTime->GetFrameDeltaTime();
	/**凍ってる間の時間も無敵時間もゼロだったら通らない
	理由はこれは数を減らすだけの関数だから両方0になったら通らないが正常*/
	if (IsFrozen()) {
		m_frostState.remainingTime -= deltaTime;
		return ;
	}

	/**戻るまでの時間が残っていなかったら、数えるものが無いから切り上げ*/
	if (m_frostState.remainingTime <= 0.0f) 
	{
		return;
	}

	/**溶けてからの時間を数え、しばらく凍らなければ時間を戻す*/
	m_frostState.rateResetTimer -= deltaTime;
	if (m_frostState.rateResetTimer <= 0.0f) {
		m_frostState.frozenTimeRate = 1.0f;
	}
}

void MagicInfluence::ClearInfluence() 
{
	/**最初の値をBaseStateに入れなおす*/
	m_burnState = BurnState();

	m_frostState = FrostState();
}

float MagicInfluence::GetSpeedMagnification()const 
{
	if (IsFrozen()) {
		return FROZEN_MAGNIFICATION;
	}
	
	return 1.0f;
}

bool MagicInfluence::IsFrozen()const 
{
	return m_frostState.remainingTime > 0.0f;
}