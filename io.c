#include "io.h"

//커서 좌표 이동함수
void gotoxy(POSITION pos) {
	COORD coord = { pos.column, pos.row }; // 행, 열 반대로 전달
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//표현 배경, 글 색상 변경함수
void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// 1. 원하는 색깔로 설정 2. 원하는 좌표로 이동 3.인수로 받은 문자를 출력
void printc(POSITION pos, char ch, int color) {
	if (color >= 0) {
		set_color(color);
	}
	gotoxy(pos);
	printf("%c", ch);
}

KEY get_key(void) {
	if (!_kbhit()) {
		return k_none; //아무 키도 입력 되지않으면 0을 리턴
	}

	int byte = _getch();    // 입력된 키를 전달 받기
	switch (byte) {
	case 'q': return k_quit;  // 5 'q'를 누르면 종료
	case 224:
		byte = _getch();  // MSB 224가 입력 되면 1바이트 더 전달 받기
		switch (byte) {
		case 72: return k_up; //1
		case 75: return k_left; //2
		case 77: return k_right; //3
		case 80: return k_down; //4
		default: return k_undef; //6
		}
	default: return k_undef; //6
	}
}


