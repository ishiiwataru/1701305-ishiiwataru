
#include <DxLib.h>
#include "main.h"
#include "keyCheck.h"
#include "player.h"
#include "enemy.h"
#include "map.h"

GAME_MODE gameMode;	// ｹﾞｰﾑﾓｰﾄﾞ宣言
int Tr = GetColor(255, 255, 255);
int Cnt = 0;
int time = GetNowCount();
// 関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言(画面遷移用の変数宣言)
void GameSystemInit();
void GameInit();
void GameTitle();
void GameMain();
void GameOver();
void GameClear();



// ---------- ﾒｲﾝ処理
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(true);	// ｳｲﾝﾄﾞｳﾓｰﾄﾞ
	SetWindowText("1701305_石井　航");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	if (DxLib_Init() == -1) return -1;	// 初期化と裏画面化
	SetDrawScreen(DX_SCREEN_BACK);

	GameSystemInit();
	gameMode = GAME_INIT;	// 最初の初期化を行う

	// ---------- ﾒｲﾝﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		ClsDrawScreen();

		CheckKey();		// ｷｰ状態をﾁｪｯｸする(毎回ﾙｰﾌﾟ)

		switch (gameMode)
		{
		case GAME_INIT:		// ｹﾞｰﾑ初期化(画像の読み込みなど)
			GameInit();
			break;
		case GAME_TITLE:// ﾀｲﾄﾙ画面
			Cnt++;
			if ((Cnt / 10 % 2) == 0)
			{
				DrawFormatString(200, 400, Tr, "PUSH A");
			}
			GameTitle();
			break;
		case GAME_MAIN:		// ｹﾞｰﾑﾒｲﾝ画面
			GameMain();
			break;
		case GAME_OVER:		// ｹﾞｰﾑｵｰﾊﾞｰ画面
			GameOver();
			break;
		case GAME_CLEAR:	// ｹﾞｰﾑｸﾘｱ画面
			GameClear();
			break;
		}
		ScreenFlip();
	}
	DxLib_End();	// DxLibの後始末
	return 0;	// ｿﾌﾄの終了
}

void GameSystemInit()
{
	gameMode = GAME_INIT;

	PlayerSystemInit();
	EnemySystemInit();
	MapSystemInit();

}

void GameInit()
{
	PlayerInit();
	EnemyInit();
	time = GetNowCount();
	gameMode = GAME_TITLE;
}

// ========== ﾀｲﾄﾙ画面の処理
void GameTitle()
{
	/*DrawFormatString(100, 100, 0xffffff, "タイトル画面");
	DrawFormatString(100, 150, 0xffffff, "Aボタンを押したらメイン画面に。");
	DrawFormatString(100, 200, 0xffffff, "Bボタンを押したらゲーム終了。");*/
	int title;
	
	title = LoadGraph("image/title.png");

	DrawGraph(130, 130, title, true);

	if (CheckHitKey(KEY_INPUT_A))
	{
		if ((Cnt / 10 % 2) == 0)
		{
			DrawFormatString(130, 400, Tr, "PUSH A");
		}
		DeleteGraph(title);
			gameMode = GAME_MAIN;
	}
	
	ScreenFlip();  //画面切り替え
}

// ========== ｹﾞｰﾑﾒｲﾝ処理
void GameMain()
{
	
	DrawFormatString(100, 0, GetColor(255, 255, 255), "残りtime %d",(43000 -(GetNowCount() - time))/1000);
	PlayerMain();
	EnemyMain();
	EnemyDraw();
	MapDraw();
	PlayerMain();
	PlayerDraw();

	//time -= 1;
	if ((43000 - (GetNowCount() - time)) / 1000 == 0)
	{
		gameMode = GAME_OVER;
		
	}
	
		if (player.score == 400)
		{
			gameMode = GAME_CLEAR;
		}
}

// ========== ｹﾞｰﾑｵｰﾊﾞｰ処理
void GameOver()
{
	DrawFormatString(100, 100, 0xffffff, "ゲームオーバー");
	DrawFormatString(100, 150, 0xffffff, "Aボタンを押したらタイトル画面に。");
	if (CheckHitKey(KEY_INPUT_A))
	{
		gameMode = GAME_INIT;	// ﾀｲﾄﾙ画面の前にｹﾞｰﾑの初期化
	}
	DrawString(0, 0, "OVER", 0xffff00);
}

// ========== ｹﾞｰﾑｸﾘｱ処理
void GameClear()
{
	DrawFormatString(100, 100, 0xffffff, "ゲームクリア");
	DrawFormatString(100, 150, 0xffffff, "Bボタンを押したらタイトル画面に。");
	if (CheckHitKey(KEY_INPUT_B))
	{
		gameMode = GAME_INIT;	// ﾀｲﾄﾙ画面の前にｹﾞｰﾑの初期化
	}
	DrawString(0, 0, "CLEAR", 0xffff00);
}

