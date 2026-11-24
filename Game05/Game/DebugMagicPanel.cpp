#include "stdafx.h"
#include "DebugMagicPanel.h"
#include "MagicManager.h"

void DebugMagicPanel::Init(MagicManager* magicManager)
{
	m_magicManager = magicManager;

	m_panel.Register("Game", "Magic", [this]() {
		Draw();
	});
}

void DebugMagicPanel::Draw()
{
	if (m_magicManager == nullptr)
	{
		ImGui::Text("MagicManager is nullptr");
		return;
	}

	//EnMagicType の順番どおりに名前を並べる（種類を増やしたらここにも足す）
	const char* magicNames[] = { "Stone", "Fire", "Ice" };
	static_assert(
		sizeof(magicNames) / sizeof(magicNames[0]) == static_cast<int>(EnMagicType::Max),
		"EnMagicType を増やしたら magicNames にも名前を足す"
	);

	//今持っているかを、種類ごとにチェックボックスに映す
	bool isHave[static_cast<int>(EnMagicType::Max)];
	bool isRemoved = false;

	for (int i = 0; i < static_cast<int>(EnMagicType::Max); i++)
	{
		EnMagicType magicType = static_cast<EnMagicType>(i);
		isHave[i] = m_magicManager->CountMagic(magicType) > 0;

		//クリックされたときだけ true になる
		if (ImGui::Checkbox(magicNames[i], &isHave[i]))
		{
			if (isHave[i])
			{
				m_magicManager->AddMagic(magicType);
			}
			else
			{
				isRemoved = true;
			}
		}
	}

	//外したときは、MagicManager を作りたての状態に戻して、
	//チェックが入っている魔法だけを入れ直す（MagicManager に外す関数を作らずに済ませるため）
	//本体の場所は変わらないので、Player や UI が持っているポインタはそのまま使える
	//※持っている個数・スロットの並び・選んでいる番号・クールダウンも最初に戻る
	if (isRemoved)
	{
		*m_magicManager = MagicManager();
		for (int i = 0; i < static_cast<int>(EnMagicType::Max); i++)
		{
			if (isHave[i])
			{
				m_magicManager->AddMagic(static_cast<EnMagicType>(i));
			}
		}
	}

	ImGui::Separator();

	//スロットの中身と、選んでいる番号
	for (int i = 0; i < 3; i++)
	{
		EnMagicType slotMagic = m_magicManager->GetNumberISlot(i);
		const char* slotName = "None";
		if (slotMagic != EnMagicType::None)
		{
			slotName = magicNames[static_cast<int>(slotMagic)];
		}
		const char* selectMark = (i == m_magicManager->GetSelectedSlot()) ? "<" : "";
		ImGui::Text("slot%d : %s %s", i, slotName, selectMark);
	}
}
