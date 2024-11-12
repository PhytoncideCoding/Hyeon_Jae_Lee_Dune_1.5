#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <assert.h>
#include <math.h>

/* ================= �ð� �Ķ���� =================== */
#define TICK 10		// time unit(ms)
#define WAITING_SECOND_ARROW 200

#define N_LAYER 2
#define MAP_WIDTH	60
#define MAP_HEIGHT	18

/* ================= â ũ�� �Ķ���� =================== */
// SetConsoleCursorPosition()�Լ��� Ư�� ���
// gotoxy()�� ����� �۵��ϴ� ������ â ũ�� ����

#define STATE_WINDOW_MAX_HEIGHT 18
#define STATE_WINDOW_MAX_WIDTH 50

#define SYSTEM_MESSAGE_W_HEIGHT 10
#define SYSTEM_MESSAGE_W_WIDTH 60

#define COMMAND_WINDOW_HEIGHT 10
#define COMMAND_WINDOW_WIDTH 50

/* ================= 3-1 ������� ���� ���� ��� �� �Ķ���� =================== */
#define COMPARING_WITH_SAND_WORM 2

/* ================= ��ġ, ���� ���� ����ü =================== */
// (��, ��) ��ġ�� ��Ÿ���� ����ü
typedef struct {
	int row, column;
} POSITION;

// Ŀ�� ���� ��ġ, ���� ��ġ�� ��Ÿ���� ����ü 
typedef struct {
	POSITION previous;  // ���� ��ġ
	POSITION current;   // ���� ��ġ
} CURSOR;

// �Է� ������ Ű ���� ����ü
typedef enum {
	k_none = 0, k_up, k_left, k_right, k_down, //1:��, 2: ����, 3: ������, 4 : �Ʒ�
	k_space, k_esc, //5: �����̽�, 6: ESC
	k_quit, //7: ���� ����
	k_undef, // 8: ���ǵ��� ���� Ű �Է�	
} KEY;

// ����Ű�� �ǹ̷����� semantic ����ü �ʱ�ȭ
typedef enum {
	d_stay = 0, d_up, d_left, d_right, d_down
} DIRECTION;
// ����: �� ��ǥ�� ���� ���ϴ� inline �Լ�
inline POSITION position_move_f(POSITION p1, POSITION p2) {
	POSITION p = { p1.row + p2.row, p1.column + p2.column };
	return p;
}

// ����: �� ��ǥ�� ���� ���ϴ� inline �Լ� 
inline POSITION position_subtraction_f_inline(POSITION p1, POSITION p2) {
	POSITION p = { p1.row - p2.row, p1.column - p2.column };
	return p;
}

// 2-1) ����Ű���� Ȯ���ϴ� ��ũ�� �Լ�
#define is_arrow_key_f_mac(k)		(k_up <= (k) && (k) <= k_down)

// 2-1) ȭ��ǥ 'Ű'(KEY)�� '����'(DIRECTION)���� ��ȯ�ϴ� ��ũ���Լ� 
#define key_to_direction_f_mac(k)		(DIRECTION)(k)

// 2-1) ����Ű 1ȸ �Է��� POSITION ���ͷ� ��ȯ�ؼ� ��ǥ�� ������ �غ� �����ִ� �Լ�
inline POSITION dtop(DIRECTION d) {
	static POSITION direction_vector[] = { {0, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
	return direction_vector[d];
}
// 2-2) ���� ����Ű �Է��� POSITION ���ͷ� ��ȯ�ؼ� ��ǥ�� ������ �غ� �����ִ� �Լ�
inline POSITION dtop_f_inline(DIRECTION Key) {
	static POSITION Direction_Vector2_arr[] = { {0, 0}, {-5, 0}, {0, -5}, {0, 5}, {5, 0} };
	return Direction_Vector2_arr[Key];
}
// 2-1) ��ġ ����p�� 1ȸ Ű �Է� ���� ����d �� ���ϴ� ��ũ�� �Լ� 
#define position_by_arrow_move_f_mac(p, d)		(position_move_f((p), dtop(d)))
// 2-2) ��ġ ����p�� 2ȸ Ű �Է� ���� ����d �� ���ϴ� ��ũ�� �Լ�
#define position_by_arrow_move2_f_mac(p, d)		(position_move_f((p), dtop_f_inline(d)))

/* ================= �ڿ�, ����, ����, �ǹ� ����ü ����� =================== */
//�ڿ� ����ü ����
typedef struct {
	int spice;		// ���� ������ �����̽�
	int spice_max;  // �����̽� �ִ� ���差
	int population; // ���� �α� ��
	int population_max;  // ���� ������ �α� ��
} RESOURCE;
//���� ����ü ����
typedef
struct unit_attribute_t {
	POSITION pos[2];		 // ���� ��ġ(position)
	POSITION dest;		 // ������(10estination)
	char representation; // ȭ�鿡 ǥ���� ����
	int speed; // �ֱ�
	int move_period;	 // '�� ms���� �� ĭ �����̴���'�� ����
	int next_move_time;	 // ������ ������ �ʱ� �ð� �� ������ ����
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)];
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)];
} UNIT_ATTRIBUTE;
//���� ����ü ����
typedef
struct land_attribute_t {
	POSITION Land_Position[11];		// ���� ��ġ(position)
	char representation;   // ȭ�鿡 ǥ���� ����
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)];
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)];
} LAND_ATTRIBUTE;
//�ǹ� ����ü ����
typedef
struct building_attribute_t {
	POSITION pos[4];
	char representation;
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)];
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)];
} BUILDING_ATTRIBUTE;

#endif