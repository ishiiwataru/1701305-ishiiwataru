#pragma once
#include "main.h"
#define SCREEN_SIZE_X 512
#define SCREEN_SIZE_Y 480

#define PLAYER_SIZE_X 16
#define PLAYER_SIZE_Y 24

#define ENEMY_SIZE_X 16
#define ENEMY_SIZE_Y 24

//#define MAP_CHIP_X 30	// �w�i���߂̉��̕��ѐ�
//#define MAP_CHIP_Y 30	// �w�i���߂̏c�̕��ѐ� 

// ---------- ��ʑJ�ڂ��Ǘ����閼�̂��`(GAME_MODE�^�Ƃ��Ċ��p)
typedef enum
{
	GAME_INIT,		// �ްъJ�n���̏�����
	GAME_TITLE,		// �ް����ُ���
	GAME_MAIN,		// �ް�Ҳݏ���
	GAME_OVER,		// �ްѵ��ް����
	GAME_CLEAR,		// �ްѸر����
	GAME_END		// �ްяI��
}GAME_MODE;

// ---------- �\���̂̐錾
typedef struct
{
	float x;
	float y;
}XY;

typedef struct
{
	XY pos;	// �ŏI�I�ȍ��W(�Փ˔����)
	XY tmp;	// �v�Z�p�̍��W(�Փ˔���O)
	XY mov;	// �ړ���
	int	LR;	// 1:�E�A-1:��
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

// ��۰��ٕϐ��Ƃ��Ă�extern�錾
extern GAME_MODE gameMode;	// ��ʑJ�ڗp
extern CHARA_DATA player;
extern CHARA_DATA enemy[4];
