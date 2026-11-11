#pragma once
#include "Character.h"

class MagicManager;

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

	/**MagicManagerをいれるもの*/
	void SetMagicManager(MagicManager* magicManager) { m_magicManager = magicManager; }

	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Attack,
		enAnimationClip_Damage,
		enAnimationClip_Die,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。
	
	int playerState = 0;	//プレイヤーのステート(状態)を表す変数。
private:

	//更新処理。
	void UpdateAction()override;

	MagicManager* m_magicManager = nullptr;

};

