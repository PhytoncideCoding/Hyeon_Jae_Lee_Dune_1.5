/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#include "display.h"
#include "io.h"

// 출력할 내용들의 좌상단(topleft) 좌표

// 리소스 출력의 첫 시작 위치
const POSITION Resource_Top_Left_Coord = { 0, 0 };
// map 출력의 첫 시작 위치
const POSITION Map_Top_Left_Coord = { 1, 0 };

char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], 
				UNIT_ATTRIBUTE Atreides_Harvestor,
				UNIT_ATTRIBUTE Haconen_Harvestor);
void display_cursor(CURSOR cursor);



// display_system_message()
// display_object_info()
// display_commands()
// ...

//1. 폰트 색상을 결정하고
//2. (세로, 가로) (0, 0)으로 이동
//3. 자원의 상태를 출력한다.
void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(Resource_Top_Left_Coord); //
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

// 배열을 하나 더 추가해서 버퍼링처리
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {//유닛이 위에 올라가면 겹치도록 표현
				if (src[k][i][j] >= 0) {//layer1의 -1로 저장된 공간은 저장하지 않음
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}

//2차원 배열로 인자 수정
//유닛의 소속에 따라 색깔을 설정
//유닛을 구분한다.
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], 
				UNIT_ATTRIBUTE Atreides_Harvestor,
				UNIT_ATTRIBUTE Haconen_Harvestor)
{
	project(map, backbuf);//map에 대한 정보를 2차원 배열 백버퍼에 전달
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) { // 같지 않은 부분을 확인
				POSITION pos = { i, j }; 
				//프론트 버퍼와 같지않는 백버퍼의 문자를 전달해서 출력한다.
				if (backbuf[i][j] == 'B' && MAP_HEIGHT - 3 <= i && i <= MAP_HEIGHT - 2 && 1 <= j && j <=2) {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], ATREIDES_COLOR);
				}
				else if (backbuf[i][j] == 'B' && 1 <= i && i <= 2 && MAP_WIDTH - 3 <= j && j <= MAP_WIDTH - 2) {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], HACONEN_COLOR);
				}
				else if (backbuf[i][j] == 'P' && MAP_HEIGHT - 3 <= i && i <= MAP_HEIGHT - 2 && 3 <= j && j <= 4) {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], PLATE_COLOR);
				}
				else if (backbuf[i][j] == 'P' && 1<= i && i <= 2 && MAP_WIDTH-5 <= j && j <= MAP_WIDTH-4) {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], PLATE_COLOR);
				}
				else if (backbuf[i][j] == '5' && i == (MAP_HEIGHT - 6) && j == 1) {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], SPICE_COLOR);
				}
				else if (backbuf[i][j] == '5' && i == 5 && j == MAP_WIDTH - 2) {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], SPICE_COLOR);
				}
				else if (backbuf[i][j] == 'R' && i == 10 && j == 7 ||
					4 <= i && i <= 5 && 14 <= j && j <= 15 ||
					10 <= i && i <= 11 && 27 <= j && j <= 28 ||
					i == 7 && j == 50 ||
					i == 14 && j == 42
					)
				{
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], ROCK_COLOR);
				}
				else if (backbuf[i][j] == 'H' && Atreides_Harvestor.pos.row == i && Atreides_Harvestor.pos.column == j) {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], ATREIDES_COLOR);
				}
				else if (backbuf[i][j] == 'H' && Haconen_Harvestor.pos.row == i && Haconen_Harvestor.pos.column == j) {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], HACONEN_COLOR);
				}
				else if (backbuf[i][j] == 'W') {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], SAND_WORM_COLOR);
				}
				else {
					printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], COLOR_DEFAULT);
				}
			}
			frontbuf[i][j] = backbuf[i][j]; //프론트 버퍼에 백버퍼를 전달 다음 비교를 위해
		}
	}
}

// frontbuf[][]에서 커서 위치의 문자를 색만 바꿔서 그대로 다시 출력
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	//이전 커서 위치에 문자를 COLOR_DEFAUKT를 출력
	//건물의 원래 색깔을 표시할 알고리즘 필요
	printc(position_move_f(Map_Top_Left_Coord, prev), ch, COLOR_DEFAULT);
	//이동된 위치에 문자를 출력
	ch = frontbuf[curr.row][curr.column];
	printc(position_move_f(Map_Top_Left_Coord, curr), ch, CURSOR_CURRENT_COLOR);
}