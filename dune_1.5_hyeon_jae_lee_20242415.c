#include <stdio.h>
#include <Windows.h>
#include <conio.h>


#define TICK 10

int sys_clock = 0;// 0���� ����

int main(void) {
	//p10 Sleep�� ���� ���� 
	
	//int sec = 1;//sec�� 1���� ����
	//1tick 10ms �� ���α׷��� �����ϴ� �ּ� �ð� ����
	//���� �ܼ��� ���Sleep()���, �� ������� ��Ȯ�� �ð� ���� ����� -> �и���.
	//while (1) {
	//	if (sys_clock % 3000 == 0) {
	//		printf("�ȳ��ϼ���\n");
	//	}
	//	//sysclock = 0 : 1���� �� 1�� ��� �� 2�ʷ� ����
	//	//sysclock = 1000 : 2�� ��� sec : 3��
	//	//sysclcok = 2000 : 3�� ��� sec : 4�� 
	//	//1 ---> ���----> 2 ---> ��� ---> 3 --->�ȳ��ϼ���---> 4 ��� ǥ���� ���  
	//	if (sys_clock % 1000 == 0) {
	//		printf("sec: %d\n", sec);
	//		sec ++;
	//	}
	//	Sleep(TICK); //10ms ���� ���� sysclock�� 10ms ����
	//	sys_clock += 10;
	//}

	////p11 Ű �Է� �ޱ� ����
	//while (1) {
	//	if (_kbhit()) {
	//		int key = _getch();
	//		if (key == 'q') {
	//			break;
	//		}
	//		Sleep(TICK);
	//	}
	//}
	
	//p12 q�� �Էµǰ� ���� 3�� �Ŀ� �����ϱ�
	int sys_clock = 0;
	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 'q') {
				while (sys_clock < 3000) {// 0 1 2 3
					Sleep(TICK); //10ms ���� ���� sysclock�� 10ms ����
					sys_clock += 10;
				}
				break;
			}
		}
	}

	//p13 �������� ���� ����
	typedef enum { //0���� ������� ���� �ο� �ȴ�.
		k_none = 0, k_up, k_right, k_left, k_down,
		k_quit, 
		k_undef,
	} KEY;





	return 0;
}