/*
*  display.c:
* ȭ�鿡 ���� ������ ���
* ��, Ŀ��, �ý��� �޽���, ����â, �ڿ� ���� ���
* io.c�� �ִ� �Լ����� �����
*/

#include "display.h"
#include "io.h"

// ����� ������� �»��(topleft) ��ǥ
// POSITION ����ü�� ������, ������
const POSITION Resource_Top_Left_Coord = { 0, 0 };
// Map�� ù ���� ��ġ ��ǥ
const POSITION Map_Top_Left_Coord = { 1, 0 };

char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);


void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], 
	CURSOR cursor)
{
	display_resource(resource);
	display_map(map);
	display_cursor(cursor);
	// display_system_message()
	// display_object_info()
	// display_commands()
	// ...
}
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

// �迭�� �ϳ� �� �߰��ؼ� ���۸�ó���� �ε巯�� ȭ�� ó�� �Լ�
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {
				if (src[k][i][j] >= 0) { //���߿� ����
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}

void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	project(map, backbuf);//map�� ���� ������ ����ۿ� ����

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) { // ���� ���� �κ��� Ȯ��
				POSITION pos = {i, j }; 
				//����Ʈ ���ۿ� �����ʴ� ������� ���ڸ� �����ؼ� ����Ѵ�.
				printc(position_move_f(Map_Top_Left_Coord, pos), backbuf[i][j], COLOR_DEFAULT);
			}
			frontbuf[i][j] = backbuf[i][j]; //����Ʈ ���ۿ� ����۸� ����
		}
	}
}

// frontbuf[][]���� Ŀ�� ��ġ�� ���ڸ� ���� �ٲ㼭 �״�� �ٽ� ���
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	//���� ��ġ�� ���ڸ� ���
	printc(position_move_f(Map_Top_Left_Coord, prev), ch, COLOR_DEFAULT);
	//�̵��� ��ġ�� ���ڸ� ���
	ch = frontbuf[curr.row][curr.column];
	printc(position_move_f(Map_Top_Left_Coord, curr), ch, COLOR_CURSOR);
}