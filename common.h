#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <assert.h>
#include <math.h>

/* ================= 시간 파라미터 =================== */
#define TICK 10		// time unit(ms)
#define WAITING_SECOND_ARROW 200

#define N_LAYER 2
#define MAP_WIDTH	60
#define MAP_HEIGHT	18

/* ================= 창 크기 파라미터 =================== */
// SetConsoleCursorPosition()함수의 특성 고려
// gotoxy()가 제대로 작동하는 범위로 창 크기 정의

#define STATE_WINDOW_MAX_HEIGHT 18
#define STATE_WINDOW_MAX_WIDTH 50

#define SYSTEM_MESSAGE_W_HEIGHT 10
#define SYSTEM_MESSAGE_W_WIDTH 60

#define COMMAND_WINDOW_HEIGHT 10
#define COMMAND_WINDOW_WIDTH 50

/* ================= 3-1 샌드웜과 비교할 유닛 대상 수 파라미터 =================== */
#define COMPARING_WITH_SAND_WORM 2

/* ================= 위치, 방향 관련 구조체 =================== */
// (행, 열) 위치를 나타내는 구조체
typedef struct {
	int row, column;
} POSITION;

// 커서 직전 위치, 현재 위치를 나타내는 구조체 
typedef struct {
	POSITION previous;  // 직전 위치
	POSITION current;   // 현재 위치
} CURSOR;

// 입력 가능한 키 종류 열거체
typedef enum {
	k_none = 0, k_up, k_left, k_right, k_down, //1:위, 2: 왼쪽, 3: 오른쪽, 4 : 아래
	k_space, k_esc, //5: 스페이스, 6: ESC
	k_quit, //7: 게임 종료
	k_undef, // 8: 정의되지 않은 키 입력	
} KEY;

// 방향키의 의미론적인 semantic 열거체 초기화
typedef enum {
	d_stay = 0, d_up, d_left, d_right, d_down
} DIRECTION;
// 공통: 두 좌표의 합을 구하는 inline 함수
inline POSITION position_move_f(POSITION p1, POSITION p2) {
	POSITION p = { p1.row + p2.row, p1.column + p2.column };
	return p;
}

// 공통: 두 좌표의 차를 구하는 inline 함수 
inline POSITION position_subtraction_f_inline(POSITION p1, POSITION p2) {
	POSITION p = { p1.row - p2.row, p1.column - p2.column };
	return p;
}

// 2-1) 방향키인지 확인하는 매크로 함수
#define is_arrow_key_f_mac(k)		(k_up <= (k) && (k) <= k_down)

// 2-1) 화살표 '키'(KEY)를 '방향'(DIRECTION)으로 변환하는 매크로함수 
#define key_to_direction_f_mac(k)		(DIRECTION)(k)

// 2-1) 방향키 1회 입력을 POSITION 벡터로 변환해서 좌표를 연산할 준비를 도와주는 함수
inline POSITION dtop(DIRECTION d) {
	static POSITION direction_vector[] = { {0, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
	return direction_vector[d];
}
// 2-2) 더블 방향키 입력을 POSITION 벡터로 변환해서 좌표를 연산할 준비를 도와주는 함수
inline POSITION dtop_f_inline(DIRECTION Key) {
	static POSITION Direction_Vector2_arr[] = { {0, 0}, {-5, 0}, {0, -5}, {0, 5}, {5, 0} };
	return Direction_Vector2_arr[Key];
}
// 2-1) 위치 벡터p를 1회 키 입력 방향 벡터d 와 더하는 매크로 함수 
#define position_by_arrow_move_f_mac(p, d)		(position_move_f((p), dtop(d)))
// 2-2) 위치 벡터p를 2회 키 입력 방향 벡터d 와 더하는 매크로 함수
#define position_by_arrow_move2_f_mac(p, d)		(position_move_f((p), dtop_f_inline(d)))

/* ================= 자원, 유닛, 지형, 건물 구조체 선언부 =================== */
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
	POSITION dest;		 // 목적지(10estination)
	char representation; // 화면에 표시할 문자
	int speed; // 주기
	int move_period;	 // '몇 ms마다 한 칸 움직이는지'를 뜻함
	int next_move_time;	 // 다음에 움직일 초기 시간 및 축적용 변수
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