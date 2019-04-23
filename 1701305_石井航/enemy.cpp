#pragma once
#include <DxLib.h>
#include "enemy.h"
#include "player.h"
#include "main.h"
#include "hitCheck.h"
#include "map.h"

int imgEnemyBalloon[2][3];	//���D
int imgEnemyBalloon2[2][4];	//���D
int imgEnemyAir[6];		//��C��

int imgEnemyFish[4];	//����

CHARA_DATA enemy[4];	//�G��
CHARA_DATA fish;		//����





void EnemySystemInit()
{
	int tmp = LoadGraph("image/enemyImage.png");

	//��C����
	for (int i = 0; i < 6; i++) 
	{
		imgEnemyAir[i] = DerivationGraph(32 * i, 48, 32, 48, tmp);
	}

	
		imgEnemyBalloon[0][0] = DerivationGraph(0, 0, 32, 48, tmp);


		imgEnemyBalloon2[0][0] = DerivationGraph(96, 0, 32, 48, tmp); 

		
}

void EnemyInit()
{
	//�G��
	enemy[0].pos.x =  130;		//��13�R�}��
	enemy[0].pos.y = 215;	//�c�W�R�}��
	enemy[0].counter = 0;			//�J�E���^�[
	enemy[0].wing = 0;				//���ł��Ȃ�
	enemy[0].walk = 0;				//�����Ă��Ȃ�
	enemy[0].LR = -1;				//1:�E�@-1:��
	enemy[0].air = 1;
	enemy[0].life = 2;
	enemy[0].flag = true;
	


	enemy[1].pos.x = 200;		//��13�R�}��
	enemy[1].pos.y = 215;	//�c�W�R�}��
	enemy[1].counter =78;			//�J�E���^�[
	enemy[1].wing = 0;				//���ł��Ȃ�
	enemy[1].walk = 0;				//�����Ă��Ȃ�
	enemy[1].LR = -1;				//1:�E�@-1:��
	enemy[1].air = 1;
	enemy[1].life = 2;
	enemy[1].flag = true;
	

	enemy[2].pos.x = 270;		//��13�R�}��
	enemy[2].pos.y = 215;	//�c�W�R�}��
	enemy[2].counter = 0;			//�J�E���^�[
	enemy[2].wing = 0;				//���ł��Ȃ�
	enemy[2].walk = 0;				//�����Ă��Ȃ�
	enemy[2].LR = -1;				//1:�E�@-1:��
	enemy[2].air = 1;
	enemy[2].life = 2;
	enemy[2].flag = true;
	

	enemy[3].pos.x = 320;		//��13�R�}��
	enemy[3].pos.y = 215;	//�c�W�R�}��
	enemy[3].counter = 0;			//�J�E���^�[
	enemy[3].wing = 0;				//���ł��Ȃ�
	enemy[3].walk = 0;				//�����Ă��Ȃ�
	enemy[3].LR = -1;				//1:�E�@-1:��
	enemy[3].air = 1;
	enemy[3].life = 2;
	enemy[3].flag = true;
	

	/*fish.flg = 1;					//����
	fish.counter = 0;*/

}

void EnemyMain()
{

	//�v���C���[�̂ق��Ɍ�����ς���
	for (int i = 0; i < 4; i++) {
		if (enemy[i].pos.x < player.pos.x)
		{
			enemy[i].LR = 1;	//�E
		}
		else
		{
			enemy[i].LR = -1;	//��
		}

	}
	
		//��C����I�������㏸���[�h
	for (int i = 0; i < 4; i++) 
	{
		if (enemy[i].counter == 180)
		{
			enemy[i].air = 0;
			enemy[i].wing = 1;
			enemy[i].mov.y = -0.1f;
			enemy[i].mov.x = 0.0f;

		}
	}
	
	//��C���ꃂ�[�h
	for (int i = 0; i < 4; i++)
	{
		if (enemy[i].air == 1)
		{
			enemy[i].mov.y = 0.0f;//�����Ȃ�
			enemy[i].mov.x = 0.0f;
		}
	}


	//�ړ����[�h
	for (int i = 0; i < 4; i++)
	{
		if (enemy[i].wing == 1)
		{
			if ((enemy[i].counter % 90) == 0)
			{//�ړ��̌�����ς���^�C�~���O
				switch (GetRand(6))
				{
				case 0:
					enemy[i].mov.x = -1.0f;
					break;
				case 1:
					enemy[i].mov.x = 1.0f;
					break;
				case 2:
					enemy[i].mov.y = 1.0f;
					break;
				case 3:
					enemy[i].mov.y = -1.0f;
					break;
				case 4:
					//�B�c���E�����Ƃ��Ƀv���C���[�ɋ߂���
					if (enemy[i].pos.y > player.pos.y)
					{
						enemy[i].mov.y = -1.0f;
					}
					else
					{
						enemy[i].mov.y = 0.5f;	//�c��
					}
					if (enemy[i].pos.x > player.pos.x)
					{
						enemy[i].mov.x = -1.0;
					}
					else
					{
						enemy[i].mov.x = 1.0f;	//����
					}
				}
			}
			if (enemy[i].life == 1)
			{
				enemy[i].mov.y = 0.5f;
				enemy[i].mov.x = 0.0f;
			}
		}
	}

	

	enemy[0].tmp.x = enemy[0].pos.x + enemy[0].mov.x;
	enemy[0].tmp.y = enemy[0].pos.y + enemy[0].mov.y;

	enemy[1].tmp.x = enemy[1].pos.x + enemy[1].mov.x;
	enemy[1].tmp.y = enemy[1].pos.y + enemy[1].mov.y;

	enemy[2].tmp.x = enemy[2].pos.x + enemy[2].mov.x;
	enemy[2].tmp.y = enemy[2].pos.y + enemy[2].mov.y;

	enemy[3].tmp.x = enemy[3].pos.x + enemy[3].mov.x;
	enemy[3].tmp.y = enemy[3].pos.y + enemy[3].mov.y;

	for (int i = 0; i < 4; i++)
	{
		HitCheckMapCharaLR(&enemy[i]);
		HitCheckMapCharaUD(&enemy[i]);
	}
	//�ŏI���W
	enemy[0].pos.x = enemy[0].tmp.x;
	enemy[0].pos.y = enemy[0].tmp.y;

	//�ŏI���W
	enemy[1].pos.x = enemy[1].tmp.x;
	enemy[1].pos.y = enemy[1].tmp.y;

	//�ŏI���W
	enemy[2].pos.x = enemy[2].tmp.x;
	enemy[2].pos.y = enemy[2].tmp.y;

	//�ŏI���W
	enemy[3].pos.x = enemy[3].tmp.x;
	enemy[3].pos.y = enemy[3].tmp.y;

}

void EnemyDraw()
{
	//�G�S���`��
	for (int i = 0; i < 4; i++)
	{
		//	DrawFormatString(0, 0 , GetColor(255, 255, 255), "score %d", enemy[i].life);
		enemy[i].counter++;
		if (enemy[i].life == 2)
		{
			//��C������
			if (enemy[i].air == 1)
			{
				if (enemy[i].LR == 1)
				{
					DrawGraph(enemy[i].pos.x - 16, enemy[i].pos.y - 24,
						imgEnemyAir[enemy[i].counter / 30 % 30], true);
				}
				else
				{
					DrawTurnGraph(enemy[i].pos.x - 16, enemy[i].pos.y - 24,
						imgEnemyAir[enemy[i].counter / 30 % 30], true);
				}
			}
			else
			{
				if (enemy[i].wing == 1)
				{
					if (enemy[i].LR == 1)
					{
						DrawGraph(enemy[i].pos.x - 16, enemy[i].pos.y - 24,
							imgEnemyBalloon[0][0], true);
					}
					else
					{
						DrawTurnGraph(enemy[i].pos.x - 16, enemy[i].pos.y - 24,
							imgEnemyBalloon[0][0], true);
					}
				}
			}
		}
		if (enemy[i].life == 1)
		{
			if (enemy[i].wing == 1)
			{
				if (enemy[i].LR == 1)
				{
					DrawGraph(enemy[i].pos.x - 16, enemy[i].pos.y - 24,
						imgEnemyBalloon2[0][0], true);
				}
				else
				{
					DrawTurnGraph(enemy[i].pos.x - 16, enemy[i].pos.y - 24,
						imgEnemyBalloon2[0][0], true);
				}
			}
		}
	}
}
