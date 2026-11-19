#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

/**敵の HP バーの大きさ*/
static constexpr float ENEMY_HP_BAR_WIDTH = 100.0f;//TODO(仕様未定)
static constexpr float ENEMY_HP_BAR_HEIGHT = 10.0f;//TODO(仕様未定)
/**足元から HP バーまでの高さ*/
static constexpr float ENEMY_HP_BAR_OFFSET_Y = 120.0f;//TODO(仕様未定)

static constexpr EnemyStatus FIRE_ENEMY_STATUS =
{
	EnMagicType::Fire,
	300,// TODO(仕様未定)
	120.0f,// TODO(仕様未定)
	"Assets/modelData/fireSlimeAnim.tkm",
	3.0f,//TODO(仕様未定)
	1000.0f,//TODO(仕様未定)
	1200.0f,//TODO(仕様未定)
	{ "Assets/animData/fireSlime_idle.tka",/**animationPathを渡している*/
	"Assets/animData/fireSlime_move.tka",
	"Assets/animData/fireSlime_attack.tka",
	"Assets/animData/fireSlime_die.tka" }
};

void IEnemy::Init(Vector3 position,const EnemyStatus&status)
{
	m_enemyStatus = status;
	m_position = position;

	for (int i = 0;i < enEnemyAnimationClip_Num;i++) 
	{
		m_animationClips[i].Load(m_enemyStatus.animationPath[i]);
		m_animationClips[enEnemyAnimationClip_Idle].SetLoopFlag(true);
		m_animationClips[enEnemyAnimationClip_Walk].SetLoopFlag(true);
		m_animationClips[enEnemyAnimationClip_Attack].SetLoopFlag(false);
		m_animationClips[enEnemyAnimationClip_Die].SetLoopFlag(false);
	}

	m_modelRender.Init(m_enemyStatus.modelPath,m_animationClips,enEnemyAnimationClip_Num,enModelUpAxisZ);
	m_modelRender.SetPosition(m_position);
	m_characterController.Init(40.0f, 50.0f, position);
	m_baseStatus.maxHp = m_enemyStatus.maxHp;
	m_baseStatus.hp = m_baseStatus.maxHp;
	m_hpBar.Init(ENEMY_HP_BAR_WIDTH, ENEMY_HP_BAR_HEIGHT,Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

void IEnemy::UpdateHpBar() 
{

	/**HPの割合でバーの長さを決める*/
	if (m_baseStatus.maxHp > 0) {
		float ratio = static_cast<float>(m_baseStatus.hp) / static_cast<float>(m_baseStatus.maxHp);
		m_hpBar.SetRatio(ratio);
	}

	/**頭の上の「世界の座標」*/
	Vector3 headPosition = m_position;
	headPosition.y += ENEMY_HP_BAR_OFFSET_Y;

	Vector3 headDirection = headPosition - g_camera3D->GetPosition();

	/**このDotの関数はｃ++のライブラリにある標準装備であり、
	Dotはベクトルの内積を計算して出している。なぜ内積が必要になったかというとその敵がカメラの前にいるのか、
	後ろにいるのかを調べて後ろにいるのなら表示しないということっを知るため。
	内積を使って0か1で向きを判断している*/
	float dotHead = headDirection.Dot(g_camera3D->GetForward());

	if (dotHead <= 0) {
		m_isHpBarVisible = false;

		return;
	}

	/**世界の座標を「画面の座標」に直す*/
	Vector2 screenPosition;
	g_camera3D->CalcScreenPositionFromWorldPosition(screenPosition, headPosition);

	/**バーは基準が左側だからそれに揃える*/
	m_hpBar.SetPosition(Vector3(screenPosition.x - ENEMY_HP_BAR_WIDTH * 0.5f, screenPosition.y, 0.0f));

	m_isHpBarVisible = true;

}

void IEnemy::Render(RenderContext& rc)
{

	//親（Character）の Render で、モデルを描く
	Character::Render(rc);

	/**敵がこちら(カメラを見ているかどうか)を見ているかどうかで見ていたらHPバーを描画する*/
	if (m_isHpBarVisible) 
	{	
		//そのあとに HP バーを描く
		m_hpBar.Render(rc);
	}
}

void IEnemy::Die() 
{
	m_isAlive = false;

	DeleteGO(this);
}

//最初はプレイヤーに向かって歩くだけ
//だがあとから改良できるようにTargetになっている
void IEnemy::MoveToTarget(const Vector3& target) 
{
	Vector3 diff = target - m_position;
	diff.y = 0.0f;

	/**チェイスをtrueにする*/
	m_isChase = true;

	if (diff.Length() <= 165.0f) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z= 0.0f;
		return;
	}

	diff.Normalize();
	m_moveSpeed.x = m_enemyStatus.moveSpeed * diff.x;
	m_moveSpeed.z = m_enemyStatus.moveSpeed * diff.z;

	//キャラクターの方向を変える。
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	//回転を伝える。
	m_modelRender.SetRotation(m_rotation);
	
}

void IEnemy::SetMagicStatusAndPath(const AttackMagicStatus& status, const char* modelPath) 
{
	/**魔法のステータスとファイルパスをコピーして渡す*/
	m_attackMagicStatus = status;
	m_modelPath = modelPath;
}

void IEnemy::ManageEnemyState()
{

	if (m_enemyState == 2 && m_modelRender.IsPlayingAnimation())
	{
		return;
	}

	/**移動していたら*/
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{


		//ステートを1(歩き)にする。
		m_enemyState = 1;

	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		m_enemyState = 0;
	}

	if (!m_isAlive)
	{
		m_enemyState = 3;
	}
}

void IEnemy::MagicAttack() 
{
	if (m_modelPath == nullptr) {
		return;
	}

	//向いてる方向をとる
	Vector3 diff = m_player->GetPosition()-m_position;
	diff.y = 0.0f;

	diff.Normalize();

	Vector3 magicPos = m_position + diff * 50.0f;
	magicPos.y += 50.0f;

	//魔法の種類ごとにモデルとステータスを決める
	const char* modelPath = m_modelPath;
	AttackMagicStatus status = m_attackMagicStatus;

	AttackMagic* magic = NewGO<AttackMagic>(0, "enemyMagic");

	if (magic == nullptr) {
		return;
	}

	/**エネミーのStateを2(魔法を撃っている状態)に変化させている*/
	m_enemyState = 2;

	magic->SetMap(m_map);
	magic->Init(modelPath, status);
	magic->SetPositionAndDirection(magicPos, diff);

	//m_isAttackMagic = true;

}

void IEnemy::PlayAnimation() 
{
	switch (m_enemyState) 
	{
	case 0:
		m_modelRender.PlayAnimation(enEnemyAnimationClip_Idle);
		break;
    /**歩きのanimation*/
	case 1:
		m_modelRender.PlayAnimation(enEnemyAnimationClip_Walk);
		break;
	/**攻撃のanimation*/
	case 2:
		m_modelRender.PlayAnimation(enEnemyAnimationClip_Attack);
		break;
	/**倒される時のanimation*/
	case 3:
		m_modelRender.PlayAnimation(enEnemyAnimationClip_Die);
		break;
	default:
		break;
	}
}


void FireEnemy::Init(Vector3 position)
{
	IEnemy::Init(position, FIRE_ENEMY_STATUS);

}

void FireEnemy::UpdateAction()
{

	MoveAction();

	//毎フレーム魔法にあったっているかをとっている
	CheckHitMagic("magic");

	//プレイヤーが渡されていなかったら動かない
	if (m_player == nullptr) {
		return;
	}

	Vector3 diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f;

	/**プレイヤーの方向を向くかどうかを場合分けしている*/
	if (diff.Length() < m_enemyStatus.chaseRange)
	{
		MoveToTarget(m_player->GetPosition());
	}
	else {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}

	if (m_enemyState == 2) 
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}


	float deltaTime = g_gameTime->GetFrameDeltaTime();

	m_nextAttackLimit -= deltaTime;

	if (diff.Length() <= m_enemyStatus.attackRange && m_nextAttackLimit <= 0.0f) {
		MagicAttack();
		m_nextAttackLimit = m_enemyStatus.attackInterval;
	}


	if (m_isChase) {
		//頭の上の HP バーを表示し動かす
		UpdateHpBar();

		/**敵が何をしているかを見ている。
		敵がplayerを見つけているかどうかを見ている*/
		m_isChase = false;
	}
	else
	{
		/**こっちの判定の変数はHPバーを実装するかどうかを見ている。
		そしてこいつがあるかないかでDrawを管理しているから敵がチェイスじゃないときに表示を切っている*/
		m_isHpBarVisible = false;
	}

	ManageEnemyState();

	PlayAnimation();

}

