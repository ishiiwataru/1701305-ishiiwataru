#pragma once
#include "main.h"
#define SCREEN_SIZE_X 512
#define SCREEN_SIZE_Y 480

#define PLAYER_SIZE_X 16
#define PLAYER_SIZE_Y 24

#define ENEMY_SIZE_X 16
#define ENEMY_SIZE_Y 24

//#define MAP_CHIP_X 30	// 背景ﾁｯﾌﾟの横の並び数
//#define MAP_CHIP_Y 30	// 背景ﾁｯﾌﾟの縦の並び数 

// ---------- 画面遷移を管理する名称を定義(GAME_MODE型として活用)
typedef enum
{
	GAME_INIT,		// ｹﾞｰﾑ開始時の初期化
	GAME_TITLE,		// ｹﾞｰﾑﾀｲﾄﾙ処理
	GAME_MAIN,		// ｹﾞｰﾑﾒｲﾝ処理
	GAME_OVER,		// ｹﾞｰﾑｵｰﾊﾞｰ処理
	GAME_CLEAR,		// ｹﾞｰﾑｸﾘｱ処理
	GAME_END		// ｹﾞｰﾑ終了
}GAME_MODE;

// ---------- 構造体の宣言
typedef struct
{
	float x;
	float y;
}XY;

typedef struct
{
	XY pos;	// 最終的な座標(衝突判定後)
	XY tmp;	// 計算用の座標(衝突判定前)
	XY mov;	// 移動量
	int	LR;	// 1:右、-1:左
	int flag;
	int	counter;
	int	wing, walk;
	int bite;
	int jumpPowMax;
	int acc;
	int jumpFlag;
	int G;
	int jumpPow;
	int fallMax;
	bool flg;
	int	life;
	int hitFlag;
	int air;
	int damageflag;
	int score;
	int scoreflag;

}CHARA_DATA;

// ｸﾞﾛｰﾊﾞﾙ変数としてのextern宣言
extern GAME_MODE gameMode;	// 画面遷移用
extern CHARA_DATA player;
extern CHARA_DATA enemy[4];
