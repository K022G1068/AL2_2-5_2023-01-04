#include <Novice.h>
#include"Particle.h"

const char kWindowTitle[] = "K022G1068";
const int kWindowWidth = 600;
const int kWindowHeight = 600;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Particle* particle = new Particle(100, 300, 300, 120, 25, 1, 1);
	int graph = Novice::LoadTexture("./particle.jpg");
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::DrawBox(0, 0, 600, 600, 0, BLACK, kFillModeSolid);
		///
		/// ↓更新処理ここから
		///
		particle->Update(keys, preKeys);
		///
		/// ↑更新処理ここまで
		///
		particle->Draw(graph);
		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
