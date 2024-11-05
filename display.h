#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

// ǥ���� ���� ��ũ�� ����
// �⺻ �۲� �Ͼ��
#define COLOR_DEFAULT 15
#define CURSOR_CURRENT_COLOR 223
#define COLOR_RESOURCE 243
#define INTRO_OUTTRO_TITLE 6
#define INTRO_OUTTRO_CONTENT 14
#define ATREIDES_COLOR 159
#define HACONEN_COLOR 79
#define PLATE_COLOR 143
//��Ȳ���� SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)�� �������� �ʾƼ�
//Dark Yellow: �����̽� Yellow: ��������� �����Ͽ����ϴ�.
#define SPICE_COLOR 111
#define SAND_WORM_COLOR 236
#define ROCK_COLOR 127

// �ڿ� ���� ǥ�� �Լ� ����
extern void display_resource(RESOURCE resource);
// 1) �� ǥ�� ��� �Լ� ����
extern void project_map_f(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
extern void display_map_f(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor
);

// 1) ����â ���簢�� ��� �Լ� ����
extern void project_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH],
	char backbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH]);
extern void display_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH]);
// 1) �ý��� �޼��� ���簢�� ��� �Լ� ����
extern void project_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH],
	char backbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH]);
extern void display_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH]);
// 1) ��ɾ� ���簢�� ��� �Լ� ����
void project_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH],
	char backbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH]);
void display_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH]);
// 1) Ŀ�� �̵� ǥ�� �Լ� ����
extern void display_cursor_f(CURSOR cursor,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor);
// 2) �����̽� �Է½� ����, �ǹ�, ���ֺ� ���� ����â ��� �Լ� ����
void state_window_by_k_space(CURSOR cursor, BUILDING_ATTRIBUTE Atreides_Base, BUILDING_ATTRIBUTE Haconen_Base, BUILDING_ATTRIBUTE Atreides_Plate);
// 2) ��ɾ� ����â ��� �Լ� ����
void command_message_by_k_space(CURSOR cursor, BUILDING_ATTRIBUTE Atreides_Base, BUILDING_ATTRIBUTE Haconen_Base);
// 2) ESC�Է½� ���� ��� ��� �Լ� ����
void eraser_state_command_window(void);
#endif