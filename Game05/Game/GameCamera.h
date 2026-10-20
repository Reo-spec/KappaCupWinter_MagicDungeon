#pragma once
//ばねカメラを採用
#include "camera/SpringCamera.h"

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start() override;
	void Update() override;

	Player* m_player;	//プレイヤー。
	Vector3 m_toCameraPos = { 0.0f, 0.0f, 0.0f };	//注視点から視点に向かうベクトル。
	SpringCamera m_springCamera;	//ばねカメラ。
	
};

