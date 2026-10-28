#include "stdafx.h"
#include "Player.h"
#include "Magic.h"
#include "MagicSelectUI.h"

Player::Player() {
	
	//アニメーションクリップをロードする。
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);

	//ユニティちゃんのモデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	//キャラコンを初期化する。
	characterController.Init(25.0f, 75.0f, m_position);

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
	//PlayAnimation();

	//絵描きさんの更新処理。
	m_modelRender.Update();

}

void Player::Move() 
{
	//ダッシュ用の関数
	int dashMagnification = 1.0f;

	if (g_pad[0]->IsPress(enButtonB) or g_pad[0]->IsPress(enButtonRB2))
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

	//重力を発生させる。
	m_moveSpeed.y -= 23.0f;

	//キャラクターコントローラーを使って座標を移動させる。
	m_position = characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);


}

void Player::ManageState()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ステートを2(歩き)にする。
		playerState = 2;
		if (g_pad[0]->IsPress(enButtonB) or g_pad[0]->IsPress(enButtonRB2))
		{
			playerState = 3;
		}
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		playerState = 0;
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
			characterController.SetPosition(m_position);
			m_modelRender.SetPosition(m_position);
		}
	}
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
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
		//UIが渡されていないときは撃たない
		if (m_magicSelectUI == nullptr) {
			return;
		}
		
		//向いてる方向をとる
		Vector3 magicDir = CalcMagicDirection();

		Vector3 magicPos = m_position + magicDir * 50.0f;
		magicPos.y += 100.0f;
		
		//UIで選んでいる魔法を聞く
		EnMagicType currentMagic = m_magicSelectUI->GetMagicType();

		//魔法の種類ごとにモデルとステータスを決める
		const char* modelPath = nullptr;
		AttackMagicStatus status;


		switch (currentMagic) {
			case EnMagicType::Stone:
		
				//TODO(仕様未定) 石の数値
				modelPath = "Assets/modelData/kariFireMagic.tkm";
				status.m_maxLifeTime = 3.0f;
				status.m_maxCoolDown = 3.0f;
				status.m_moveSpeed = 500.0f;
				break;
			case EnMagicType::Fire:
				modelPath = "Assets/modelData/kariFireMagic.tkm";
				// TODO(仕様未定) 炎の数値
				status.m_maxLifeTime = 3.0f;
				status.m_maxCoolDown = 3.0f;
				status.m_moveSpeed = 1000.0f;
				break;
			default:
				return;

		}

		AttackMagic* magic = NewGO<AttackMagic>(0, "magic");

		if (magic == nullptr) {
			return;
		}
		magic->Init(modelPath, status);
		magic->SetPositionAndDirection(magicPos, magicDir);

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


