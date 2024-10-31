#include "io.h"

//Ŀ�� ��ǥ �̵��Լ�
void gotoxy(POSITION pos) {
	COORD coord = { pos.column, pos.row }; // ��, �� �ݴ�� ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//ǥ�� ���, �� ���� �����Լ�
void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// 1. ���ϴ� ����� ���� 2. ���ϴ� ��ǥ�� �̵� 3.�μ��� ���� ���ڸ� ���
void printc(POSITION pos, char ch, int color) {
	if (color >= 0) {
		set_color(color);
	}
	gotoxy(pos);
	printf("%c", ch);
}

KEY get_key(void) {
	if (!_kbhit()) {
		return k_none; //�ƹ� Ű�� �Է� ���������� 0�� ����
	}

	int byte = _getch();    // �Էµ� Ű�� ���� �ޱ�
	switch (byte) {
	case 'q': return k_quit;  // 5 'q'�� ������ ����
	case 224:
		byte = _getch();  // MSB 224�� �Է� �Ǹ� 1����Ʈ �� ���� �ޱ�
		switch (byte) {
		case 72: return k_up; //1
		case 75: return k_left; //2
		case 77: return k_right; //3
		case 80: return k_down; //4
		default: return k_undef; //6
		}
	default: return k_undef; //6
	}
}


