#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <corecrt_math_defines.h>

#define High 480  // ��Ϸ����ߴ�
#define Width 640

inline static double to_degree(int i)
{
	return M_PI * 2 * i / 60;
}

int main()
{
	initgraph(Width, High, EX_DBLCLKS | EX_NOCLOSE);        // ��ʼ�� 640 x 480 �Ļ�ͼ����
	int center_x, center_y;      // ���ĵ�����꣬Ҳ�Ǳ������
	center_x = Width / 2;
	center_y = High / 2;
	int secondLength = Width / 5;           // ����ĳ���
	int minuteLength = Width / 6;           // ����ĳ���
	int hourLength = Width / 7;             // ʱ��ĳ���

	int secondEnd_x, secondEnd_y;    // ������յ�
	int minuteEnd_x, minuteEnd_y;    // ������յ�
	int hourEnd_x, hourEnd_y;    // ʱ����յ�
	float secondAngle;       // ���Ӷ�Ӧ�ĽǶ�
	float minuteAngle;       // ���Ӷ�Ӧ�ĽǶ�
	float hourAngle;         // ʱ�Ӷ�Ӧ�ĽǶ�

	SYSTEMTIME ti;                // ����������浱ǰʱ��
	ExMessage ex;				//������Ϣ�ṹ�������Ϣ

	BeginBatchDraw();
	while (true)
	{
		// ����һ���򵥵ı���
		setlinestyle(PS_SOLID, 1);
		setcolor(WHITE);
		circle(center_x, center_y, Width / 4);

		// ���̶�
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

		outtextxy(center_x - 25, center_y + Width / 6, L"�ҵ�ʱ��");

		GetLocalTime(&ti);        // ��ȡ��ǰʱ��
		// ���ӽǶȱ仯
		secondAngle = to_degree(ti.wSecond);  // һȦһ��2*PI��һȦ60�룬һ���������߹��ĽǶ�Ϊ2*PI/60
		// ���ӽǶȱ仯
		minuteAngle = to_degree(ti.wMinute) + secondAngle / 60;  // һȦһ��2*PI��һȦ60�֣�һ���ӷ����߹��ĽǶ�Ϊ2*PI/60
		// ʱ�ӽǶȱ仯
		hourAngle = ti.wHour * 2 * M_PI / 12 + minuteAngle / 12;  // һȦһ��2*PI��һȦ12Сʱ��һСʱʱ���߹��ĽǶ�Ϊ2*PI/12
		// �ɽǶȾ���������˵�����
		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);

		// �ɽǶȾ����ķ���˵�����
		minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);

		// �ɽǶȾ�����ʱ��˵�����
		hourEnd_x = center_x + hourLength * sin(hourAngle);
		hourEnd_y = center_y - hourLength * cos(hourAngle);

		setlinestyle(PS_SOLID, 2);
		setcolor(WHITE);
		line(center_x, center_y, secondEnd_x, secondEnd_y); // ������

		setlinestyle(PS_SOLID, 5);
		setcolor(GREEN);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y); // ������

		setlinestyle(PS_SOLID, 10);
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y); // ��ʱ��

		FlushBatchDraw();
		Sleep(10);

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		line(center_x, center_y, secondEnd_x, secondEnd_y);  // ����ǰһ֡������
		setlinestyle(PS_SOLID, 5);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y); // ����ǰһ֡�ķ���
		setlinestyle(PS_SOLID, 10);
		line(center_x, center_y, hourEnd_x, hourEnd_y); // ����ǰһ֡��ʱ��

		if (peekmessage(&ex, EX_MOUSE) && ex.message == WM_LBUTTONDBLCLK)
		{
			EndBatchDraw();
			closegraph();            // �رջ�ͼ����
			return 0;
		}//�յ�˫����Ϣ��ʾ�����˳���
	}

	return -1;
}