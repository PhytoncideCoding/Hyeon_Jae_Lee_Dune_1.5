//#include <stdio.h>
//#include <Windows.h>
//#include <conio.h>

//#define TICK 10
//
//int sys_clock = 0;// 0���� ����
//
////p13 �������� ���� ����
//typedef enum { //0���� ������� ���� �ο� �ȴ�. //�͸� ����ü �ٷ� �ȿ� �ִ� ��� ������ ��� ����
//	k_none = 0, k_up, k_right, k_left, k_down,
//	k_quit,
//	k_undef,
//} KEY;
////14����Ű �Է� �ޱ�
//KEY get_key(void) {
//	if (!_kbhit) {
//		return k_none;
//	}
//
//	int byte = _getch();
//	switch (byte) {
//	case 'q': return k_quit;
//	case 224:
//		byte = _getch();
//		switch (byte) {
//		case 72: return k_up;
//		case 75: return k_left;
//		case 77: return k_right;
//		case 80: return k_down;
//
//		default: return k_undef;
//		}
//	default: return k_undef;
//	}
//}

////p17
//void gotoxy(short, short);
//void gotoxy(short x, short y) {
//	COORD coord = { x, y };
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}

//int main(void) {
//	//p10 Sleep�� ���� ���� 
//	
//	//int sec = 1;//sec�� 1���� ����
//	//1tick 10ms �� ���α׷��� �����ϴ� �ּ� �ð� ����
//	//���� �ܼ��� ���Sleep()���, �� ������� ��Ȯ�� �ð� ���� ����� -> �и���.
//	//while (1) {
//	//	if (sys_clock % 3000 == 0) {
//	//		printf("�ȳ��ϼ���\n");
//	//	}
//	//	//sysclock = 0 : 1���� �� 1�� ��� �� 2�ʷ� ����
//	//	//sysclock = 1000 : 2�� ��� sec : 3��
//	//	//sysclcok = 2000 : 3�� ��� sec : 4�� 
//	//	//1 ---> ���----> 2 ---> ��� ---> 3 --->�ȳ��ϼ���---> 4 ��� ǥ���� ���  
//	//	if (sys_clock % 1000 == 0) {
//	//		printf("sec: %d\n", sec);
//	//		sec ++;
//	//	}
//	//	Sleep(TICK); //10ms ���� ���� sysclock�� 10ms ����
//	//	sys_clock += 10;
//	//}
//
//	////p11 Ű �Է� �ޱ� ����
//	//while (1) {
//	//	if (_kbhit()) {
//	//		int key = _getch();
//	//		if (key == 'q') {
//	//			break;
//	//		}
//	//		Sleep(TICK);
//	//	}
//	//}
//	
//	////p12 q�� �Էµǰ� ���� 3�� �Ŀ� �����ϱ�
//	//int sys_clock = 0;
//	//while (1) {
//	//	if (_kbhit()) {
//	//		int key = _getch();
//	//		if (key == 'q') {
//	//			while (sys_clock < 3000) {// 0 1 2 3
//	//				Sleep(TICK); //10ms ���� ���� sysclock�� 10ms ����
//	//				sys_clock += 10;
//	//			}
//	//			break;
//	//		}
//	//	}
//	//}
//	////p15 ���� Ű �Է� �ޱ�
//	//
//	//while (1) {
//	//	KEY key = get_key();
//
//	//	switch (key) {
//	//	case k_quit: printf("exiting...\n"); return 0;
//	//	case k_up: printf("up\n"); break;
//	//	case k_left: printf("left\n"); break;
//	//	case k_right: printf("right\n"); break;
//	//	case k_down: printf("down\n"); break;
//	//	default: break;
//	//	}
//	//	Sleep(TICK);
//	//	
//	//  }
//
//	////p16 ���� ���� �Լ� 0~15���� ���ڻ� 0~15���� ���� ��������
//	//for (int color = 0x00; color < 0xFF; color++) {
//	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
//	//	printf("%d���� ���� ���ϱ��?\n", color);
//	//}
//	
//	//p17 Ŀ�� �̵���Ű��
//	srand((unsigned int)time(NULL));
//	while (1) {
//		gotoxy(rand() % 300 / 2, rand() % 40);
//		printf("*");
//		Sleep(1000);
//	}
//
//	
//	return 0;
//}

