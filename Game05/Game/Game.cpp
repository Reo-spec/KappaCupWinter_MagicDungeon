#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "GameCamera.h"
#include "Magic.h"
#include "MagicSelectUI.h"
#include "MagicManager.h"
#include "Enemy.h"

bool Game::Start()
{

	m_map = NewGO<Map>(0, "map");

	/**宝箱に魔法を渡すためにMAPを経由している*/
	m_map->SetMagicManager(&m_magicManager);

	m_player = NewGO<Player>(0, "player");

	/**プレイヤーが魔法を聞く*/
	m_player->SetMagicManager(&m_magicManager);

	m_player->SetMap(m_map);

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_msUI = NewGO<MagicSelectUI>(0, "magicSelectUI");

	m_msUI->SetMagicManager(&m_magicManager);

	m_fireEnemy = NewGO<FireEnemy>(0, "fireEnemy");

	m_fireEnemy->Init(Vector3(800.0f, 0.0f, 600.0f));

	m_fireEnemy->SetPlayer(m_player);

	/**ゲームが炎の敵のファイルパスとステータスを取り出して渡している*/
	m_fireEnemy->SetMagicStatusAndPath(m_magicManager.GetBaseStatus(EnMagicType::Fire),m_magicManager.GetModelPath(EnMagicType::Fire));

	m_fireEnemy->SetMap(m_map);

	/**デバッグGUI：魔法を持つ・持たないをチェックボックスで切り替える*/
	m_debugMagicPanel.Register("Game", "Magic", [this]() {
		//EnMagicType の順番どおりに名前を並べる（種類を増やしたらここにも足す）
		const char* magicNames[] = { "Stone", "Fire" };
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
			isHave[i] = m_magicManager.CountMagic(magicType) > 0;

			//クリックされたときだけ true になる
			if (ImGui::Checkbox(magicNames[i], &isHave[i]))
			{
				if (isHave[i])
				{
					m_magicManager.AddMagic(magicType);
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
			m_magicManager = MagicManager();
			for (int i = 0; i < static_cast<int>(EnMagicType::Max); i++)
			{
				if (isHave[i])
				{
					m_magicManager.AddMagic(static_cast<EnMagicType>(i));
				}
			}
		}

		ImGui::Separator();

		//スロットの中身と、選んでいる番号
		for (int i = 0; i < 3; i++)
		{
			EnMagicType slotMagic = m_magicManager.GetNumberISlot(i);
			const char* slotName = "None";
			if (slotMagic != EnMagicType::None)
			{
				slotName = magicNames[static_cast<int>(slotMagic)];
			}
			const char* selectMark = (i == m_magicManager.GetSelectedSlot()) ? "<" : "";
			ImGui::Text("slot%d : %s %s", i, slotName, selectMark);
		}
	});

	return true;
}

void Game::Update()
{
	m_magicManager.CoolDownLimit();
}

void Game::Render(RenderContext&rc)
{


}