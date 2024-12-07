#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <corecrt_math_defines.h>

#define High 480  // 游戏画面尺寸
#define Width 640

inline static double to_degree(int i)
{
	return M_PI * 2 * i / 60;
}

int main()
{
	initgraph(Width, High, EX_DBLCLKS | EX_NOCLOSE);        // 初始化 640 x 480 的绘图窗口
	int center_x, center_y;      // 中心点的坐标，也是表的中心
	center_x = Width / 2;
	center_y = High / 2;
	int secondLength = Width / 5;           // 秒针的长度
	int minuteLength = Width / 6;           // 分针的长度
	int hourLength = Width / 7;             // 时针的长度

	int secondEnd_x, secondEnd_y;    // 秒针的终点
	int minuteEnd_x, minuteEnd_y;    // 分针的终点
	int hourEnd_x, hourEnd_y;    // 时针的终点
	float secondAngle;       // 秒钟对应的角度
	float minuteAngle;       // 分钟对应的角度
	float hourAngle;         // 时钟对应的角度

	SYSTEMTIME ti;                // 定义变量保存当前时间
	ExMessage ex;				//定义消息结构体接收消息

	BeginBatchDraw();
	while (true)
	{
		// 绘制一个简单的表盘
		setlinestyle(PS_SOLID, 1);
		setcolor(WHITE);
		circle(center_x, center_y, Width / 4);

		// 画刻度
		int x, y;
		for (int i = 0; i < 60; i++)
		{
			x = center_x + int(Width / 4.3 * sin(to_degree(i)));
			y = center_y + int(Width / 4.3 * cos(to_degree(i)));

			if (i % 15 == 0)
				bar(x - 5, y - 5, x + 5, y + 5);
			else if (i % 5 == 0)
				circle(x, y, 3);
			else
				putpixel(x, y, WHITE);
		}

		outtextxy(center_x - 25, center_y + Width / 6, L"我的时钟");

		GetLocalTime(&ti);        // 获取当前时间
		// 秒钟角度变化
		secondAngle = to_degree(ti.wSecond);  // 一圈一共2*PI，一圈60秒，一秒钟秒钟走过的角度为2*PI/60
		// 分钟角度变化
		minuteAngle = to_degree(ti.wMinute) + secondAngle / 60;  // 一圈一共2*PI，一圈60分，一分钟分钟走过的角度为2*PI/60
		// 时钟角度变化
		hourAngle = ti.wHour * 2 * M_PI / 12 + minuteAngle / 12;  // 一圈一共2*PI，一圈12小时，一小时时钟走过的角度为2*PI/12
		// 由角度决定的秒针端点坐标
		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);

		// 由角度决定的分针端点坐标
		minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);

		// 由角度决定的时针端点坐标
		hourEnd_x = center_x + hourLength * sin(hourAngle);
		hourEnd_y = center_y - hourLength * cos(hourAngle);

		setlinestyle(PS_SOLID, 2);
		setcolor(WHITE);
		line(center_x, center_y, secondEnd_x, secondEnd_y); // 画秒针

		setlinestyle(PS_SOLID, 5);
		setcolor(GREEN);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y); // 画分针

		setlinestyle(PS_SOLID, 10);
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y); // 画时针

		FlushBatchDraw();
		Sleep(10);

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		line(center_x, center_y, secondEnd_x, secondEnd_y);  // 隐藏前一帧的秒针
		setlinestyle(PS_SOLID, 5);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y); // 隐藏前一帧的分针
		setlinestyle(PS_SOLID, 10);
		line(center_x, center_y, hourEnd_x, hourEnd_y); // 隐藏前一帧的时针

		if (peekmessage(&ex, EX_MOUSE) && ex.message == WM_LBUTTONDBLCLK)
		{
			EndBatchDraw();
			closegraph();            // 关闭绘图窗口
			return 0;
		}//收到双击消息表示正常退出了
	}

	return -1;
}