#pragma once
#include <DxLib.h>
#include "enemy.h"
#include "player.h"
#include "main.h"
#include "hitCheck.h"
#include "map.h"

int imgEnemyBalloon[2][3];	//風船
int imgEnemyBalloon2[2][4];	//風船
int imgEnemyAir[6];		//空気入

int imgEnemyFish[4];	//怪魚

CHARA_DATA enemy[4];	//雑魚
CHARA_DATA fish;		//怪魚





void EnemySystemInit()
{
	int tmp = LoadGraph("image/enemyImage.png");

	//空気入れ
	for (int i = 0; i < 6; i++) 
	{
		imgEnemyAir[i] = DerivationGraph(32 * i, 48, 32, 48, tmp);
	}

	
		imgEnemyBalloon[0][0] = DerivationGraph(0, 0, 32, 48, tmp);


		imgEnemyBalloon2[0][0] = DerivationGraph(96, 0, 32, 48, tmp); 

		
}

void EnemyInit()
{
	//雑魚
	enemy[0].pos.x =  130;		//横13コマ目
	enemy[0].pos.y = 215;	//縦８コマ目
	enemy[0].counter = 0;			//カウンター
	enemy[0].wing = 0;				//飛んでいない
	enemy[0].walk = 0;				//歩いていない
	enemy[0].LR = -1;				//1:右　-1:左
	enemy[0].air = 1;
	enemy[0].life = 2;
	enemy[0].flag = true;
	


	enemy[1].pos.x = 200;		//横13コマ目
	enemy[1].pos.y = 215;	//縦８コマ目
	enemy[1].counter =78;			//カウンター
	enemy[1].wing = 0;				//飛んでいない
	enemy[1].walk = 0;				//歩いていない
	enemy[1].LR = -1;				//1:右　-1:左
	enemy[1].air = 1;
	enemy[1].life = 2;
	enemy[1].flag = true;
	

	enemy[2].pos.x = 270;		//横13コマ目
	enemy[2].pos.y = 215;	//縦８コマ目
	enemy[2].counter = 0;			//カウンター
	enemy[2].wing = 0;				//飛んでいない
	enemy[2].walk = 0;				//歩いていない
	enemy[2].LR = -1;				//1:右　-1:左
	enemy[2].air = 1;
	enemy[2].life = 2;
	enemy[2].flag = true;
	

	enemy[3].pos.x = 320;		//横13コマ目
	enemy[3].pos.y = 215;	//縦８コマ目
	enemy[3].counter = 0;			//カウンター
	enemy[3].wing = 0;				//飛んでいない
	enemy[3].walk = 0;				//歩いていない
	enemy[3].LR = -1;				//1:右　-1:左
	enemy[3].air = 1;
	enemy[3].life = 2;
	enemy[3].flag = true;
	

	/*fish.flg = 1;					//怪魚
	fish.counter = 0;*/

}

void EnemyMain()
{

	//プレイヤーのほうに向きを変える
	for (int i = 0; i < 4; i++) {
		if (enemy[i].pos.x < player.pos.x)
		{
			enemy[i].LR = 1;	//右
		}
		else
		{
			enemy[i].LR = -1;	//左
		}

	}
	
		//空気入れ終わったら上昇モード
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
	
	//空気入れモード
	for (int i = 0; i < 4; i++)
	{
		if (enemy[i].air == 1)
		{
			enemy[i].mov.y = 0.0f;//動かない
			enemy[i].mov.x = 0.0f;
		}
	}


	//移動モード
	for (int i = 0; i < 4; i++)
	{
		if (enemy[i].wing == 1)
		{
			if ((enemy[i].counter % 90) == 0)
			{//移動の向きを変えるタイミング
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
					//③縦軸・横軸ともにプレイヤーに近つける
					if (enemy[i].pos.y > player.pos.y)
					{
						enemy[i].mov.y = -1.0f;
					}
					else
					{
						enemy[i].mov.y = 0.5f;	//縦軸
					}
					if (enemy[i].pos.x > player.pos.x)
					{
						enemy[i].mov.x = -1.0;
					}
					else
					{
						enemy[i].mov.x = 1.0f;	//横軸
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
	//最終座標
	enemy[0].pos.x = enemy[0].tmp.x;
	enemy[0].pos.y = enemy[0].tmp.y;

	//最終座標
	enemy[1].pos.x = enemy[1].tmp.x;
	enemy[1].pos.y = enemy[1].tmp.y;

	//最終座標
	enemy[2].pos.x = enemy[2].tmp.x;
	enemy[2].pos.y = enemy[2].tmp.y;

	//最終座標
	enemy[3].pos.x = enemy[3].tmp.x;
	enemy[3].pos.y = enemy[3].tmp.y;

}

void EnemyDraw()
{
	//敵全員描画
	for (int i = 0; i < 4; i++)
	{
		//	DrawFormatString(0, 0 , GetColor(255, 255, 255), "score %d", enemy[i].life);
		enemy[i].counter++;
		if (enemy[i].life == 2)
		{
			//空気入れ状態
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
