# アセットのライセンス一覧

ゲームで使うアセット（モデル・テクスチャ・アニメーション・音・フォントなど）の出所とライセンスをまとめる。
新しいアセットを入れるときは、ここに 1 行追加してから使う。GitHub のリポジトリは公開なので、「再配布」が × や ? のものは push しない。

- 再配布：○ = GitHub に上げてよい / × = 上げてはいけない（`.gitignore` に入れる） / ? = 未確認
- 「要確認」のものは、配布元とライセンスを確認して埋める

## 参照した規約

- Google 利用規約（2026-07-30 発効）: https://policies.google.com/terms 「Google won't claim ownership over that content.」
- Google 生成 AI の使用禁止ポリシー（2024-12-17 更新）: https://policies.google.com/terms/generative-ai/use-policy 4.5「生成物を人間だけが作ったと偽ること」の禁止、1.6「他者の知的財産権の侵害」の禁止
- ユニティちゃんライセンス: https://unity3d.jp/unity-chan/license?lang=ja （本文は未確認）
- Meshy 利用規約（2026-09-19 更新）: https://www.meshy.ai/terms-of-use §3.2「無料プランの出力は Meshy が所有し、Meshy へのクレジット表記を条件に CC BY 4.0 で提供」、有料プランは利用者が所有。§2.4 出力内の識別情報（メタデータ・透かし）を消すことの禁止。料金ページ（https://www.meshy.ai/pricing）の FAQ では無料プランも商用利用可（クレジット表記あり）
- CC BY 4.0（2026-10-29 確認）: https://creativecommons.org/licenses/by/4.0/legalcode.ja 商用を含む共有・改変 OK。共有するときは §3(a) に従って、作者の表示・ライセンスへのリンク・改変したことの表示が必要（「合理的な方法」でよく、必要な情報をまとめたファイルやリンクでも満たせる）。追加の制限をかけるのは禁止

## 一覧

| ファイル | 中身 | 配布元・作者 | ライセンス | 商用・GFF 応募 | クレジット表記 | 再配布 | 確認日・メモ |
|---|---|---|---|---|---|---|---|
| `Assets/shader/` 一式 | エンジンのシェーダー | 学校配布（k2Engine） | 学校の配布物 | 要確認 | 要確認 | ? | 学校の配布物を公開してよいか先生に確認する |
| `Assets/modelData/preset/` 一式 | エンジンの初期モデル・空のテクスチャ・スカイボックス | 学校配布（k2Engine） | 学校の配布物 | 要確認 | 要確認 | ? | 同上 |
| `Assets/font/myfile.spritefont` | フォント | 要確認 | 要確認 | 要確認 | 要確認 | ? | 元になったフォントを確認する |
| `Assets/modelData/unityChan.*`、`utc_*.DDS` | プレイヤーのモデルとテクスチャ（ユニティちゃん） | ユニティ・テクノロジーズ・ジャパン（学校配布で入手） | ユニティちゃんライセンス条項（UCL） | 要確認 | 必要（要確認） | ? | **公開リポジトリにすでに push 済み**。学校配布でも、ライセンスは UCL のまま。2026-10-23 に https://unity3d.jp/unity-chan/license?lang=ja を読もうとしたが、本文がページから取得できず未確認。ブラウザで本文を読むか、先生に「公開リポジトリに上げてよいか」を確認する。**後で別のモデルに差し替える予定（2026-10-23 時点）** |
| `Assets/animData/*.tka` | プレイヤーのアニメーション（idle / walk / run / jump） | 要確認 | 要確認 | 要確認 | 要確認 | ? | ユニティちゃんのモーションかどうか確認する |
| `Assets/modelData/Map.DDS` | 仮のマップの床のテクスチャ（うすい青の方眼） | 元は自作（立花玲穏）の緑一色。2026-10-28 にユーザーの依頼で Claude Code がスクリプトで描き直した（256×256。Unity などの試作用グリッドに似せた見た目だが、画像は一から描いたもので、Unity の素材は使っていない） | 自作扱い | ○ | 不要 | ○ | 2026-10-28 |
| `Assets/modelData/kariMap.tkm`、`kariWall.dds` | 仮のマップ（一辺 8000 の床＋7×7 マスの迷路の区画）と壁のテクスチャ | ユーザーの依頼で Claude Code（Anthropic）がスクリプトで生成（2026-10-28）。以前の kariMap.tkm（自作）を上書き | 自作扱い（Anthropic の利用規約では、出力の権利は利用者に帰属する） | ○ | 不要（AI で作ったことを書くかは、応募のルールに合わせる） | ○ | 2026-10-28。外部の素材は使っていない（床は Map.DDS、壁の模様はスクリプトで描いた）。2026-10-29 に床の上の面を 400 ごとのマス目（三角形 800 枚）に分け直した（大きな三角形2枚だとプレイヤーが床をすり抜けたため） |
| `Assets/modelData/kariFireMagic.tkm`、`fireMagic.DDS` | 仮の炎の魔法 | 要確認（自作？） | 要確認 | 要確認 | 要確認 | ? | |
| `Assets/modelData/bg.tkm`、`ground.*`、`building.DDS` | 背景・地面 | 要確認（学校配布のサンプル？） | 要確認 | 要確認 | 要確認 | ? | |
| `Assets/MagicIcon/*.DDS` | 魔法のアイコン、魔法選択リング | Google Gemini で生成（AI 生成） | Google 利用規約・生成 AI の使用禁止ポリシー | ○（条件あり） | AI 生成であることを明記する | ○ | 2026-10-23 確認。Google は生成物の所有権を主張しない。ただし、生成物を人間だけが作ったと偽ることは禁止なので、クレジットや応募書類に「Gemini で生成」と書く。既存キャラクターや実在の人物に似せた画像は不可。規約に「再配布を禁止する」文言はない。まだコミットしていない |
| `Assets/modelData/fireSlime.tkm`、`fireSlime.dds`、`fireSlimeAnim.tkm`、`fireSlimeAnim.tks`、`Assets/animData/fireSlime_idle/attack/move/die.tka`（元ファイルは `Game05/AssetSource/fireSlime/`） | 炎の敵のモデル（炎の怪物）と炎の色のテクスチャ | 形は Meshy AI で生成（ユーザー、2026-10-29）。面の削減（119,294 → 6,000 面）・UV・テクスチャ（スクリプトで描いた炎のグラデーション）・tkm への変換は Claude Code（Blender）。骨（16本）とアニメーション4つ（Idle・Attack・Move・Die）も Claude Code が Blender のスクリプトで作成 | CC BY 4.0（**無料プランで生成**、Meshy が所有。2026-10-29 にユーザーが確認） | ○（Meshy の規約・CC BY 4.0 とも商用可）。ただし GFF の応募規約で AI 生成素材を使えるかは要確認 | **必要**：作者（Meshy）、CC BY 4.0 へのリンク、改変したこと（面の削減・UV・テクスチャ・骨とアニメーションの追加）。AI 生成であることも書く | ○（条件つき：リポジトリにクレジットの表記を一緒に入れる） | 2026-10-29。クレジットはこのファイルの「クレジット」に書いた（2026-10-29）。面の削減などの加工が §2.4 に当たるかは規約から判断できない |

## クレジット

このリポジトリとゲームに含まれる、表記が必要な素材。

### 炎の敵のモデル（fireSlime）

- 対象：`Game05/Game/Assets/modelData/fireSlime.tkm`、`fireSlime.dds`、`fireSlimeAnim.tkm`、`fireSlimeAnim.tks`、`Game05/Game/Assets/animData/fireSlime_idle.tka`、`fireSlime_attack.tka`、`fireSlime_move.tka`、`fireSlime_die.tka`
- 元のモデル：Meshy（https://www.meshy.ai/）の AI で生成（無料プラン、2026-10-29）。著作権者は Meshy
- ライセンス：Creative Commons Attribution 4.0 International（CC BY 4.0） https://creativecommons.org/licenses/by/4.0/
- 改変：面の数を減らした（119,294 → 6,000 面）、UV を付けた、炎の色のテクスチャを描いた、骨（16本）とアニメーション（Idle・Attack・Move・Die）を付けた、k2Engine の形式（tkm・tks・tka・dds）に変換した。改変は Claude Code（Anthropic）が Blender のスクリプトで行った
- 無保証：CC BY 4.0 のとおり、元の素材は無保証で提供されている
