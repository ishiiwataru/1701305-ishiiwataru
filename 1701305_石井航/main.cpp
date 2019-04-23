
#include <DxLib.h>
#include "main.h"
#include "keyCheck.h"
#include "player.h"
#include "enemy.h"
#include "map.h"

GAME_MODE gameMode;	// �ް�Ӱ�ސ錾
int Tr = GetColor(255, 255, 255);
int Cnt = 0;
int time = GetNowCount();
// �֐��������ߐ錾(��ʑJ�ڗp�̕ϐ��錾)
void GameSystemInit();
void GameInit();
void GameTitle();
void GameMain();
void GameOver();
void GameClear();



// ---------- Ҳݏ���
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(true);	// ����޳Ӱ��
	SetWindowText("1701305_�Έ�@�q");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	if (DxLib_Init() == -1) return -1;	// �������Ɨ���ʉ�
	SetDrawScreen(DX_SCREEN_BACK);

	GameSystemInit();
	gameMode = GAME_INIT;	// �ŏ��̏��������s��

	// ---------- Ҳ�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		ClsDrawScreen();

		CheckKey();		// ����Ԃ���������(����ٰ��)

		switch (gameMode)
		{
		case GAME_INIT:		// �ްя�����(�摜�̓ǂݍ��݂Ȃ�)
			GameInit();
			break;
		case GAME_TITLE:// ���ى��
			Cnt++;
			if ((Cnt / 10 % 2) == 0)
			{
				DrawFormatString(200, 400, Tr, "PUSH A");
			}
			GameTitle();
			break;
		case GAME_MAIN:		// �ް�Ҳ݉��
			GameMain();
			break;
		case GAME_OVER:		// �ްѵ��ް���
			GameOver();
			break;
		case GAME_CLEAR:	// �ްѸر���
			GameClear();
			break;
		}
		ScreenFlip();
	}
	DxLib_End();	// DxLib�̌�n��
	return 0;	// ��Ă̏I��
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

// ========== ���ى�ʂ̏���
void GameTitle()
{
	/*DrawFormatString(100, 100, 0xffffff, "�^�C�g�����");
	DrawFormatString(100, 150, 0xffffff, "A�{�^�����������烁�C����ʂɁB");
	DrawFormatString(100, 200, 0xffffff, "B�{�^������������Q�[���I���B");*/
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
	
	ScreenFlip();  //��ʐ؂�ւ�
}

// ========== �ް�Ҳݏ���
void GameMain()
{
	
	DrawFormatString(100, 0, GetColor(255, 255, 255), "�c��time %d",(43000 -(GetNowCount() - time))/1000);
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

// ========== �ްѵ��ް����
void GameOver()
{
	DrawFormatString(100, 100, 0xffffff, "�Q�[���I�[�o�[");
	DrawFormatString(100, 150, 0xffffff, "A�{�^������������^�C�g����ʂɁB");
	if (CheckHitKey(KEY_INPUT_A))
	{
		gameMode = GAME_INIT;	// ���ى�ʂ̑O�ɹްт̏�����
	}
	DrawString(0, 0, "OVER", 0xffff00);
}

// ========== �ްѸر����
void GameClear()
{
	DrawFormatString(100, 100, 0xffffff, "�Q�[���N���A");
	DrawFormatString(100, 150, 0xffffff, "B�{�^������������^�C�g����ʂɁB");
	if (CheckHitKey(KEY_INPUT_B))
	{
		gameMode = GAME_INIT;	// ���ى�ʂ̑O�ɹްт̏�����
	}
	DrawString(0, 0, "CLEAR", 0xffff00);
}

