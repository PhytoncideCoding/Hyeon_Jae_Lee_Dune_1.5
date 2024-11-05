#include "io.h"

//Ŀ�� ��ǥ �̵��Լ�
void gotoxy(POSITION pos) {
	COORD coord = { pos.column, pos.row }; // ��, �� �ݴ�� ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//ǥ�� ���, �� ���� �����Լ�
void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// 1. ���ϴ� ����� ���� 2. ���ϴ� ��ǥ�� �̵� 3.�μ��� ���� ���ڸ� ���
void printc(POSITION pos, char ch, int color) {
	if (color >= 0) {
		set_color(color);
	}
	gotoxy(pos);
	printf("%c", ch);
}

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

KEY get_key(void) {
	if (!_kbhit()) {
		return k_none; //�ƹ� Ű�� �Է� ���������� 0�� ����
	}

	int byte = _getch();    // �Էµ� Ű�� ���� �ޱ�
	switch (byte) {
	case 27: return k_esc;
	case 32: return k_space; //5�� ����
	case 'q': return k_quit;  // 5 'q'�� ������ ����
	case 224:
		byte = _getch();  // MSB 224�� �Է� �Ǹ� 1����Ʈ �� ���� �ޱ�
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