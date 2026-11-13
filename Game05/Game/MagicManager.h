#pragma once
#include "Magic.h"

class MagicManager
{
public:
	
	MagicManager();
	~MagicManager() {}

	void AddMagic(EnMagicType magicType);

	int CountMagic(EnMagicType magicType)const;


	/**指定した番号(0~2)のスロットに入っている魔法に返す*/
	EnMagicType GetNumberISlot(int slotNumber)const { return m_magicSlot[slotNumber]; }
	/**下で指定した魔法の基本ステ‐タスを返す*/
	AttackMagicStatus GetBaseStatus(EnMagicType magicType)const { return m_baseStatus[static_cast<int>(magicType)]; }
	/**指定した魔法のモデルパスを返す*/
	const char* GetModelPath(EnMagicType magicType)const { return m_modelPath[static_cast<int>(magicType)]; }

	/**今の魔法を取得している*/
	EnMagicType GetMagicType()const { return m_magicSlot[m_selectedSlot]; }

	/**UIに今選んでるスロットの番号を渡している*/
	int GetSelectedSlot()const { return m_selectedSlot; }

	/**セッター*/
	void SetSelectedSlot(int selectedSlot) { m_selectedSlot = selectedSlot; }

	/**魔法の残りのクールダウンを減らす*/
	void CoolDownLimit();

	/**撃てるかどうかを確認している*/
	bool IsReady(EnMagicType magicType)const;

	/**魔法を使っているかどうかの判定*/
	void UseMagic(EnMagicType magicType);

private:
	/**手に入れた魔法を全て覚えておくための一覧*/
	std::vector<EnMagicType> m_magicTypes;

	/**撃つための3つのスロット*/
	EnMagicType m_magicSlot[3];

	/**魔法ごとの基本ステータスを箱に格納物*/
	AttackMagicStatus m_baseStatus[static_cast<int>(EnMagicType::Max)];

	/**魔法の種類ごとのModelPath*/
	const char* m_modelPath[static_cast<int>(EnMagicType::Max)];

	/**魔法の種類ごとのクールダウン*/
	float m_coolDownTimer[static_cast<int>(EnMagicType::Max)] ;

	/**現在設定しているSlotを記憶している*/
	int m_selectedSlot = 0;
};

