#include "io.h"

//공통) 좌표 이동함수
void gotoxy(POSITION pos) {
	COORD coord = { pos.column, pos.row }; // 행, 열 반대로 전달
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//공통) 글 배경, 글 색상 변경함수
void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//공통) 원하는 좌표로 이동해서 원하는 색상으로 문자 출력 함수
void printc(POSITION pos, char ch, int color) {
	//1. 원하는 색깔로 설정
	if (color >= 0) {
		set_color(color);
	}
	//2. 원하는 좌표로 이동
	gotoxy(pos);
	//3.인수로 받은 문자를 출력
	printf("%c", ch);
}
//2-1) 방향키 입력받는 함수
KEY get_key(void) {
	if (!_kbhit()) {
		return k_none; //아무 키도 입력 되지않으면 0을 리턴
	}

	int byte = _getch();    // 입력된 키를 전달 받기
	switch (byte) {
	case 27: return k_esc;
	case 32: return k_space; //5를 리턴
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
//2-3) 선택에 의한 상태 문자열 출력 함수
void print_state_info_f(POSITION State_Window_Pos,
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)], int color)
{
	if (color >= 0) {
		set_color(color);
	}
	gotoxy(State_Window_Pos);
	for (int i = 0; i < (STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2); i++) {
		printf("%c", introduce_self[i]);
		if (introduce_self[i] == '\n') {
			State_Window_Pos.row += 1;
			State_Window_Pos.column = MAP_WIDTH + 1;
			gotoxy(State_Window_Pos);
		}
	}
}
//2-3) 선택에 의한 명령어 문자열 출력 함수
void print_command_message_info(POSITION Command_Window_Pos,
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)], int color)
{
	if (color >= 0) {
		set_color(color);
	}
	gotoxy(Command_Window_Pos);
	for (int i = 0; i < (COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2); i++) {
		if (commands_info[i] != '\n') {
			printf("%c", commands_info[i]);
		}
		else {
			Command_Window_Pos.row += 1;
			Command_Window_Pos.column = MAP_WIDTH + 1;
			gotoxy(Command_Window_Pos);
		}
	}
}
//2-3) 다른 오브젝트 선택 시 기존 상태창 문자열 삭제하는 함수
void reset_state_window_f(POSITION State_Window_Pos, char blank_character, int color)
{
	if (color >= 0) {
		set_color(color);
	}
	gotoxy(State_Window_Pos);
	for (int i = 0; i < STATE_WINDOW_MAX_HEIGHT - 2; i++) {
		for (int j = 0; j < STATE_WINDOW_MAX_WIDTH - 2; j++) {
			printf("%c", blank_character);
		}
		if (i == STATE_WINDOW_MAX_HEIGHT - 3) {
			break;
		}
		State_Window_Pos.row += 1;
		State_Window_Pos.column = MAP_WIDTH + 1;
		gotoxy(State_Window_Pos);
	}
}
//2-3) 다른 오브젝트 선택 시 기존 명령어 창 문자열 삭제하는 함수
void reset_command_window_f(POSITION Command_Window_Pos, char blank_character, int color) {

	if (color >= 0) {
		set_color(color);
	}
	gotoxy(Command_Window_Pos);
	for (int i = 0; i < COMMAND_WINDOW_HEIGHT - 2; i++) {
		for (int j = 0; j < COMMAND_WINDOW_WIDTH - 2; j++) {
			printf("%c", blank_character);
		}
		if (i == COMMAND_WINDOW_HEIGHT - 3) {
			break;
		}
		Command_Window_Pos.row += 1;
		Command_Window_Pos.column = MAP_WIDTH + 1;
		gotoxy(Command_Window_Pos);
	}
}
