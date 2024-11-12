/* ================= header part =================== */
#include "display.h"
#include "io.h"

// ���ҽ� ����� ù ���� ��ġ
const POSITION Resource_Top_Left_Coord = { 0, 0 };
// map ����� ù ���� ��ġ ����� ����ü ����
const POSITION Map_Top_Left_Coord = { 1, 0 };
//����â ��� ù ���� ��ġ ����� ����ü ���� 
const POSITION S_W_Top_Left_Coord = { 1, MAP_WIDTH };
//�ý��� �޼��� ��� ù ���� ��ġ ����� ����ü ����
const POSITION SYSTEM_Message_W_T_L_Coord = { 1 + MAP_HEIGHT, 0 };
//��ɾ� â ��� ù ���� ��ġ ����� ����ü ����
const POSITION Command_Message_T_L_Coord = { 1 + MAP_HEIGHT, MAP_WIDTH };
//�� ���۸� �迭 �ʱ�ȭ
char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
//����â ���۸� �迭 �ʱ�ȭ
char frontbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH] = { 0 };
char backbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH] = { 0 };
//�ý��� �޼��� ���۸� �迭 �ʱ�ȭ
char frontbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH] = { 0 };
char backbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH] = { 0 };
//���â ���۸� �迭 �ʱ�ȭ
char frontbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH] = { 0 };
char backbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH] = { 0 };


//1) �ڿ� ���� ��� �Լ�
void display_resource(RESOURCE resource) {
	//��Ʈ ���� ����
	set_color(COLOR_RESOURCE);
	//�Էµ� ��ǥ�� �̵�
	gotoxy(Resource_Top_Left_Coord);
	//�ش� ��ġ�� �ڿ� ���� ���
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

//1) �� ���۸� �Լ�.
void project_map_f(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {
				//������ ���� �ö󰡸� ��ġ���� ǥ��
				if (src[k][i][j] >= 0) {
					//layer2�� -1�� ����� ������ �迭�� ���� ���� ���� �ʴ´�.
					dest[i][j] = src[k][i][j];
				}
			}  
		}
	}
}
//1) �� ��� �Լ�
void display_map_f(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor,
	LAND_ATTRIBUTE Rocks,
	UNIT_ATTRIBUTE Sand_Worm

)
{
	project_map_f(map, backbuf);//map�� ���� ������ 2���� �迭 ����ۿ� ����
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			// ����ư ���ۿ� ������� ���� ���� �κ��� Ȯ��
			if (frontbuf[i][j] != backbuf[i][j]) { 
				POSITION Backbuf_Pos = { i, j };
				//����Ʈ ���ۿ� �����ʴ� ������� ���ڸ� �����ؼ� �ش� ��ġ�� ���
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
				else if (backbuf[i][j] == 'H' && Atreides_Harvestor.pos[0].row == i && Atreides_Harvestor.pos[0].column == j) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], ATREIDES_COLOR);
				}
				else if (backbuf[i][j] == 'H' && Haconen_Harvestor.pos[0].row == i && Haconen_Harvestor.pos[0].column == j) {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], HACONEN_COLOR);
				}
				else if (backbuf[i][j] == 'W') {
					if (Sand_Worm.pos[0].row == i && Sand_Worm.pos[0].column == j) {
						printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], SAND_WORM_COLOR);
					}
					else if (Sand_Worm.pos[1].row == i && Sand_Worm.pos[1].column == j) {
						printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], SAND_WORM_COLOR);
					}
				}
				else {
					printc(position_move_f(Map_Top_Left_Coord, Backbuf_Pos), backbuf[i][j], COLOR_DEFAULT);
				}
			}
			frontbuf[i][j] = backbuf[i][j]; // ���� �񱳸� ���� ����Ʈ ���ۿ� ����۸� ����
		}
	}
}
//2-1) Ŀ���� �̵��� �ݿ��ϴ� Ŀ�� ��� �Լ�
void display_cursor_f(CURSOR cursor,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor)
{
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	//���� Ŀ�� ��ġ�� ���ڸ� ������� ���
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
	else if (ch == 'H' && Atreides_Harvestor.pos[0].row == prev.row &&
		Atreides_Harvestor.pos[0].column == prev.column)
	{
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, ATREIDES_COLOR);
	}
	else if (ch == 'H' && Haconen_Harvestor.pos[0].row == prev.row &&
		Haconen_Harvestor.pos[0].column == prev.column)
	{
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, HACONEN_COLOR);
	}
	else {
		printc(position_move_f(Map_Top_Left_Coord, prev), ch, COLOR_DEFAULT);
	}
	// ���ο� Ŀ����ġ�� Ŀ�� ����� ���
	ch = frontbuf[curr.row][curr.column];
	printc(position_move_f(Map_Top_Left_Coord, curr), ch, CURSOR_CURRENT_COLOR);
}
//1) ����â ���簢�� ���۸� �Լ�
void project_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH],
	char backbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH]) {
	for (int i = 0; i < STATE_WINDOW_MAX_HEIGHT; i++) {
		for (int j = 0; j < STATE_WINDOW_MAX_WIDTH; j++) {
			backbuf_state_window_arr[i][j] = state_window_arr[i][j];
		}
	}
}
//1) ����â ���簢�� ��� �Լ�
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
//1) �ý��� �޽��� ���簢�� ���۸� �Լ�
void project_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH],
	char backbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH])
{
	for (int i = 0; i < SYSTEM_MESSAGE_W_HEIGHT; i++) {
		for (int j = 0; j < SYSTEM_MESSAGE_W_WIDTH; j++) {
			backbuf_system_message_arr[i][j] = system_message_arr[i][j];
		}
	}
}
//1) �ý��� �޼��� ���簢�� ��� �Լ�
void display_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH])
{
	project_system_message_w_f(system_message_arr, backbuf_system_message_arr);
	for (int i = 0; i < SYSTEM_MESSAGE_W_HEIGHT; i++) {
		for (int j = 0; j < SYSTEM_MESSAGE_W_WIDTH; j++) {
			if (frontbuf_system_message_arr[i][j] != backbuf_system_message_arr[i][j]) {
				POSITION System_Message_Pos = { i, j };
				//����Ʈ ���ۿ� �����ʴ� ������� ���ڸ� �����ؼ� ����Ѵ�.
				printc(position_move_f(SYSTEM_Message_W_T_L_Coord, System_Message_Pos),
					backbuf_system_message_arr[i][j], COLOR_DEFAULT);
			}
			frontbuf_system_message_arr[i][j] = backbuf_system_message_arr[i][j];
		}
	}
}
//1) ��ɾ� ���簢�� ���۸� �Լ�
void project_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH],
	char backbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH])
{
	for (int i = 0; i < COMMAND_WINDOW_HEIGHT; i++) {
		for (int j = 0; j < COMMAND_WINDOW_WIDTH; j++) {
			backbuf_command_w_arr[i][j] = command_window_arr[i][j];
		}
	}
}
//1) ��ɾ� ���簢�� ��� �Լ�
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
//2-3) ���ÿ� ���� ����â ��� �Լ�
void state_window_by_k_space(CURSOR cursor, LAND_ATTRIBUTE Rocks, 
	 LAND_ATTRIBUTE Spice, LAND_ATTRIBUTE Desert, UNIT_ATTRIBUTE Sand_Worm,
	 BUILDING_ATTRIBUTE Atreides_Base,  BUILDING_ATTRIBUTE Atreides_Plate, 
	 UNIT_ATTRIBUTE Atreides_Harvestor, 
	 BUILDING_ATTRIBUTE Haconen_Base, BUILDING_ATTRIBUTE Haconen_Plate,
	 UNIT_ATTRIBUTE Haconen_Harvestor)
{
	POSITION Cursor_Current_Pos = cursor.current;
	POSITION Shift_To_State_W = { 1, 1 };
	POSITION Before_Unit_Position = { 0, 0 };
	char ch = frontbuf[Cursor_Current_Pos.row][Cursor_Current_Pos.column];
	
	//�ʹݿ� �� ����� ���� ����
	static int state_count_k_space = 0;
	if (state_count_k_space >=1 && (Before_Unit_Position.row != Cursor_Current_Pos.row ||
		Before_Unit_Position.column != Cursor_Current_Pos.column))
	{
		reset_state_window_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W), ' ', COLOR_DEFAULT);
	}
	if (state_count_k_space == 0) {
		state_count_k_space++;
	}
	//����
	if (ch == 'R') {
		for (int i = 0; i < 11; i++) {
			if (Rocks.Land_Position[i].row == Cursor_Current_Pos.row &&
				Rocks.Land_Position[i].column == Cursor_Current_Pos.column) 
			{
				print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
					Rocks.introduce_self, COLOR_DEFAULT);
				Before_Unit_Position.row = Rocks.Land_Position[i].row;
				Before_Unit_Position.column = Rocks.Land_Position[i].column;
			}
		}
	}
	//�����̽�
	else if ( '1' <= ch && ch <= '9') {
		for (int i = 0; i < 2; i++) {
			if (Spice.Land_Position[i].row == Cursor_Current_Pos.row &&
				Spice.Land_Position[i].column == Cursor_Current_Pos.column)
			{
				print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
					Spice.introduce_self, COLOR_DEFAULT);
				Before_Unit_Position.row = Spice.Land_Position[i].row;
				Before_Unit_Position.column = Spice.Land_Position[i].column;
			}
		}
	}
	//�����
	else if (ch == 'W') {
		for (int i = 0; i < 2; i++) {
			if (Sand_Worm.pos[i].row == Cursor_Current_Pos.row &&
				Sand_Worm.pos[i].column == Cursor_Current_Pos.column)
			{
				print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
					  Sand_Worm.introduce_self, COLOR_DEFAULT);
				Before_Unit_Position.row = Sand_Worm.pos[i].row;
				Before_Unit_Position.column = Sand_Worm.pos[i].column;
			}
		}
	}
	//���� �Ϻ�����
	else if (ch == 'H') {
		if (Atreides_Harvestor.pos[0].row == Cursor_Current_Pos.row &&
			Atreides_Harvestor.pos[0].column == Cursor_Current_Pos.column)
		{
			print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
				Atreides_Harvestor.introduce_self, COLOR_DEFAULT);
			Before_Unit_Position.row = Atreides_Harvestor.pos[0].row;
			Before_Unit_Position.column = Atreides_Harvestor.pos[0].column;
		}
		else if (Haconen_Harvestor.pos[0].row == Cursor_Current_Pos.row &&
			Haconen_Harvestor.pos[0].column == Cursor_Current_Pos.column)
		{
			print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
				Haconen_Harvestor.introduce_self, COLOR_DEFAULT);
			Before_Unit_Position.row = Haconen_Harvestor.pos[0].row;
			Before_Unit_Position.column = Haconen_Harvestor.pos[0].column;
		}
	}
	//����
	else if (ch == 'P') {
		for (int i = 0; i < 4; i++) {
			if (Atreides_Plate.pos[i].row == Cursor_Current_Pos.row && Atreides_Plate.pos[i].column == Cursor_Current_Pos.column) {
				print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
					Atreides_Plate.introduce_self, COLOR_DEFAULT);
				Before_Unit_Position.row = Atreides_Plate.pos[i].row;
				Before_Unit_Position.column = Atreides_Plate.pos[i].column;
			}
			else if (Haconen_Plate.pos[i].row == Cursor_Current_Pos.row &&
				Haconen_Plate.pos[i].column == Cursor_Current_Pos.column)
			{
				print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
					Haconen_Plate.introduce_self, COLOR_DEFAULT);
				Before_Unit_Position.row = Haconen_Plate.pos[i].row;
				Before_Unit_Position.column = Haconen_Plate.pos[i].column;
			}
		}
	}
	//����
	else if (ch == 'B') {
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
	//�縷
	else {
		print_state_info_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W),
			Desert.introduce_self, COLOR_DEFAULT);
		Before_Unit_Position.row = Cursor_Current_Pos.row; //Ŀ���� ��ġ�� ���� ���� ��ġ�� �ʱ�ȭ ���ش�.
		Before_Unit_Position.column = Cursor_Current_Pos.column;
	}
}
//2-3) ���ÿ� ���� ��ɾ� ��� �Լ�
void command_message_by_k_space(CURSOR cursor, LAND_ATTRIBUTE Rocks,
	LAND_ATTRIBUTE Spice, UNIT_ATTRIBUTE Sand_Worm,
	BUILDING_ATTRIBUTE Atreides_Base, BUILDING_ATTRIBUTE Atreides_Plate,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	BUILDING_ATTRIBUTE Haconen_Base, BUILDING_ATTRIBUTE Haconen_Plate,
	UNIT_ATTRIBUTE Haconen_Harvestor)
{
	//�����̽��� ������ �� Ŀ���� ��ġ ����
	POSITION Cursor_Current_Pos = cursor.current;
	POSITION Shift_To_Command_W = { 1, 1 };
	//Ŀ�� ��ġ�� ���ڸ� ch�� ����
	char ch = frontbuf[Cursor_Current_Pos.row][Cursor_Current_Pos.column];
	POSITION Before_Unit_Position = { 0, 0 };
	
	//�� ���� �� ���� �Ǿ��� �� ���� ���� ���
	static int command_count_k_space = 0;
	if (command_count_k_space >= 1 && (Before_Unit_Position.row != Cursor_Current_Pos.row ||
		Before_Unit_Position.column != Cursor_Current_Pos.column))
	{
		reset_command_window_f(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
			' ', COLOR_DEFAULT);
	}
	if (command_count_k_space == 0) {
		command_count_k_space++;
	}

	//����
	if (ch == 'R') {
		for (int i = 0; i < 11; i++) {
			if (Rocks.Land_Position[i].row == Cursor_Current_Pos.row &&
				Rocks.Land_Position[i].column == Cursor_Current_Pos.column)
			{
				print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
					Rocks.commands_info, COLOR_DEFAULT);
				Before_Unit_Position.row = Rocks.Land_Position[i].row;
				Before_Unit_Position.column = Rocks.Land_Position[i].column;
			}
		}
	}
	//�����̽�
	else if ('1' <= ch && ch <= '9') {
		for (int i = 0; i < 2; i++) {
			if (Spice.Land_Position[i].row == Cursor_Current_Pos.row &&
				Spice.Land_Position[i].column == Cursor_Current_Pos.column)
			{
				print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
					Spice.commands_info, COLOR_DEFAULT);
				Before_Unit_Position.row = Spice.Land_Position[i].row;
				Before_Unit_Position.column = Spice.Land_Position[i].column;
			}
		}
	}
	//����
	else if (ch == 'P') {
		for (int i = 0; i < 4; i++) {
			if (Atreides_Plate.pos[i].row == Cursor_Current_Pos.row &&
				Atreides_Plate.pos[i].column == Cursor_Current_Pos.column)
			{
				print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
					Atreides_Plate.commands_info, COLOR_DEFAULT);
				Before_Unit_Position.row = Atreides_Plate.pos[i].row;
				Before_Unit_Position.column = Atreides_Plate.pos[i].column;
			}
			else if (Haconen_Plate.pos[i].row == Cursor_Current_Pos.row &&
				Haconen_Plate.pos[i].column == Cursor_Current_Pos.column)
			{
				print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
					Haconen_Plate.commands_info, COLOR_DEFAULT);
				Before_Unit_Position.row = Haconen_Plate.pos[i].row;
				Before_Unit_Position.column = Haconen_Plate.pos[i].column;
			}
		}
	}
	//����: �����
	else if (ch == 'W') {
		for (int i = 0; i < 2; i++) {
			if (Sand_Worm.pos[i].row == Cursor_Current_Pos.row &&
				Sand_Worm.pos[i].column == Cursor_Current_Pos.column)
			{
				print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
					Sand_Worm.commands_info, COLOR_DEFAULT);
				Before_Unit_Position.row = Sand_Worm.pos[i].row;
				Before_Unit_Position.column = Sand_Worm.pos[i].column;
			}
		}
	}
	//����: �Ϻ�����
	else if (ch == 'H') {
		if (Atreides_Harvestor.pos[0].row == Cursor_Current_Pos.row &&
			Atreides_Harvestor.pos[0].column == Cursor_Current_Pos.column)
		{
			print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
				Atreides_Harvestor.commands_info, COLOR_DEFAULT);
			Before_Unit_Position.row = Atreides_Harvestor.pos[0].row;
			Before_Unit_Position.column = Atreides_Harvestor.pos[0].column;
		}
		else if (Haconen_Harvestor.pos[0].row == Cursor_Current_Pos.row &&
			Haconen_Harvestor.pos[0].column == Cursor_Current_Pos.column)
		{
			print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
				Haconen_Harvestor.commands_info, COLOR_DEFAULT);
			Before_Unit_Position.row = Haconen_Harvestor.pos[0].row;
			Before_Unit_Position.column = Haconen_Harvestor.pos[0].column;
		}
	}
	// ����
	else if (ch == 'B') {
		for (int i = 0; i < 4; i++) {

			if (Atreides_Base.pos[i].row == Cursor_Current_Pos.row && \
				Atreides_Base.pos[i].column == Cursor_Current_Pos.column)
			{
				print_command_message_info(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W),
					Atreides_Base.commands_info, COLOR_DEFAULT);
				Before_Unit_Position.row = Atreides_Base.pos[i].row;
				Before_Unit_Position.column = Atreides_Base.pos[i].column;
			}
			else if (Haconen_Base.pos[i].row == Cursor_Current_Pos.row &&
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
//2-4) ���Ű �Է����� ����â, ��ɾ� â ���� �Լ�
void eraser_state_command_window(void) {
	POSITION Shift_To_State_W = { 1, 1 };
	POSITION Shift_To_Command_W = { 1, 1 };
	reset_state_window_f(position_move_f(S_W_Top_Left_Coord, Shift_To_State_W), ' ', COLOR_DEFAULT);
	reset_command_window_f(position_move_f(Command_Message_T_L_Coord, Shift_To_Command_W), ' ', COLOR_DEFAULT);
}


