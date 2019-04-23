#pragma once
#include <DxLib.h>
#include "hitCheck.h"
#include "map.h"
#include "enemy.h"



void HitCheckMapVsCharaLR(CHARA_DATA* c)
{
	int bl;	// �u���b�N�̍����W
	int br; // �u���b�N�̉E���W
	int bu; // �u���b�N�̏���W
	int bd; // �u���b�N�̉����W


	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			if (MapData[y][x] >= 0)
			{
				bl = x * 16;	    // ��
				br = x * 16 + 16;	// �E
				bu = y * 16;        // ��
				bd = y * 16 + 16;	// ��

				// ���E�ǔ���
				if (((c->pos.y - 16) < bd)
					&& ((c->pos.y + 16) > bu))
				{
					// �L�����N�^�[�̉E���ǂ̍�
					if (((c->pos.x + 8) < bl)
						&& ((c->tmp.x + 8) >= bl))
					{
						c->tmp.x -= 10;
					}
					// �L�����N�^�[�̍����ǂ̉E
					if (((c->pos.x - 8) > br)
						&& ((c->tmp.x -8) <= br))
					{
						c->tmp.x += 10;
					}
				}
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (((c->pos.y - 16) < enemy[i].pos.y)
			&& ((c->pos.y + 16) > enemy[i].pos.y))
		{
			if (((c->pos.x + 16) < enemy[i].pos.x - 16)
				&& ((c->tmp.x + 16) >= enemy[i].pos.x -16))
			{
				enemy[i].life--;
				if (enemy[i].life == 0)
				{
					player.score += 100;
					enemy[i].flag = false;
				}
			}

			if (((c->pos.x - 16) > enemy[i].pos.x + 16)
				&& ((c->tmp.x - 16) <= enemy[i].pos.x + 16))
			{
				enemy[i].life--;
				if (enemy[i].life == 0) 
				{
					player.score += 100;
					enemy[i].flag = false;
				}
			}
		}
	}
}

void HitCheckMapVsCharaUD(CHARA_DATA* c)
{
	int bl;	// �u���b�N�̍����W
	int br; // �u���b�N�̉E���W
	int bu; // �u���b�N�̏���W
	int bd; // �u���b�N�̉����W

	


	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			if (MapData[y][x] >= 0)
			{
				bl = x * 16;	    // ��
				br = x * 16 + 16;	// �E
				bu = y * 16;        // ��
				bd = y * 16 + 16;	// ��
			
				// �㉺�ǔ���
				if (((c->pos.x - 16) < br)
					&& ((c->pos.x + 16) > bl))
				{
					// �n�ʔ���
					if (((c->pos.y + 24) <= bu)
						&& ((c->tmp.y + 24) > bu))
					{
						c->tmp.y = bu - 24.0f;
						c->wing = 0;
					}
					// ������
					if (((c->pos.y - 16) >= bd)
						&& ((c->tmp.y - 16) < bd))
					{
						c->tmp.y += 9;
						c->mov.y = 2;
					}
				}
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (((c->pos.x - 16) < enemy[i].pos.x)
			&& ((c->pos.x + 16) > enemy[i].pos.x))
		{
			
			if (((c->pos.y - 16) <= enemy[i].pos.y - 48.0f)
				&& ((c->tmp.y - 16) > enemy[i].pos.y - 48.0f))
			{
				enemy[i].life--;
				if (enemy[i].life == 0)
				{
					player.score += 100;
					enemy[i].flag = false;
				}
			}
			
			if (((c->pos.y + 16) >= enemy[i].pos.y + 48.0f)
				&& ((c->tmp.y + 16) < enemy[i].pos.y + 48.0f))
			{
				enemy[i].life--;
				if (enemy[i].life == 0)
				{
					player.score += 100;
					enemy[i].flag = false;
				}
			}
		}
	}



}
void HitCheckMapCharaLR(CHARA_DATA* e)
{
	int bl;	// �u���b�N�̍����W
	int br; // �u���b�N�̉E���W
	int bu; // �u���b�N�̏���W
	int bd; // �u���b�N�̉����W

	if (e->tmp.x > SCREEN_SIZE_X)
	{
		e->tmp.x = 0.5f;
		e->wing = 1;
	}
	if (e->tmp.x < 0.5f)
	{
		e->tmp.x = SCREEN_SIZE_X;
		e->wing = 1;
	}
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			if (MapData[y][x] >= 0)
			{
				bl = x * 16;	    // ��
				br = x * 16 + 16;	// �E
				bu = y * 16;        // ��
				bd = y * 16 + 16;	// ��

				// ���E�ǔ���
				if (((e->pos.y - 16) < bd)
					&& ((e->pos.y + 16) > bu))
				{
					// �L�����N�^�[�̉E���ǂ̍�
					if (((e->pos.x + 8) < bl)
						&& ((e->tmp.x + 8) >= bl))
					{
						e->tmp.y -= 10;
					}
					// �L�����N�^�[�̍����ǂ̉E
					if (((e->pos.x - 8) > br)
						&& ((e->tmp.x - 8) <= br))
					{
						e->tmp.y += 10;
					}
				}
			}
		}
	}


}
void HitCheckMapCharaUD(CHARA_DATA* e)
{
	int bl;	// �u���b�N�̍����W
	int br; // �u���b�N�̉E���W
	int bu; // �u���b�N�̏���W
	int bd; // �u���b�N�̉����W

	//�X�N���[����

	if (e->pos.y < 0)
	{
		e->pos.y = SCREEN_SIZE_Y - 15.0f;
		e->wing = 1;

	}


	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			if (MapData[y][x] >= 0)
			{
				bl = x * 16;	    // ��
				br = x * 16 + 16;	// �E
				bu = y * 16;        // ��
				bd = y * 16 + 16;	// ��

				// �㉺�ǔ���
				if (((e->pos.x - 16) < br)
					&& ((e->pos.x + 16) > bl))
				{
					// �n�ʔ���
					if (((e->pos.y + 24) <= bu)
						&& ((e->tmp.y + 24) > bu))
					{
						if (e->life == 1)
						{
							e->life = 2;
						}
						e->tmp.y = bu - 24.0f;
				//		e->wing = 0;
					}
					// ������
					if (((e->pos.y - 16) >= bd)
						&& ((e->tmp.y - 16) < bd))
					{
						
						e->tmp.y += 6;
						e->mov.y = 0.01f;
						
					}
				}
			}
		}
	}

}
