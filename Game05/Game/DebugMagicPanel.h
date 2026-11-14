#pragma once

class MagicManager;

/**
 * デバッグGUI：魔法を持つ・持たないをチェックボックスで切り替えるパネル
 * F1 → メニューの Game → Magic で開く
 * Game がメンバ変数で持ち、Start で Init を呼ぶ（Game が消えるとパネルの登録も消える）
 */
class DebugMagicPanel
{
public:
	/**パネルを登録する。いじる MagicManager を受け取る*/
	void Init(MagicManager* magicManager);

private:
	/**パネルの中身を描く（ImGui はここの中だけで使う）*/
	void Draw();

	/**いじる MagicManager（Game の本体を指す）*/
	MagicManager* m_magicManager = nullptr;

	/**エンジンのパネル。消えると登録も自動で消える*/
	DebugGuiPanel m_panel;
};
