# NewGO の弾を時間切れで消す

- **開始**：2026-10-23
- **状態**：保留（時間切れで消す処理は書けた。起動しての確認と、残りのことはまだ）
- **段階**：時間切れの処理の移動は3回目まで済み。「弾が出ない」バグは1回目（ヒント）で解決。残りのこと（`delete`、`nullptr` チェック）はまだ質問されていないので、聞かれたら1回目から
- **関連**：`Game05/Game/Magic.cpp`、`Game05/Game/Player.cpp`、Notion「石を飛ばす魔法の実装」

## 内容

オブジェクトプールをやめて、`NewGO<AttackMagic>` で撃つ形に戻した。時間切れの処理が `Player::ShotMagic()` に入っていて、ビルドエラー（`m_lifeTime` が未定義）になっている。3回目で次の手順を伝えた。

1. Player の時間切れの6行を切り取り、`AttackMagic::Update()` の最後に貼る
2. `m_lifeTime` を `As()->m_lifeTime` にする
3. Player で `status.m_lifeTime` にも寿命と同じ値を入れる

### 2026-10-24：ユーザーが時間切れの処理を書いた → 弾が出なくなった

- 時間切れの処理は `AttackMagic::Update()` に移せた。寿命は「`m_lifeTime` を 0 から増やして `m_maxLifeTime` と比べる」やり方にした
- 弾が出ない原因を見つけたので、ヒントだけ伝えた（新しいバグなので1回目から。答えはまだ出していない）
  - `Magic.cpp` 24行目の `if` の比較の向き
  - `m_lifeTime` に初期値がない（`Magic.h` 34行目、Player 側でも入れていない）
- ヒント1（比較の向き）はユーザーが `>=` に直した
- ヒント2もユーザーが直した（`Magic.h` で `m_lifeTime = 0.0f`）。これで撃った弾が3秒後に消える形になった。実際に起動しての確認はまだ
- ついでに伝えたこと：`AttackMagic` の `m_status` が `IMagic` の `m_status` と同じ名前で別の変数になっている（`Magic.h` 78行目）

## 分かったこと

- 関数の中の `this` は「そのクラスの自分」。Player の中で `DeleteGO(this)` するとプレイヤーが消える
- 毎フレーム数える処理は、ボタンの `if` の中ではなく `Update()` に書く
- 初期値のない変数は Debug で 0xCCCCCCCC（float だと約 -1 億）になる
- 「時間が来たら消す」は `経った時間 >= 寿命` で書く。`<=` だと最初のフレームで消えて「弾が出ない」ように見える
- 数え始める値（経った時間 = 0）は、構造体の宣言で `= 0.0f` と入れておけば、作るたびに入れ忘れない

## 残っていること

- `new AttackMagicStatus` の `delete`（デストラクタ）
- `nullptr` チェックの位置（`Player::ShotMagic()` で、`magic->Init()` の後にチェックしている）
- 起動して、弾が約3秒で消えるかの確認
- `AttackMagicStatus` の残りのメンバ（`m_moveSpeed`、`m_attackValue`、`m_maxLifeTime`）に初期値がない
- 規約：構造体のメンバの `m_`（R-05）、Player のコメントアウト（R-09）、`Magic.cpp` の古い TODO コメント
