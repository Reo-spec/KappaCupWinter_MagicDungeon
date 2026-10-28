#pragma once
#include "Character.h"

class MagicSelectUI;

class Player :  public Character
{
public:
	Player();
	~Player();
	//移動処理。
	void Move();
	//回転処理。
	void Rotation();
	//ステート管理。
	void ManageState();
	//アニメーションの再生。
	void PlayAnimation();
	//回転回避の処理
	void Rolling();
	//魔法発射の処理関数
	void ShotMagic();
	//魔法発射の向きの計算用の関数
	Vector3 CalcMagicDirection();

	//移動用の向き参照(回転回避にも使用)
	Vector3 GetCameraDirection(float stickX, float stickY);

	//UIをいれるもの
	void SetUI(MagicSelectUI* magicSelectUI) { m_magicSelectUI = magicSelectUI; }

	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。
	
	int playerState = 0;	//プレイヤーのステート(状態)を表す変数。
private:

	//更新処理。
	void UpdateAction()override;

	MagicSelectUI* m_magicSelectUI = nullptr;

};

