#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <assert.h>

/* ================= system parameters =================== */
#define TICK 10		// time unit(ms)
#define WAITING_SECOND_ARROW 500

#define N_LAYER 2
#define MAP_WIDTH	60
#define MAP_HEIGHT	18

#define STATE_WINDOW_MAX_HEIGHT 18
#define STATE_WINDOW_MAX_WIDTH 50
// 배열 크기에 따라 gotoxy()함수가 제대로 작동하지 않을 수 있다.
// SetConsoleCursorPosition()함수의 특성
#define SYSTEM_MESSAGE_W_HEIGHT 10
#define SYSTEM_MESSAGE_W_WIDTH 60

#define COMMAND_WINDOW_HEIGHT 10
#define COMMAND_WINDOW_WIDTH 50

/* ================= 위치와 방향 =================== */
//common.h에 구조체들에 대한 선언
// 맵에서 위치를 나타내는 구조체
typedef struct {
	int row, column;
} POSITION;

// 커서 위치
typedef struct {
	POSITION previous;  // 직전 위치
	POSITION current;   // 현재 위치
} CURSOR;

// 입력 가능한 키 종류.
typedef enum {
	// k_none: 입력된 키가 없음. d_stay(안 움직이는 경우)에 대응
	k_none = 0, k_up, k_left, k_right, k_down,
	k_space, k_esc,
	k_quit,
	k_undef, // 정의되지 않은 키 입력	
} KEY;


// DIRECTION은 KEY의 부분집합이지만, semantic 열거체 정의
typedef enum {
	d_stay = 0, d_up, d_left, d_right, d_down
} DIRECTION;


/* ================= 위치와 방향(2) =================== */
// 편의성을 위한 함수들. KEY, POSITION, DIRECTION 구조체들을 유기적으로 변환

// 편의성 함수
inline POSITION position_move_f(POSITION p1, POSITION p2) {
	POSITION p = { p1.row + p2.row, p1.column + p2.column };
	return p;
}

// p1 - p2
inline POSITION position_subtraction_f_inline(POSITION p1, POSITION p2) {
	POSITION p = { p1.row - p2.row, p1.column - p2.column };
	return p;
}

// 방향키인지 확인하는 함수 // k_up : 1 ~ k_down : 4
#define is_arrow_key_f_mac(k)		(k_up <= (k) && (k) <= k_down)

// 화살표 '키'(KEY)를 '방향'(DIRECTION)으로 변환. 정수 값은 똑같으니 타입만 바꿔주면 됨
#define key_to_direction_f_mac(k)		(DIRECTION)(k)

// DIRECTION을 POSITION 벡터로 변환해서 좌표를 연산할 준비를 도와주는 함수
inline POSITION dtop(DIRECTION d) {
	static POSITION direction_vector[] = { {0, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
	return direction_vector[d];
}

inline POSITION dtop_f_inline(DIRECTION Key) {
	static POSITION Direction_Vector2_arr[] = { {0, 0}, {-5, 0}, {0, -5}, {0, 5}, {5, 0} };
	return Direction_Vector2_arr[Key];
}

// p를 d 방향으로 이동시킨 POSITION
#define position_by_arrow_move_f_mac(p, d)		(position_move_f((p), dtop(d)))
#define position_by_arrow_move2_f_mac(p, d)		(position_move_f((p), dtop_f_inline(d)))

/* ================= 구조체 선언부 =================== */
//자원 구조체 선언
typedef struct {
	int spice;		// 현재 보유한 스파이스
	int spice_max;  // 스파이스 최대 저장량
	int population; // 현재 인구 수
	int population_max;  // 수용 가능한 인구 수
} RESOURCE;
//유닛 구조체 선언
typedef
struct unit_attribute_t {
	POSITION pos[2];		 // 현재 위치(position)
	POSITION dest;		 // 목적지(destination)
	char representation; // 화면에 표시할 문자
	int speed;
	int move_period;	 // '몇 ms마다 한 칸 움직이는지'를 뜻함
	int next_move_time;	 // 다음에 움직일 시간
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)];
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)];
} UNIT_ATTRIBUTE;
//지형 구조체 선언
typedef
struct land_attribute_t {
	POSITION Land_Position[11];		// 현재 위치(position)
	char representation;   // 화면에 표시할 문자
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)];
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)];
} LAND_ATTRIBUTE;
//건물 구조체 선언
typedef
struct building_attribute_t {
	POSITION pos[4];
	char representation;
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)];
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)];
} BUILDING_ATTRIBUTE;

#endif