//#include <stdio.h>
//#include <Windows.h>
//#include <conio.h>
//#include <stdbool.h>
//
//#define TICK 10
//int sys_clock = 0;
//
//bool exiting = false;
//int exit_count = 0;
//
//// �ð����� Sleep() �����층���� �ణ �и���. �ð��� �����ϴϱ�
//// TICK �ּҴ��� 10ms  �������� ��ǥ �ϳ��� �ش��Ѵٰ� ����
//// �帥 �ð��� ī��Ʈ �ϰڴ�.
//// 3�ʸ��� ��� �ȳ��ϼ���
//// 1�ʸ��� ��� ��������
//
//int main(void) {
//	if (sys_clock % 1300 == 0) {
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT, HANDLE), color);
//		printf("%d�� ����");
//		color = (color + 1) % 0xFF;
//	}
//	return 0;
//}
//
//int main(void) {
//	
//	int sec = 1;
//	while (1) {// �̷�������
//		/*
//		if (sys_clock % 3000 == 0) {
//			printf("�ȳ��ϼ���\n");
//		}
//		
//		if (sys_clock % 1000 == 0) {
//			printf("sec: %d\n", sec);	
//			sec++;
//		}
//		Sleep(TICK);
//		sys_clock += 10;
//		W*/
//
//		if (exiting) {
//			exit_count -= TICK;
//			if (exit_count <= 0) {
//				break;
//			}
//		}
//
//		if (_kbhit()) {
//			int key = _getch();
//			if (key == 'q') {//3�� �ڿ� ������
//				exiting = true;
//				exit_count = 3000; // sysclock�� ���ʰ� ���� �� ������
//			}
//			//00�ʸ��� ȭ�� ���
//			//00�ʸ��� AI���� ���ʸ���
//			Sleep(TICK);
//			sys_clock += TICK;
//		}
//	}
//	return 0;
//}

#include <stdio.h>
#include <Windows.h>
#include <conio.h>


#define TICK 10

int sys_clock = 0;// 0���� ����

int main(void) {
	//Sleep�� ���� ���� 
	
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

	////Ű �Է� �ޱ� ����
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
	return 0;
}