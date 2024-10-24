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
//// 시간관리 Sleep() 스케쥴링으로 약간 밀린다. 시간이 간단하니까
//// TICK 최소단위 10ms  수직선의 좌표 하나에 해당한다고 생각
//// 흐른 시간을 카운트 하겠다.
//// 3초마다 출력 안녕하세요
//// 1초마다 출력 수직선의
//
//int main(void) {
//	if (sys_clock % 1300 == 0) {
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT, HANDLE), color);
//		printf("%d번 색상");
//		color = (color + 1) % 0xFF;
//	}
//	return 0;
//}
//
//int main(void) {
//	
//	int sec = 1;
//	while (1) {// 이루프에서
//		/*
//		if (sys_clock % 3000 == 0) {
//			printf("안녕하세요\n");
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
//			if (key == 'q') {//3초 뒤에 끝내기
//				exiting = true;
//				exit_count = 3000; // sysclock이 몇초가 됬을 때 끝내라
//			}
//			//00초마다 화면 출력
//			//00초마다 AI동작 몇초마다
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

int sys_clock = 0;// 0부터 시작

int main(void) {
	//Sleep에 대한 이해 
	
	//int sec = 1;//sec는 1부터 시작
	//1tick 10ms 이 프로그램이 동작하는 최소 시간 단위
	//가장 단순한 방법Sleep()사용, 이 방법으로 정확한 시간 제어 어려움 -> 밀린다.
	//while (1) {
	//	if (sys_clock % 3000 == 0) {
	//		printf("안녕하세요\n");
	//	}
	//	//sysclock = 0 : 1초텀 후 1초 출력 후 2초로 변경
	//	//sysclock = 1000 : 2초 출력 sec : 3초
	//	//sysclcok = 2000 : 3초 출력 sec : 4초 
	//	//1 ---> 사건----> 2 ---> 사건 ---> 3 --->안녕하세요---> 4 사건 표현의 방식  
	//	if (sys_clock % 1000 == 0) {
	//		printf("sec: %d\n", sec);
	//		sec ++;
	//	}
	//	Sleep(TICK); //10ms 지난 다음 sysclock이 10ms 증가
	//	sys_clock += 10;
	//}

	////키 입력 받기 이해
	//while (1) {
	//	if (_kbhit()) {
	//		int key = _getch();
	//		if (key == 'q') {
	//			break;
	//		}
	//		Sleep(TICK);
	//	}
	//}
	
	//p12 q가 입력되고 나서 3초 후에 종료하기
	int sys_clock = 0;
	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 'q') {
				while (sys_clock < 3000) {// 0 1 2 3
					Sleep(TICK); //10ms 지난 다음 sysclock이 10ms 증가
					sys_clock += 10;
				}
				break;
			}
		}
	}
	return 0;
}