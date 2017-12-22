#include "stdafx.h"
#include "tetris.h"
#include <windows.h>
#include<gtest\gtest.h>
#include <mmsystem.h>//����windows�����ý���йصĴ�����ӿ�
#pragma comment(lib, "WINMM.LIB")//����winmm�⣺WINMM.LIB��Windows��ý�����Ӧ�ó���ӿ�
int CheckValide(int startX, int startY, BOOL bTemp[4][4])//����һ�����󣬲鿴�Ƿ�Ϸ�
{
	int i, j;
	for (i = 3; i >= 0; i--)
	{
		for (j = 3; j >= 0; j--)
		{
			if (bTemp[i][j])
			{
				if (j + startX<0 || j + startX >= NUM_X)
				{
					return -1;
				}
				if (i + startY >= NUM_Y)
				{
					return -2;
				}
				if (g_hasBlocked[i + startY][j + startX])
				{
					//outPutBoxInt(j+startY);
					if (curPosY == 0)
					{
						return -3;
					}
					return -2;
				}
			}
		}
	}
	//MessageBox(NULL,L"����",L"as",MB_OK);
	//outPutBoxInt(curPosY);
	return 1;
}
void RotateTeris(BOOL bTeris[4][4])
{
	BOOL bNewTeris[4][4];
	int x, y;
	for (x = 0; x<4; x++)
	{
		for (y = 0; y<4; y++)
		{//��ת�Ƕ�
			bNewTeris[x][y] = bTeris[3 - y][x];
			//��ʱ�룺
			//bNewTeris[x][y] = bTeris[y][3-x];
		}
	}
	if (CheckValide(curPosX, curPosY, bNewTeris) == 1)
	{
		memcpy(bTeris, bNewTeris, sizeof(bNewTeris));//�ɹ��򽫱任�����״����
	}
}