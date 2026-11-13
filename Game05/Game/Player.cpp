#include "stdafx.h"
#include "Player.h"
#include "Magic.h"
#include "MagicManager.h"

Player::Player() {
	
	//アニメーションクリップをロードする。
	animationClips[enAnimationClip_Idle].Load("Assets/animData/wizard_idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/wizard_walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/wizard_run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Attack].Load("Assets/animData/wizard_attack.tka");
	animationClips[enAnimationClip_Attack].SetLoopFlag(false);
	animationClips[enAnimationClip_Damage].Load("Assets/animData/wizard_damage.tka");
	animationClips[enAnimationClip_Damage].SetLoopFlag(false);
	animationClips[enAnimationClip_Die].Load("Assets/animData/wizard_die.tka");
	animationClips[enAnimationClip_Die].SetLoopFlag(false);

	//ユニティちゃんのモデルを読み込む。
	m_modelRender.Init("Assets/modelData/wizard.tkm", animationClips, enAnimationClip_Num, enModelUpAxisZ);

	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);

	m_baseStatus.maxHp = 500;
	m_baseStatus.hp = m_baseStatus.maxHp;
}

Player::~Player() 
{

}

void Player::UpdateAction() {
	//移動処理。
	Move();

	//回転処理。
	Rotation();

	//ローリング回避用のコード
	Rolling();

	//魔法を打つために使用
	ShotMagic();

	//ステート管理。
	ManageState();

	//アニメーションの再生。
	PlayAnimation();

	/**敵の魔法に当たっているかの確認*/
	CheckHitMagic("enemyMagic");

}

void Player::Move() 
{
	//ダッシュ用の関数
	int dashMagnification = 1.0f;

	if (g_pad[0]->IsPress(enButtonB))
	{
		dashMagnification *= 2.0f;
	}

	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += GetCameraDirection(g_pad[0]->GetLStickXF(), g_pad[0]->GetLStickYF()) * 240.0f * dashMagnification;

	MoveAction();

}

void Player::ManageState()
{

	//魔法を撃つステートになっているか？
	//Returnで切り返しても問題ない
	//理由としてはちゃんと順番を守ってコードを書けば問題ないから
	if (playerState == 2 && m_modelRender.IsPlayingAnimation())
	{
		return;
	}

	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ステートを1(歩き)にする。
		playerState = 1;

		//ダッシュをする(ステート3)
		if (g_pad[0]->IsPress(enButtonB))
		{
			playerState = 3;
		}

		if (g_pad[0]->IsPress(enButtonX)) 
		{
			playerState = 4;
		}
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		playerState = 0;
	}

}

void Player::PlayAnimation()
{
	//switch文。
	switch (playerState) {
		//プレイヤーステートが0(待機)だったら。
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//プレイヤーステートが1(歩き)だったら。
	case 1:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
		//プレイヤーステートが2(魔法を打つ)だったら。
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Attack);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

//回転回避をさせる
void Player::Rolling() 
{
	if (g_pad[0]->IsTrigger(enButtonX)) {

		//カメラからのベクトルを取り最終的に1にしてスティックの方向を探っている
		Vector3 dir= GetCameraDirection(g_pad[0]->GetLStickXF(), g_pad[0]->GetLStickYF());

		//ここで実際の移動の処理を行っている
		//移動のベクトルが伸びたらそれを感知してPositionを動かしている
		if (dir.Length() > 0.001f) {
			dir.Normalize();
			m_position += dir*30.0f;
			m_characterController.SetPosition(m_position);
			m_modelRender.SetPosition(m_position);
		}
	}
}

Vector3 Player::GetCameraDirection(float stickX,float stickY)
{
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	forward.y = 0.0f;
	right.y = 0.0f;
	forward.Normalize();
	right.Normalize();

	return right * stickX + forward * stickY;
}

void Player::Rotation() 
{
	//xかzの移動速度があったら(スティックの入力があったら)。
		if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		{
			//キャラクターの方向を変える。
			m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
			//回転を伝える。
			m_modelRender.SetRotation(m_rotation);
		}
}

void Player::ShotMagic()
{
	if (g_pad[0]->IsTrigger(enButtonRB2))
	{
		//MagicManagerが渡されていないときは撃たない
		if (m_magicManager == nullptr) {
			return;
		}
		
		//向いてる方向をとる
		Vector3 magicDir = CalcMagicDirection();

		Vector3 magicPos = m_position + magicDir * 50.0f;
		magicPos.y += 100.0f;
		
		/**MagicManagerに魔法を聞く*/
		EnMagicType currentMagic = m_magicManager->GetMagicType();


		if (currentMagic==EnMagicType::None) {
			return;
		}


		if (!m_magicManager->IsReady(currentMagic)) {
			return;
		}

		//魔法の種類ごとにモデルとステータスを決める
		const char* modelPath = m_magicManager->GetModelPath(currentMagic);
		AttackMagicStatus status = m_magicManager->GetBaseStatus(currentMagic);
	
		AttackMagic* magic = NewGO<AttackMagic>(0, "magic");

		if (magic == nullptr) {
			return;
		}

		magic->SetMap(m_map);
		magic->Init(modelPath, status);
		m_magicManager->UseMagic(currentMagic);
		magic->SetPositionAndDirection(magicPos, magicDir);

		//ステート2(魔法を打つ)に変更
		playerState = 2;
	}
}

Vector3 Player::CalcMagicDirection() 
{
	Vector3 dir = GetCameraDirection(g_pad[0]->GetLStickXF(), g_pad[0]->GetLStickYF());
	//LengthについているSqは長さの二乗をしている
	if (dir.LengthSq() < 0.001f) 
	{
		dir = Vector3::AxisZ;
		m_rotation.Apply(dir);
	}

	dir.Normalize();   
	return dir;
}


