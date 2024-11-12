#ifndef _IO_H_
#define _IO_H_

#include "common.h"

//공통) 원하는 좌표로 이동해서 원하는 색상으로 문자 출력 함수 선언
void printc(POSITION pos, char ch, int color);
//공통) 좌표 이동함수 선언
extern void gotoxy(POSITION pos);
//공통) 글 배경, 글 색상 변경함수 선언
extern void set_color(int color);
//2-1) 키입력을 받는 함수 선언
KEY get_key(void);
//2-3) 선택에 의한 상태 문자열 출력 함수 선언
extern void print_state_info_f(POSITION State_Window_Pos,
	        char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)], 
	        int color);
//2-3) 선택에 의한 명령어 문자열 출력 함수 선언
extern void print_command_message_info(POSITION Command_Window_Pos,
	        char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)], 
	        int color);
//2-3) 다른 오브젝트 선택 시 기존 상태창 문자열 삭제하는 함수 선언
extern void reset_state_window_f(POSITION State_Window_Pos, 
	                             char blank_character, 
								 int color);
//2-3) 다른 오브젝트 선택 시 기존 명령어 창 문자열 삭제하는 함수 선언
extern void reset_command_window_f(POSITION Command_Window_Pos, 
								   char blank_character, 
								   int color);
#endif


