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
- CC0 1.0（2026-11-05 確認、要約ページ）: https://creativecommons.org/publicdomain/zero/1.0/ 「You can copy, modify, distribute and perform the work, even for commercial purposes, all without asking permission.」クレジット表記は不要。作者が推薦しているように見せるのは禁止。無保証。法的な本文は https://creativecommons.org/publicdomain/zero/1.0/legalcode.en （未読）
- Poly Pizza 利用規約（2026-11-05 確認）: https://poly.pizza/docs/tos ダウンロードした素材は、そのときのクリエイティブ・コモンズのライセンスに従う。サイトの自動取得（スクレイピング）や AI の学習への利用は禁止
- Mixamo（Adobe）の FAQ（2026-11-06 確認）: 公式ページ https://helpx.adobe.com/creative-cloud/faq/mixamo-faq.html は 403 で読めなかった。読めたのはコミュニティに写された 2022 年の FAQ（https://community.adobe.com/t5/mixamo-discussions/mixamo-faq-licensing-royalties-ownership-eula-and-tos/td-p/13234775 、Adobe の社員の投稿ではない）だけ。そこでは「商用・非商用とも無料で使える」「クレジットは不要」「really the only thing you can't do is distribute the raw character and animation files」「You may not distribute the files to customers or non-team members」。変換したアニメのファイルが「raw」に入るかは書かれていない。改変・リターゲットについての記述もない → 今の規約は要確認

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
| `Assets/modelData/wizard.tkm`、`wizard.tks`、`wizard.dds`、`Assets/animData/wizard_idle/walk/run/jump/attack/damage/die.tka`（元ファイルは `Game05/AssetSource/wizard/`） | プレイヤーのモデル（星と月のローブの少年の魔法使い、杖つき）とテクスチャ | 元の絵（`Meshy_AI_Wizard Clean A-Pose.png`）と形・色は Meshy AI で生成（ユーザー、2026-11-03）。面の削減（214,780 → 10,000 面）・UV の作り直し・色のベイク（2048×2048）・tkm への変換、骨（21本）とアニメーション7つは Claude Code（Blender のスクリプト）。dds は学校のツールの texconv（BC7）で変換 | CC BY 4.0（**無料プランで生成**、Meshy が所有。2026-11-03 にユーザーが確認） | ○（Meshy の規約・CC BY 4.0 とも商用可）。ただし GFF の応募規約で AI 生成素材を使えるかは要確認 | **必要**：作者（Meshy）、CC BY 4.0 へのリンク、改変したこと。AI 生成であることも書く | ○（条件つき：リポジトリにクレジットの表記を一緒に入れる） | 2026-11-03。クレジットはこのファイルの「クレジット」に書いた。ユニティちゃんの差し替え用。元の絵が Meshy の画像生成かは、ファイル名（Meshy_AI_）からの判断 |
| `Assets/modelData/dungeonWall.tkm`、`dungeonWall.dds`（元ファイルは `Game05/AssetSource/wall/`） | 迷路の壁（「Wall Modular」、ローポリの石・レンガの壁。タグ：Wall / Brick / Stone / Dungeon）。2026-11-05 に Claude Code が Blender のスクリプト（`build_wall.py`）で加工：幅と高さを 400 に合わせた、隠れる裏の面を消した（1,672 → 1,090 枚）、色を 16×16 の色の表（dds）に移した。2026-11-07 に、色の表を手続き生成の石の肌のテクスチャ（512×512、`make_textures.py`）に替え、面の向きに合わせて投影する UV にした。へこんだ角のすき間をふさぐ平らなふたを板の両端に足した（1,094 枚）。同じスクリプトで作った当たり判定の箱 `dungeonWallCol.tkm`・迷路全体の床 `mazeFloor.tkm`・迷路全体の天井 `mazeCeiling.tkm`（2026-11-06）は外の素材を使っていない（自作扱い） | Quaternius（https://poly.pizza/u/Quaternius）。配布ページ：https://poly.pizza/m/itasw0GWNf（FBX / glTF） | CC0 1.0（パブリックドメイン） | ○ | 不要（入れるなら「Quaternius（CC0）」） | ○ | 2026-11-05 にライセンスを確認。ユーザーがダウンロードし、元ファイルを `Game05/AssetSource/wall/src/Wall_Modular.fbx` に置いた（zip の中身は FBX 1つだけ）。三角形 1,672 枚、大きさ 2×0.44×2、表裏とも石の模様。テクスチャ・UV はなく、色はマテリアル3つ（Wall_Dark・Wall_Medium・Wall_Highlights）。どのパックの一部かは書かれていない |
| `Assets/modelData/mazeFloor.dds`、`mazeCeiling.dds`、`dungeonWall.dds`（元の PNG とスクリプトは `Game05/AssetSource/wall/make_textures.py`） | 迷路の床（踏み固められた土に小石・半分埋まった石、1024×1024）・天井（岩、512×512）・壁の板（苔のついた石の肌、512×512）のテクスチャ。BC7 | ユーザーの依頼で Claude Code（Anthropic）が Python のスクリプトで手続き生成（ノイズと乱数で描いた。2026-11-07） | 自作扱い（Anthropic の利用規約では、出力の権利は利用者に帰属する） | ○ | 不要（AI で作ったことを書くかは、応募のルールに合わせる） | ○ | 2026-11-07。外部の画像・素材は使っていない。床は 4×4 マス（1600）、天井は 2×2 マス（800）で 1 回くり返す。同じ日に、壁に苔を足し、床を作り直した（くり返しを目立たなくし、壁の石と色が分かれるように土が主役の茶色に）。`dungeonWall.dds` は壁の元モデル（Quaternius、CC0）の色を参考にした |
| `Assets/animData/wizard_roll.tka`（スクリプトは `Game05/AssetSource/wizard/retarget_roll.py`） | プレイヤーのローリング回避のアニメーション | Mixamo（Adobe）の「Stand To Roll」 | Mixamo の利用条件（上の「参照した規約」） | ○（2022 年の FAQ の写しによる。今の規約は要確認） | 不要（同上） | ?（要確認。アニメの元ファイルの配布とチーム外の人へ渡すことは禁止。変換した tka を公開リポジトリに上げるとこれに当たるおそれ → コミットせず `.gitignore` に入れることを提案中） | 2026-11-06。改変：魔法使いの骨（21本）にリターゲット（T ポーズと A ポーズの違いは骨の向きを合わせて吸収）、前へ進む動きを消してその場で転がる形に、最初と最後の立っている所を削って 1.5 倍速に（72 → 41 フレーム）、最初と最後を idle の 0 フレームに合わせた、杖を転がっている間は水平に寝かせた、体を地面に合わせた。入手方法：Mixamo で「Stand To Roll」を FBX でダウンロード → `blender -b wizardAnim.blend --python retarget_roll.py -- <fbx のパス>`（fbx はリポジトリにも AssetSource にも置いていない） |
| `Assets/modelData/treasureChest.tkm`、`treasureChestOpen.tkm`、`treasureChestCol.tkm`、`treasureChest.dds`（スクリプトと元ファイルは `Game05/AssetSource/treasureChest/`） | 宝箱（閉じた形・ふたが開いた形・当たり判定の箱）とテクスチャ | 形とテクスチャの元の絵は**自作**（立花玲穏。以前のプロジェクト Game02 の `takaraBako.tkm`、3ds Max の元ファイル `karihako.max`、テクスチャの元の絵 `chest_Top2.png`。2026-11-09 にユーザーが「自作」と確認）。2026-11-09 に Claude Code が Blender のスクリプト（`build_chest.py`）で加工：ふたと箱を 1 つにまとめた、原点を床の高さ・真ん中に、1.25 倍、ふたを 110 度開いた形を追加、当たり判定の箱を追加。テクスチャは元の絵の色の配置（UV）のまま、木目・板の継ぎ目・金具の陰影をスクリプトで描き足した（1024×1024、BC7）。黄色一色の `hako.DDS`（863×1542）は使わず、その面は同じテクスチャの金具の色を指すようにした | 自作 | ○ | 不要 | ○ | 2026-11-09。外部の素材は使っていない |

## クレジット

このリポジトリとゲームに含まれる、表記が必要な素材。

### プレイヤーのモデル（wizard）

- 対象：`Game05/Game/Assets/modelData/wizard.tkm`、`wizard.tks`、`wizard.dds`、`Game05/Game/Assets/animData/wizard_idle.tka`、`wizard_walk.tka`、`wizard_run.tka`、`wizard_jump.tka`、`wizard_attack.tka`、`wizard_damage.tka`、`wizard_die.tka`
- 元のモデル：Meshy（https://www.meshy.ai/）の AI で生成（無料プラン、2026-11-03）。著作権者は Meshy
- ライセンス：Creative Commons Attribution 4.0 International（CC BY 4.0） https://creativecommons.org/licenses/by/4.0/
- 改変：面の数を減らした（214,780 → 10,000 面）、UV を作り直して元の色をベイクした（2048×2048）、大きさと向きを変えた、骨（21本）とアニメーション（Idle・Walk・Run・Jump・Attack・Damage・Die）を付けた、k2Engine の形式（tkm・tks・tka・dds）に変換した。改変は Claude Code（Anthropic）が Blender のスクリプトで行った
- 無保証：CC BY 4.0 のとおり、元の素材は無保証で提供されている

### 炎の敵のモデル（fireSlime）

- 対象：`Game05/Game/Assets/modelData/fireSlime.tkm`、`fireSlime.dds`、`fireSlimeAnim.tkm`、`fireSlimeAnim.tks`、`Game05/Game/Assets/animData/fireSlime_idle.tka`、`fireSlime_attack.tka`、`fireSlime_move.tka`、`fireSlime_die.tka`
- 元のモデル：Meshy（https://www.meshy.ai/）の AI で生成（無料プラン、2026-10-29）。著作権者は Meshy
- ライセンス：Creative Commons Attribution 4.0 International（CC BY 4.0） https://creativecommons.org/licenses/by/4.0/
- 改変：面の数を減らした（119,294 → 6,000 面）、UV を付けた、炎の色のテクスチャを描いた、骨（16本）とアニメーション（Idle・Attack・Move・Die）を付けた、k2Engine の形式（tkm・tks・tka・dds）に変換した。改変は Claude Code（Anthropic）が Blender のスクリプトで行った
- 無保証：CC BY 4.0 のとおり、元の素材は無保証で提供されている
