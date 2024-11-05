#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

// 표시할 색상 매크로 정의
// 기본 글꼴 하얀색
#define COLOR_DEFAULT 15
#define CURSOR_CURRENT_COLOR 223
#define COLOR_RESOURCE 243
#define INTRO_OUTTRO_TITLE 6
#define INTRO_OUTTRO_CONTENT 14
#define ATREIDES_COLOR 159
#define HACONEN_COLOR 79
#define PLATE_COLOR 143
//주황색은 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)에 존재하지 않아서
//Dark Yellow: 스파이스 Yellow: 샌드웜으로 설정하였습니다.
#define SPICE_COLOR 111
#define SAND_WORM_COLOR 236
#define ROCK_COLOR 127

// 자원 상태 표시 함수 선언
extern void display_resource(RESOURCE resource);
// 1) 맵 표시 출력 함수 선언
extern void project_map_f(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
extern void display_map_f(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor
);

// 1) 상태창 직사각형 출력 함수 선언
extern void project_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH],
	char backbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH]);
extern void display_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH]);
// 1) 시스템 메세지 직사각형 출력 함수 선언
extern void project_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH],
	char backbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH]);
extern void display_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH]);
// 1) 명령어 직사각형 출력 함수 선언
void project_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH],
	char backbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH]);
void display_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH]);
// 1) 커서 이동 표시 함수 선언
extern void display_cursor_f(CURSOR cursor,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor);
// 2) 스페이스 입력시 지형, 건물, 유닛별 상태 선택창 출력 함수 선언
void state_window_by_k_space(CURSOR cursor, BUILDING_ATTRIBUTE Atreides_Base, BUILDING_ATTRIBUTE Haconen_Base, BUILDING_ATTRIBUTE Atreides_Plate);
// 2) 명령어 선택창 출력 함수 선언
void command_message_by_k_space(CURSOR cursor, BUILDING_ATTRIBUTE Atreides_Base, BUILDING_ATTRIBUTE Haconen_Base);
// 2) ESC입력시 선택 취소 기능 함수 선언
void eraser_state_command_window(void);
#endif