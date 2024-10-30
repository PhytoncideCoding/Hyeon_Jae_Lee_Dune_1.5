/*
*  display.c:
* ȭ�鿡 ���� ������ ���
* ��, Ŀ��, �ý��� �޽���, ����â, �ڿ� ���� ���
* io.c�� �ִ� �Լ����� �����
*/

#include "display.h"
#include "io.h"

// ����� ������� �»��(topleft) ��ǥ

// ���ҽ� ����� ù ���� ��ġ
const POSITION Resource_Top_Left_Coord = { 0, 0 };
// map ����� ù ���� ��ġ
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

//1. ��Ʈ ������ �����ϰ�
//2. (����, ����) (0, 0)���� �̵�
//3. �ڿ��� ���¸� ����Ѵ�.
void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(Resource_Top_Left_Coord); //
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

// �迭�� �ϳ� �� �߰��ؼ� ���۸�ó��
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {//������ ���� �ö󰡸� ��ġ���� ǥ��
				if (src[k][i][j] >= 0) {//layer1�� -1�� ����� ������ �������� ����
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}

//2���� �迭�� ���� ����
//������ �Ҽӿ� ���� ������ ����
//������ �����Ѵ�.
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], 
				UNIT_ATTRIBUTE Atreides_Harvestor,
				UNIT_ATTRIBUTE Haconen_Harvestor)
{
	project(map, backbuf);//map�� ���� ������ 2���� �迭 ����ۿ� ����
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) { // ���� ���� �κ��� Ȯ��
				POSITION pos = { i, j }; 
				//����Ʈ ���ۿ� �����ʴ� ������� ���ڸ� �����ؼ� ����Ѵ�.
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
			frontbuf[i][j] = backbuf[i][j]; //����Ʈ ���ۿ� ����۸� ���� ���� �񱳸� ����
		}
	}
}

// frontbuf[][]���� Ŀ�� ��ġ�� ���ڸ� ���� �ٲ㼭 �״�� �ٽ� ���
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	//���� Ŀ�� ��ġ�� ���ڸ� COLOR_DEFAUKT�� ���
	//�ǹ��� ���� ������ ǥ���� �˰��� �ʿ�
	printc(position_move_f(Map_Top_Left_Coord, prev), ch, COLOR_DEFAULT);
	//�̵��� ��ġ�� ���ڸ� ���
	ch = frontbuf[curr.row][curr.column];
	printc(position_move_f(Map_Top_Left_Coord, curr), ch, CURSOR_CURRENT_COLOR);
}