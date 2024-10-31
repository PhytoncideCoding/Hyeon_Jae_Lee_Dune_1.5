#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

// 표시할 색상 정의
#define COLOR_DEFAULT 15 //하얀 글꼴
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

extern void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
extern void display_resource(RESOURCE resource);
extern void display_map_f(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor);
extern void display_cursor_f(CURSOR cursor,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor);

// display_system_message()
// display_object_info()
// display_commands()
// ...

#endif
