// mytetristest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <gtest/gtest.h>

const int BORDER_X = 10;
const int BORDER_Y = 10;
const int SCREEN_LEFT_X = 300 + BORDER_X;
const int SCREEN_Y = 600 + BORDER_Y;
const int SCREEN_RIGHT_X = 180 + BORDER_X * 2;
const int SCREEN_X = SCREEN_LEFT_X + SCREEN_RIGHT_X;
const BOOL state_teris[][4][4] =
{
	{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
	{ { 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
	{ { 0,1,1,1 },{ 0,0,0,1 },{ 0,0,0,0 },{ 0,0,0,0 } },
	{ { 0,1,1,0 },{ 0,0,1,1 },{ 0,0,0,0 },{ 0,0,0,0 } },
	{ { 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
	{ { 0,1,1,1 },{ 0,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
	{ { 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }
};



//全局变量声明
static bool g_hasBlocked[50][50];
static RECT rc_left, rc_right, rc_right_top, rc_right_bottom, rc_main;
static int g_speed = 300;
static int t_speed = 300;
static BOOL bCurTeris[4][4];
static BOOL bNextCurTeris[4][4];
static int curPosX, curPosY;
static int rd_seed = 1995421;
static int tPre = 0, tCur;
static int GAME_STATE = 0;
static int GAME_SCORE = 0;
static int GAME_DIFF = 1;
static int NUM_X = 10;
static int NUM_Y = 20;
static int BLOCK_SIZE = 30;


int CheckValide(int startX, int startY, BOOL bTemp[4][4])//给定一个矩阵，查看是否合法
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
	//MessageBox(NULL,L"这里",L"as",MB_OK);
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
		{
			bNewTeris[x][y] = bTeris[3 - y][x];
		}
	}

	if (CheckValide(curPosX, curPosY, bNewTeris) == 1)
	{
		memcpy(bTeris, bNewTeris, sizeof(bNewTeris));//成功则将变换后的形状保存
	}
}

TEST(A, test0)
{
	BOOL bTemp[4][4] = {
		1, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
	};

	EXPECT_EQ(1, CheckValide(4, 5, bTemp));
}

TEST(A, test1)
{
	BOOL bTemp[4][4] = {
		1, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
	};

	EXPECT_EQ(-1, CheckValide(9, 5, bTemp));
}

TEST(A, test2)
{
	BOOL bTemp[4][4] = {
		1, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
	};

	EXPECT_EQ(-2, CheckValide(4, 19, bTemp));
}

TEST(A, test3)
{
	BOOL bTemp[4][4] = {
		1, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
	};

	g_hasBlocked[5][4] = TRUE;
	EXPECT_EQ(-3, CheckValide(4, 4, bTemp));
}

bool isSame(BOOL a[4][4], BOOL b[4][4])
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (a[i][j] != b[i][j]) {
				return false;
			}
		}
	}

	return true;
}

TEST(B, test0)
{
	BOOL bTemp[4][4] = {
		1, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
	};

	BOOL bResult[4][4] = {
		0, 1, 1, 1,
		0, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	RotateTeris(bTemp);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << bTemp[i][j];
		}
		std::cout << std::endl;
}
	EXPECT_EQ(true, isSame(bTemp, bResult));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("Pause");
    return 0;
}

