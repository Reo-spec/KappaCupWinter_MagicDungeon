# Player クラスのレビュー

- **開始**：2026-10-23
- **状態**：保留（弾を消す話を先に進める）
- **段階**：—（レビューのみ。直し方の質問はまだ）
- **関連**：`Game05/Game/Player.h`、`Game05/Game/Player.cpp`

## 内容

`ShotMagic()` 以外に気づいた点を伝えた。

- RB2 で「撃つ」と「ダッシュ」が両方動く
- `int dashMagnification = 1.0f;`（float を int に入れている）
- 使っていないもの（`stickL`、コメントアウト、`#include "Bullet.h"`）→ R-09
- `Roring` → `Rolling`（R-08）、メンバ変数の `m_` 抜け（R-04）、メンバが全部 public
- マジックナンバー（240、23、30、50、100）、`1.0f / 60.0f` の固定値
