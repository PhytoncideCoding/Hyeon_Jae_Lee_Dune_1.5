#ifndef _IO_H_
#define _IO_H_

#include "common.h"
//1) Ű�Է��� �޴� �Լ� ����
KEY get_key(void);
//1) pos ��ġ�� ���ϴ� ����� ���ϴ� ���ڸ� ǥ���ϴ� �Լ� ����
void printc(POSITION pos, char ch, int color);
extern void gotoxy(POSITION pos);
void set_color(int color);
extern void print_state_info_f(POSITION State_Window_Pos,
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)], int color);
extern void print_command_message_info(POSITION Command_Window_Pos,
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)], int color);

extern void reset_state_window_f(POSITION State_Window_Pos, char blank_character, int color);
extern void reset_command_window_f(POSITION Command_Window_Pos, char blank_character, int color);
#endif

