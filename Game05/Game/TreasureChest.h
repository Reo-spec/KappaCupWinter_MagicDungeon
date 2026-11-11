#pragma once
#include "Magic.h"

class Player;
class MagicManager;

class TreasureChest:public IGameObject
{
public:

	TreasureChest() {};
	~TreasureChest() {};

	bool Start()override;
	void Update()override;

	void Render(RenderContext& rc)override;

	//Positionと魔法の中身とRotationと松明を渡す用
	void SetPosition(const Vector3& position);
	void SetRotation(const Quaternion& rotation);
	void SetContents(EnMagicType magicType);
	void SetTorch();

	/**セッター*/
	void SetMagicManager(MagicManager* magicManager) { m_magicManager = magicManager; }

protected:

private:
	EnMagicType m_magicType = EnMagicType::None;

	bool m_torch = false;
	bool m_openChest = false;

	Vector3 m_position;
	Quaternion m_rotation;

	ModelRender m_closeChestRender;
	ModelRender m_openChestRender;

	ModelRender m_chestCollisionRender;

	PhysicsStaticObject m_chestCollision;

	Player* m_player = nullptr;
	MagicManager* m_magicManager = nullptr;
};

