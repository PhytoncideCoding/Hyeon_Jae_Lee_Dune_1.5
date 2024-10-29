//#include <stdio.h>
//#include <Windows.h>
//#include <conio.h>

//#define TICK 10
//
//int sys_clock = 0;// 0부터 시작
//
////p13 열거형에 대한 이해
//typedef enum { //0부터 순서대로 정수 부여 된다. //익명 열거체 바로 안에 있는 멤버 변수들 사용 가능
//	k_none = 0, k_up, k_right, k_left, k_down,
//	k_quit,
//	k_undef,
//} KEY;
////14방향키 입력 받기
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
//	//p10 Sleep에 대한 이해 
//	
//	//int sec = 1;//sec는 1부터 시작
//	//1tick 10ms 이 프로그램이 동작하는 최소 시간 단위
//	//가장 단순한 방법Sleep()사용, 이 방법으로 정확한 시간 제어 어려움 -> 밀린다.
//	//while (1) {
//	//	if (sys_clock % 3000 == 0) {
//	//		printf("안녕하세요\n");
//	//	}
//	//	//sysclock = 0 : 1초텀 후 1초 출력 후 2초로 변경
//	//	//sysclock = 1000 : 2초 출력 sec : 3초
//	//	//sysclcok = 2000 : 3초 출력 sec : 4초 
//	//	//1 ---> 사건----> 2 ---> 사건 ---> 3 --->안녕하세요---> 4 사건 표현의 방식  
//	//	if (sys_clock % 1000 == 0) {
//	//		printf("sec: %d\n", sec);
//	//		sec ++;
//	//	}
//	//	Sleep(TICK); //10ms 지난 다음 sysclock이 10ms 증가
//	//	sys_clock += 10;
//	//}
//
//	////p11 키 입력 받기 이해
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
//	////p12 q가 입력되고 나서 3초 후에 종료하기
//	//int sys_clock = 0;
//	//while (1) {
//	//	if (_kbhit()) {
//	//		int key = _getch();
//	//		if (key == 'q') {
//	//			while (sys_clock < 3000) {// 0 1 2 3
//	//				Sleep(TICK); //10ms 지난 다음 sysclock이 10ms 증가
//	//				sys_clock += 10;
//	//			}
//	//			break;
//	//		}
//	//	}
//	//}
//	////p15 방향 키 입력 받기
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
//	////p16 색상 변경 함수 0~15가지 글자색 0~15가지 배경색 순차변경
//	//for (int color = 0x00; color < 0xFF; color++) {
//	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
//	//	printf("%d번은 무슨 색일까요?\n", color);
//	//}
//	
//	//p17 커서 이동시키기
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

