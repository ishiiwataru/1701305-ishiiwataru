#include <DxLib.h>
#include "player.h"
#include "main.h"
#include "keyCheck.h"
#include "hitCheck.h"



int imgPlayer[2][14];
CHARA_DATA player;

void PlayerSystemInit()
{
	int tmp = LoadGraph("image/playerimage.png");

	//�H�΂������D1��
	imgPlayer[0][0] = DerivationGraph(0, 0, 32, 48, tmp);	//1
	imgPlayer[0][1] = DerivationGraph(32, 0, 32, 48, tmp);	//2
	imgPlayer[0][2] = DerivationGraph(64, 0, 32, 48, tmp);	//3
	imgPlayer[0][3] = imgPlayer[0][1];	//4(2�Ɠ��l�j


	//�������D�P��
	imgPlayer[0][10] = DerivationGraph(96, 0, 32, 48, tmp);
	imgPlayer[0][11] = DerivationGraph(128, 0, 32, 48, tmp);
	imgPlayer[0][12] = DerivationGraph(160, 0, 32, 48, tmp);
	imgPlayer[0][13] = DerivationGraph(192, 0, 32, 48, tmp);

	//�H�΂������D�Q��
	imgPlayer[1][0] = DerivationGraph(0, 48, 32, 48, tmp);
	imgPlayer[1][1] = DerivationGraph(32, 48, 32, 48, tmp);
	imgPlayer[1][2] = DerivationGraph(64, 48, 32, 48, tmp);
	imgPlayer[1][3] = imgPlayer[1][1];
	//�������D�Q��
	imgPlayer[1][10] = DerivationGraph(96, 48, 32, 48, tmp);
	imgPlayer[1][11] = DerivationGraph(96 + 32, 48, 32, 48, tmp);
	imgPlayer[1][12] = DerivationGraph(128 + 32, 48, 32, 48, tmp);
	imgPlayer[1][13] = DerivationGraph(160 + 32, 48, 32, 48, tmp);


	//

}

// --------------------
// ��ڲ԰����������
// --------------------
void PlayerInit()
{
	player.flag = 0;
	player.pos.x = 3 * 16;
	player.pos.y = 25*16;
	player.mov.x = 0.0f;
	player.mov.y = 0.0f;

	player.hitFlag;
	player.score = 0;
	player.scoreflag = true;
	player.LR = 1;
	//player.acc = 0.15f;
	//player.speed = 0.0f;
	//player.speedMax = 4.0f;

	player.counter = 0;
}

// --------------------
// Ҳݏ���
// --------------------
void PlayerMain()
{

	// �L�[���͂��������ꍇ
	player.wing = 1;
	if (newKey[_1UP])
		//if(CheckHitKey(KEY_INPUT_UP))
	{
		player.mov.y -= 0.1f; // �㏸����
		if (player.mov.y < -2.0f)
		{
			player.mov.y = -2.0f;	// ����ő�l
		}
		//if (player.pos.y > SCREEN_SIZE_Y - PLAYER_SIZE_Y) player.pos.y = 0;
		//�X�N���[����
		if (player.pos.y < 0)
		{
			player.pos.y =  20.0f;
		}
	}
	else {
		player.wing = 1;
		player.mov.y += 0.5f; // ���~����
		if (player.mov.y > 1.5f)
		{
			player.mov.y = 1.5f;	// ���~�ő�l
		}
	}
	// �ŏI�I�ȕ`��
	player.tmp.y = player.pos.y + player.mov.y;



	player.walk = 0;
	if (newKey[_1RIGHT])
		//if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		player.mov.x += 0.05f;
		if (player.mov.x > 2.0f) player.mov.x = 2.0f;
		if (player.pos.x > SCREEN_SIZE_X - PLAYER_SIZE_X) player.pos.x = 0.5f;
	
		player.walk = 1;
		player.LR = 1;
	}
	if (newKey[_1LEFT])
		//if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player.mov.x -= 0.5f;
		if (player.mov.x < -2.0f) player.mov.x = -2.0f;
		if (player.pos.x < 0.5f) player.pos.x = SCREEN_SIZE_X - PLAYER_SIZE_X;
		player.walk = 1;
		player.LR = -1;
		

	}
	//����
	if (player.walk == 0)
	{
		if ((player.mov.x <= 0.05f)
			&& (player.mov.x >= -0.05f))
		{
			player.mov.x = 0.0f;
		}
		// �󒆂̌���
		if (player.wing == 0)
		{
			if (player.mov.x > 0) player.mov.x -= 0.1f;
			if (player.mov.x < 0) player.mov.x += 0.1f;
		}
		else
		{
			if (player.mov.x > 0) player.mov.x -= 0.02f;
			if (player.mov.x < 0) player.mov.x += 0.02f;
		}
	}

	player.tmp.x = player.pos.x + player.mov.x;

	// �w�i�Ƃ̓����蔻��
	//player.hitFlag = 0;
	HitCheckMapVsCharaLR(&player);
	HitCheckMapVsCharaUD(&player);

	// �ŏI�I�ȍ��W
	player.pos.x = player.tmp.x;
	player.pos.y = player.tmp.y;

	// �n��(�f�o�b�N�p)
	if (player.pos.y >= SCREEN_SIZE_Y - 24)
	{
		player.pos.y = SCREEN_SIZE_Y - 24;
	}

	DrawFormatString(0, 0, GetColor(255, 255, 255), "score %d", player.score);

}

void PlayerDraw()
{
	player.counter++;
	// ���ł�����
	if (player.wing == 1)
	{
		if (player.LR == 1) // �E����
		{
			DrawGraph(player.pos.x - 16,
				player.pos.y - 24,
				imgPlayer[1][player.counter / 5 % 4], true);
		}
		else  // ������
		{
			DrawTurnGraph(player.pos.x - 16,
				player.pos.y - 24,
				imgPlayer[1][player.counter / 5 % 4], true);
		}

	}

	// ���ł��Ȃ����
	if (player.wing == 0)
	{
		// �����Ă���
		if (player.walk == 1)
		{
			if (player.LR == 1) // �E����
			{
				DrawGraph(player.pos.x - 16,
					player.pos.y - 24,
					imgPlayer[1][10 + player.counter / 5 % 4], true);
			}
			else  // ������
			{
				DrawTurnGraph(player.pos.x - 16,
					player.pos.y - 24,
					imgPlayer[1][10 + player.counter / 5 % 4], true);
			}
		}
		// �����Ă��Ȃ�
		if (player.walk == 0)
		{
			if (player.LR == 1) // �E����
			{
				DrawGraph(player.pos.x - 16,
					player.pos.y - 24,
					imgPlayer[1][10], true);
			}
			else  // ������
			{
				DrawTurnGraph(player.pos.x - 16,
					player.pos.y - 24,
					imgPlayer[1][10], true);
			}
		}
	}
}