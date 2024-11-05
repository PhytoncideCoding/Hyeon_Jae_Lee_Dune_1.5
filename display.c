#include "display.h"
#include "io.h"

// 출력할 내용들의 좌상단(topleft) 좌표

// 리소스 출력의 첫 시작 위치
const POSITION Resource_Top_Left_Coord = { 0, 0 };
// map 출력의 첫 시작 위치
const POSITION Map_Top_Left_Coord = { 1, 0 };
//상태창 출력 첫 시작 위치
const POSITION S_W_Top_Left_Coord = { 1, MAP_WIDTH };
//시스템 메세지 출력 첫 시작 위치 
const POSITION SYSTEM_Message_W_T_L_Coord = { 1 + MAP_HEIGHT, 0 };
//명령어 창 출력 첫 시작 위치
const POSITION Command_Message_T_L_Coord = { 1 + MAP_HEIGHT, MAP_WIDTH };

//맵 버퍼링 배열
char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
//상태창 버퍼링 배열
char frontbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH] = { 0 };
char backbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH] = { 0 };
//시스템 메세지 버퍼링 배열
char frontbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH] = { 0 };
char backbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH] = { 0 };
//명령창 버퍼링 배열
char frontbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH] = { 0 };
char backbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH] = { 0 };


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
//맵 출력 함수
//1layer, 2layer(Bonus 문제) 덧칠해서 표현한다.
void project_map_f(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
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
void display_map_f(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor
)
{
	project_map_f(map, backbuf);//map에 대한 정보를 2차원 배열 백버퍼에 전달
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) { // 같지 않은 부분을 확인
				POSITION Backbuf_Pos = { i, j };
				//프론트 버퍼와 같지않는 백버퍼의 문자를 전달해서 해당 위치에 출력
				if (backbuf[i][j] == 'B' && MAP_HEIGHT - 3 <= i && i <= MAP_HEIGHT - 2 && 1 <= j && j <= 2) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], ATREIDES_COLOR);
				}
				else if (backbuf[i][j] == 'B' && 1 <= i && i <= 2 && MAP_WIDTH - 3 <= j && j <= MAP_WIDTH - 2) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], HACONEN_COLOR);
				}
				else if (backbuf[i][j] == 'P' && MAP_HEIGHT - 3 <= i && i <= MAP_HEIGHT - 2 && 3 <= j && j <= 4) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], PLATE_COLOR);
				}
				else if (backbuf[i][j] == 'P' && 1 <= i && i <= 2 && MAP_WIDTH - 5 <= j && j <= MAP_WIDTH - 4) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], PLATE_COLOR);
				}
				else if ('1' <= backbuf[i][j] && backbuf[i][j] <= '9' && i == (MAP_HEIGHT - 6) && j == 1) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], SPICE_COLOR);
				}
				else if ('1' <= backbuf[i][j] && backbuf[i][j] <= '9' && i == 5 && j == MAP_WIDTH - 2) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], SPICE_COLOR);
				}
				else if (backbuf[i][j] == 'R') {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], ROCK_COLOR);
				}
				else if (backbuf[i][j] == 'H' && Atreides_Harvestor.pos.row == i && Atreides_Harvestor.pos.column == j) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], ATREIDES_COLOR);
				}
				else if (backbuf[i][j] == 'H' && Haconen_Harvestor.pos.row == i && Haconen_Harvestor.pos.column == j) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], HACONEN_COLOR);
				}
				else if (backbuf[i][j] == 'W') {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], SAND_WORM_COLOR);
				}
				else {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], COLOR_DEFAULT);
				}
			}
			frontbuf[i][j] = backbuf[i][j]; // 다음 비교를 위해 프론트 버퍼에 백버퍼를 전달
		}
	}
}
//커서의 이동을 반영하는 커서 출력 함수
void display_cursor_f(CURSOR cursor,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor)
{
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	//이전 커서 위치에 문자를 원래대로 출력
	if ('1' <= ch && ch <= '9') {
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, SPICE_COLOR);
	}
	else if (ch == 'P') {
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, PLATE_COLOR);
	}
	else if (ch == 'W') {
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, SAND_WORM_COLOR);
	}
	else if (ch == 'R') {
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, ROCK_COLOR);
	}
	else if (ch == 'B' && MAP_HEIGHT - 3 <= prev.row && prev.row <= MAP_HEIGHT - 2 &&
		1 <= prev.column && prev.column <= 2)
	{
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, ATREIDES_COLOR);
	}
	else if (ch == 'B' && 1 <= prev.row && prev.row <= 2 &&
		MAP_WIDTH - 3 <= prev.column && prev.column <= MAP_WIDTH - 2)
	{
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, HACONEN_COLOR);
	}
	else if (ch == 'H' && Atreides_Harvestor.pos.row == prev.row &&
		Atreides_Harvestor.pos.column == prev.column)
	{
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, ATREIDES_COLOR);
	}
	else if (ch == 'H' && Haconen_Harvestor.pos.row == prev.row &&
		Haconen_Harvestor.pos.column == prev.column)
	{
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, HACONEN_COLOR);
	}
	else {
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, COLOR_DEFAULT);
	}
	// 새로운 커서위치에 커서 색깔로 출력
	ch = frontbuf[curr.row][curr.column];
	printc(position_move_f(Map_Top_Left_Coord, curr), ch, CURSOR_CURRENT_COLOR);
}
// 상태창 직사각형 출력
void project_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH],
	char backbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH]) {
	for (int i = 0; i < STATE_WINDOW_MAX_HEIGHT; i++) {
		for (int j = 0; j < STATE_WINDOW_MAX_WIDTH; j++) {
			backbuf_state_window_arr[i][j] = state_window_arr[i][j];
		}
	}
}
void display_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH])
{
	project_state_window_f(state_window_arr, backbuf_state_window_arr);
	for (int i = 0; i < STATE_WINDOW_MAX_HEIGHT; i++) {
		for (int j = 0; j < STATE_WINDOW_MAX_WIDTH; j++) {
			if (frontbuf_state_window_arr[i][j] != backbuf_state_window_arr[i][j]) {
				POSITION Pos = { i, j };
				printc(position_move_f(S_W_Top_Left_Coord, Pos),
					backbuf_state_window_arr[i][j], COLOR_DEFAULT);
			}
			frontbuf_state_window_arr[i][j] = backbuf_state_window_arr[i][j];
		}
	}
}
//2-3) 상태 선택창 출력 함수
void state_window_by_k_space(CURSOR cursor, BUILDING_ATTRIBUTE Atreides_Base, BUILDING_ATTRIBUTE Haconen_Base,
	BUILDING_ATTRIBUTE Atreides_Plate)
{
	POSITION Cursor_Current_Pos = cursor.current;
	POSITION Shift_To_State_W = { 1, 1 };
	POSITION Before_Unit_Position = { 0, 0 };
	char ch = frontbuf[Cursor_Current_Pos.row][Cursor_Current_Pos.column];

	if (Before_Unit_Position.row != Cursor_Current_Pos.row ||
		Before_Unit_Position.column != Cursor_Current_Pos.column)
	{
		reset_state_window_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W), ' ', COLOR_DEFAULT);
	}

	if (ch == 'B') {
		for (int i = 0; i < 4; i++) {
			if (Atreides_Base.pos[i].row == Cursor_Current_Pos.row && \
				Atreides_Base.pos[i].column == Cursor_Current_Pos.column)
			{
				print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
					Atreides_Base.introduce_self, COLOR_DEFAULT);
				Before_Unit_Position.row = Atreides_Base.pos[i].row;
				Before_Unit_Position.column = Atreides_Base.pos[i].column;
			}
			else if (Haconen_Base.pos[i].row == Cursor_Current_Pos.row && \
				Haconen_Base.pos[i].column == Cursor_Current_Pos.column)
			{
				print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
					Haconen_Base.introduce_self, COLOR_DEFAULT);
				Before_Unit_Position.row = Haconen_Base.pos[i].row;
				Before_Unit_Position.column = Haconen_Base.pos[i].column;
			}
		}
	}
	else if (ch == 'P') {
		for (int i = 0; i < 4; i++) {
			if (Atreides_Plate.pos[i].row == Cursor_Current_Pos.row && Atreides_Plate.pos[i].column == Cursor_Current_Pos.column) {
				print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
					Atreides_Plate.introduce_self, COLOR_DEFAULT);
				Before_Unit_Position.row = Atreides_Plate.pos[i].row;
				Before_Unit_Position.column = Atreides_Plate.pos[i].column;
			}
		}
	}
}
//2-3) 명령어 선택창 출력 함수
void command_message_by_k_space(CURSOR cursor, BUILDING_ATTRIBUTE Atreides_Base, BUILDING_ATTRIBUTE Haconen_Base) {
	//스페이스를 눌렀을 때 커서의 위치
	POSITION Cursor_Current_Pos = cursor.current;
	POSITION Shift_To_Command_W = { 1, 1 };

	char ch = frontbuf[Cursor_Current_Pos.row][Cursor_Current_Pos.column];
	POSITION Before_Unit_Position = { 0, 0 };

	if (Before_Unit_Position.row != Cursor_Current_Pos.row ||
		Before_Unit_Position.column != Cursor_Current_Pos.column)
	{
		reset_command_window_f(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
			' ', COLOR_DEFAULT);
	}

	if (ch == 'B') {
		for (int i = 0; i < 4; i++) {

			if (Atreides_Base.pos[i].row == Cursor_Current_Pos.row && \
				Atreides_Base.pos[i].column == Cursor_Current_Pos.column)
			{
				print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
					Atreides_Base.commands_info, COLOR_DEFAULT);
				Before_Unit_Position.row = Atreides_Base.pos[i].row;
				Before_Unit_Position.column = Atreides_Base.pos[i].column;
			}
			else if (Haconen_Base.pos[i].row == Cursor_Current_Pos.row && \
				Haconen_Base.pos[i].column == Cursor_Current_Pos.column)
			{
				print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
					Haconen_Base.commands_info, COLOR_DEFAULT);
				Before_Unit_Position.row = Haconen_Base.pos[i].row;
				Before_Unit_Position.column = Haconen_Base.pos[i].column;
			}
		}
	}
}
void eraser_state_command_window(void) {
	POSITION Shift_To_State_W = { 1, 1 };
	POSITION Shift_To_Command_W = { 1, 1 };
	reset_state_window_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W), ' ', COLOR_DEFAULT);
	reset_command_window_f(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W), ' ', COLOR_DEFAULT);
}
// 시스템 메시지 직사각형 출력 함수
void project_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH],
	char backbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH])
{
	for (int i = 0; i < SYSTEM_MESSAGE_W_HEIGHT; i++) {
		for (int j = 0; j < SYSTEM_MESSAGE_W_WIDTH; j++) {
			backbuf_system_message_arr[i][j] = system_message_arr[i][j];
		}
	}
}
void display_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH])
{
	project_system_message_w_f(system_message_arr, backbuf_system_message_arr);
	for (int i = 0; i < SYSTEM_MESSAGE_W_HEIGHT; i++) {
		for (int j = 0; j < SYSTEM_MESSAGE_W_WIDTH; j++) {
			if (frontbuf_system_message_arr[i][j] != backbuf_system_message_arr[i][j]) {
				POSITION System_Message_Pos = { i, j };
				//프론트 버퍼와 같지않는 백버퍼의 문자를 전달해서 출력한다.
				printc(position_move_f(SYSTEM_Message_W_T_L_Coord, System_Message_Pos),
					backbuf_system_message_arr[i][j], COLOR_DEFAULT);
			}
			frontbuf_system_message_arr[i][j] = backbuf_system_message_arr[i][j];
		}
	}
}
//명령어 직사각형 출력 함수
void project_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH],
	char backbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH])
{
	for (int i = 0; i < COMMAND_WINDOW_HEIGHT; i++) {
		for (int j = 0; j < COMMAND_WINDOW_WIDTH; j++) {
			backbuf_command_w_arr[i][j] = command_window_arr[i][j];
		}
	}
}
void display_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH]) {
	project_command_message_w_f(command_window_arr, backbuf_command_w_arr);
	for (int i = 0; i < COMMAND_WINDOW_HEIGHT; i++) {
		for (int j = 0; j < COMMAND_WINDOW_WIDTH; j++) {
			if (frontbuf_command_w_arr[i][j] != backbuf_command_w_arr[i][j]) {
				POSITION Command_Pos = { i, j };
				printc(position_move_f(Command_Message_T_L_Coord, Command_Pos),
					backbuf_command_w_arr[i][j], COLOR_DEFAULT);
			}
			frontbuf_command_w_arr[i][j] = backbuf_command_w_arr[i][j];
		}
	}
}

