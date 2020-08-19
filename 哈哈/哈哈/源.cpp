#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "resource.h"
#include <conio.h>

#define NUM 13
#define  PI  3.1415926548

//烟花弹结构体
struct Jet
{
	int x; //坐标
	int y;
	int hx; //最高的坐标 将赋值给烟花  
	int hy;
	int height; //高度
	bool shoot; //是否可以发射
	DWORD t1, t2, dt;//烟花弹的上升速度
	IMAGE img[2];    //一亮一暗两张图片
	byte n : 1;      //图片下标 0 1  //位段 一个二进制位  int 32 float 32 short 16
}jet[13];

//烟花结构体
struct Fire
{
	int x, y;			//坐标
	int cen_x, cen_y;	//中心坐标
	int width, height;	//图片的宽和高
	int r;				//半径 从小变大
	int max_r;			//最大的半径

	int xy[240][240];   //像素点的集合

	bool show;
	bool draw;			//输出像素点
	DWORD t1, t2, dt;
}fire[NUM];

void Init(int i);
void welcome();
void Load();
void Chose(DWORD& t1);
void shoot();
void Show(DWORD* pMem);

int main()
{
	initgraph(1200, 700); //打开一个界面
	welcome();

	DWORD t1 = timeGetTime();
	DWORD *pMem = GetImageBuffer();

	//循环初始化13次
	for (int i = 0; i < NUM; i++)
	{
		Init(i);
	}
	Load();
	BeginBatchDraw();
	
	while (1)
	{
		Sleep(10);

		for (int clr = 0; clr < 1000; clr++)
		{
			for (int j = 0; j < 2; j++)
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 700;

				if (py1 < 699)
				{
					pMem[py1 * 1200 + px1] = pMem[py1 * 1200 + px1 + 1] = BLACK;
				}
			}
		}
		settextstyle(100, 35, L"AR DELANEY");
		settextcolor(RGB(255, 0, 0));
		outtextxy(75, 600, L"(*^^*)¡Feliz cumpleaños!(*^^*)");
/*		settextstyle(30, 0, L"AR DELANEY");
		outtextxy(1110, 670, L"The End");
*/		Chose(t1);
		shoot();
		Show(pMem);
		FlushBatchDraw(); //吧显存展示出来
	}

	getchar();
	closegraph();		//关闭界面
	return 0;
}


void welcome()
{
	PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

	settextcolor(RGB(255, 0, 255));
	settextstyle(200, 0, L"AR DELANEY");
	cleardevice();
	outtextxy(550, 250, L"5");
	Sleep(1000);
	cleardevice();
	outtextxy(550, 250, L"4");
	Sleep(1000);
	cleardevice();
	outtextxy(550, 250, L"3");
	Sleep(1000);
	cleardevice();
	outtextxy(550, 250, L"2");
	Sleep(1000);
	cleardevice();
	outtextxy(550, 250, L"1");
	Sleep(1000);


	//怎样得到一个圆的轨迹上的n个坐标。
	for (int i = 0; i < 50; i++)
	{
		int x = 600 + int(180 * sin(PI * 2 * i / 60));
		int y = 200 + int(180 * cos(PI * 2 * i / 60));
		cleardevice();  //刷新 没有指定颜色 默认为黑色
		settextstyle(i, 0, L"楷体");
		outtextxy(x - 100, y, L"献给：");
		outtextxy(x + 50, y + 100, L"亲爱的老铁 铭铭");
		outtextxy(x + 50, y + 200, L"(^з^)-☆");
		Sleep(50);
	}
	Sleep(5000);

	cleardevice();
	settextstyle(30, 0, L"楷体");
	settextcolor(RGB(255, 255, 0));
	for (int i = 0; i < 15; i++)
	{
		outtextxy(600 + i * 30, 25, L"★");
		outtextxy(600 - i * 30, 25, L"★");
		Sleep(150);
	}
	for (int i = 0; i < 22; i++)
	{
		outtextxy(180, 25 + i * 30, L"★");
		outtextxy(1020, 25 + i * 30, L"★");
		Sleep(150);
	}
	for (int i = 800; i >= 50; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"光阴似箭，日月如梭；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"光阴似箭，日月如梭；");
		Sleep(50);
	}
	for (int i = 850; i >= 90; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"转眼之间我们从初中过度到了大学；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"转眼之间我们从初中过度到了大学；");
		Sleep(50);
	}
	for (int i = 850; i >= 130; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"请允许我陪你过21岁生日and大年初六；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"请允许我陪你过21岁生日and大年初六；");
		Sleep(50);
	}
	for (int i = 850; i >= 170; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"很庆幸我们做过同桌；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"很庆幸我们做过同桌；");
		Sleep(50);
	}
	for (int i = 850; i >= 210; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"让我认识了一个如此内外兼修、倾国倾城的你；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"让我认识了一个如此内外兼修、倾国倾城的你；");
		Sleep(50);
	}
	for (int i = 850; i >= 250; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"虽然我们不常见面；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"虽然我们不常见面；");
		Sleep(50);
	}
	for (int i = 850; i >= 290; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"但你突然要走了好舍不得；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"但你突然要走了好舍不得；");
		Sleep(50);
	}
	for (int i = 850; i >= 330; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"到古巴要好好学习保重身体；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"到古巴要好好学习保重身体；");
		Sleep(50);
	}
	for (int i = 850; i >= 370; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"有困难就跟我说；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"有困难就跟我说；");
		Sleep(50);
	}
	for (int i = 850; i >= 410; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"在我能力范围之内的一定全力以赴；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"在我能力范围之内的一定全力以赴；");
		Sleep(50);
	}
	for (int i = 850; i >= 450; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"据说古巴雨水很大；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"据说古巴雨水很大；");
		Sleep(50);
	}
	for (int i = 850; i >= 490; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"在那边要注意防潮；");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"在那边要注意防潮；");
		Sleep(50);
	}
	for (int i = 850; i >= 530; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"最后祝铭铭新年快乐！生日快乐！");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"最后祝铭铭新年快乐！生日快乐！");
		Sleep(50);
	}
	for (int i = 850; i >= 570; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"愿做你一生的老铁");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"愿做你一生的老铁");
		Sleep(50);
	}
	for (int i = 850; i >= 610; i -= 10)
	{
		settextcolor(RGB(255, 0, 255));
		outtextxy(300, i, L"我会想你滴！              ——嘴哥");
		settextcolor(RGB(0, 0, 0));
		outtextxy(300, i + 30, L"我会想你滴！              ——嘴哥");
		Sleep(50);
	}
	settextcolor(RGB(255, 255, 0));
	for (int i = 0; i < 15; i++)
	{
		outtextxy(180 + i * 30, 658, L"★");
		outtextxy(1020 - i * 30, 658, L"★");
		Sleep(150);
	}
	Sleep(5000);
}


void Init(int i)
{
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	//初始化烟花
	fire[i].x = 0;
	fire[i].y = 0;
	fire[i].width = 240;
	fire[i].height = 240;
	fire[i].max_r = r[i];
	fire[i].cen_x = x[i];
	fire[i].cen_y = y[i];
	fire[i].show = false;
	fire[i].dt = 5;
	fire[i].t1 = timeGetTime();
	fire[i].r = 0;


	//初始化烟花弹
	jet[i].x = 0;
	jet[i].y = 0;
	jet[i].hx = 0;
	jet[i].hy = 0;
	jet[i].height = 0;
	jet[i].t1 = timeGetTime();
	jet[i].dt = rand() % 10;
	jet[i].n = 0;
	jet[i].shoot = false;
}


void Load()
{
	//加载烟花
	IMAGE fm, gm;
	loadimage(&fm, L"./images/flower.jpg");
	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&fm);  //工作---对象是一张图片 
		getimage(&gm, i * 240, 0, 240, 240);

		SetWorkingImage(&gm);  //工作---对象是一张图片 
		for (int a = 0; a < 240; a++)
		{
			for (int b = 0; b < 240; b++)
			{
				fire[i].xy[a][b] = getpixel(a, b);
			}
		}
	}

	//加载烟花弹
	IMAGE jm;
	loadimage(&jm, L"./images/shoot.jpg");
	//jm 里面保存了一整张图片 分隔开来

	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&jm);  //工作---对象是一张图片 
		int n = rand() % 5;    //0-4

		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}

	SetWorkingImage(NULL); //放弃掉刚才的工作区域。
}


//选出13个 
void Chose(DWORD& t1)
{
	DWORD t2 = timeGetTime();

	if (t2 - t1 > 100)
	{
		int n = rand() % 20;

		if (n < NUM&&jet[n].shoot == false && fire[n].show == false)
		{
			jet[n].x = rand() % 1200;
			jet[n].y = rand() % 100 + 600; //600-699
			jet[n].hx = jet[n].x;
			jet[n].hy = rand() % 400;
			jet[n].height = jet[n].y - jet[n].hy;
			jet[n].shoot = true;
			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n], SRCINVERT);
		}
		t1 = t2;
	}
}


void shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = timeGetTime();
		if (jet[i].t2 - jet[i].t1>jet[i].dt&&jet[i].shoot == true)
		{
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			if (jet[i].y > jet[i].hy)
			{
				jet[i].n++; //明暗交替的效果
				jet[i].y -= 5;
			}
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			
			if (jet[i].y <= jet[i].hy)
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
				fire[i].x = jet[i].hx + 10;
				fire[i].y = jet[i].hy;
				fire[i].show = true;
				jet[i].shoot = false;
			}
			

			jet[i].t1 = jet[i].t2;
		}
	}
}


void Show(DWORD* pMem) //显存指针  像素 这里面所有的像素点的集合
{
	//3D游戏 地形 天空 显存来做
	int drt[16] = { 5, 5, 5, 5, 5, 5, 25, 25, 25, 25, 55, 55, 55, 55, 55, 55 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = timeGetTime();
		if (fire[i].t2 - fire[i].t1>fire[i].dt&&fire[i].show == true)
		{
			if (fire[i].r < fire[i].max_r)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}
			if (fire[i].r >= fire[i].max_r - 1)
			{
				fire[i].draw = false;
				Init(i);
			}
			fire[i].t1 = fire[i].t2;
		}
		if (fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a += 0.01)
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r*cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r*sin(a));


				if (x1 > 0 && x1<fire[i].width&&y1>0 && y1 < fire[i].height)
				{
					int b = fire[i].xy[x1][y1] & 0xff;
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;
					int r = (fire[i].xy[x1][y1] >> 16);

					int xx = (int)(fire[i].x + fire[i].r*cos(a));
					int yy = (int)(fire[i].y - fire[i].r*sin(a));

					if (r>0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx<1200 && yy>0 && yy < 800)
						pMem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
				}
			}
			fire[i].draw = false;
		}
	}
}