#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

#define TICK 10
int sys_clock = 0;

bool exiting = false;
int exit_count = 0;

// 시간관리 Sleep() 스케쥴링으로 약간 밀린다. 시간이 간단하니까
// TICK 최소단위 10ms  수직선의 좌표 하나에 해당한다고 생각
// 흐른 시간을 카운트 하겠다.
// 3초마다 출력 안녕하세요
// 1초마다 출력 수직선의

int main(void) {
	if (sys_clock % 1300 == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT, HANDLE), color);
		printf("%d번 색상");
		color = (color + 1) % 0xFF;
	}
	return 0;
}

int main(void) {
	
	int sec = 1;
	while (1) {// 이루프에서
		/*
		if (sys_clock % 3000 == 0) {
			printf("안녕하세요\n");
		}
		
		if (sys_clock % 1000 == 0) {
			printf("sec: %d\n", sec);	
			sec++;
		}
		Sleep(TICK);
		sys_clock += 10;
		W*/

		if (exiting) {
			exit_count -= TICK;
			if (exit_count <= 0) {
				break;
			}
		}

		if (_kbhit()) {
			int key = _getch();
			if (key == 'q') {//3초 뒤에 끝내기
				exiting = true;
				exit_count = 3000; // sysclock이 몇초가 됬을 때 끝내라
			}
			//00초마다 화면 출력
			//00초마다 AI동작 몇초마다
			Sleep(TICK);
			sys_clock += TICK;
		}
	}
	return 0;
}